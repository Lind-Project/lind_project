#include "main.h"
#include <math.h>

// These will contain pre-allocated values that we will use often
FIOBJ HTTP_HEADER_X_DATA;

// static PostgreSQL connection
static PGconn *conn = NULL;

// Buffers for each endpoint and power level
static char *responses[MAX_POWER_INDEX] = {0};

// Pre-allocate buffers for each power level
static void init_buffers(void) {
    for (int i = 0; i < MAX_POWER_INDEX; ++i) {
        responses[i] = malloc(pow(2, MIN_POWER + (i*2)));
    }
}

// Initialize PostgreSQL connection
static void init_db(void) {
  conn = PQconnectdb("dbname=postgres user=lind host=/tmp");
  if (PQstatus(conn) != CONNECTION_OK) {
      fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
      exit(1);
  }
}


// Utility function to calculate index from power
static int power_to_index(int power) {
  return (power - MIN_POWER) / POWER_STEP;
}


// Utility function to free preallocated buffers
static void free_buffers(void) {
    for (int i = 0; i < MAX_POWER_INDEX; ++i) {
        free(responses[i]);
    }
}

// Utility function to extract the power parameter from the request
int extract_power(http_s *request) {
    // Parse the query string to get the "power" parameter
    http_parse_query(request);
    // Create a new string object for the key "power"
    FIOBJ key = fiobj_str_new("power", 5);
    // Get the value of the "power" parameter from the request
    FIOBJ power_param = fiobj_hash_get(request->params, key);
    // Convert the value to an integer, or use the default value if not provided
    // Check if the power value is within the valid range
    int power = power_param ? atoi(fiobj_obj2cstr(power_param).data) : MIN_POWER;
    if (power < MIN_POWER || power > MAX_POWER || (power - MIN_POWER) % POWER_STEP != 0) {
        http_send_error(request, 400);
        return MIN_POWER;
    }
    // Free the key object
    fiobj_free(key);
    // Return the power value
    return power;
}


// Utility function to handle postgres queries
// This function will be called to fill the response buffer with data from the database
size_t query_postgres(char *response, size_t total_queries, size_t response_offset) {

    char query[128];
    // Query to get the top n rows from world table.
    snprintf(query, sizeof(query), "SELECT * FROM world LIMIT %zu;", total_queries);
    
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return 0;
    }
    
    int nrows = PQntuples(res);
    // Assuming each value is exactly 2048 bytes (e.g., CHAR(2048))
    for (int i = 0; i < nrows; ++i) {
        char *value = PQgetvalue(res, i, 1);  // column index 1
        memcpy(response + response_offset, value, ROW_SIZE);
        response_offset += ROW_SIZE;
    }
    while (total_queries > ROW_SIZE) {
        total_queries = total_queries - ROW_SIZE;
        for (int i = 0; i < MIN(nrows, total_queries); ++i) {
            char *value = PQgetvalue(res, i, 1);  // column index 1
            memcpy(response + response_offset, value, ROW_SIZE);
            response_offset += ROW_SIZE;
        }
    }

    
    PQclear(res);

    return response_offset;
}


// Handler for the "/queries" endpoint
// Usage: /queries?power=16
static void on_queries(http_s *request) {

    // Parse the query string to get the "power" parameter
    int power = extract_power(request);

    // Index from power to use the right power level buffer
    int index_from_power = power_to_index(power);

    // Calculating Total rows to be queried from database.
    // Subtract 2^16 because each loop gens 64kb
    size_t loops = 1UL << (power - MIN_POWER);
    size_t total_queries = loops * BATCH_SIZE_QUERIES;

    char *response = responses[index_from_power];
    if (!response) {
        http_send_error(request, 500);
        return;
    }

    // Postgres query and output copied to response.
    size_t response_offset = query_postgres(response, total_queries, 0);
    if (response_offset == 0) {
        http_send_error(request, 500);
        return;
    }

    // Send final response
    http_send_body(request, response, response_offset);
}


// Handler for the "/mixed" endpoint
// Usage: /mixed?power=16
static void on_mixed(http_s *request) {
    // Parse the query string to get the "power" parameter
    int power = extract_power(request);

    // Index from power to use the right power level buffer
    int index_from_power = power_to_index(power);

    // Calculating Total rows to be queried from database.
    // Subtract 2^16 because each loop gens 64kb ideally but here we will only gen 32kb per loop and rest is plaintext.
    size_t loops = 1UL << (power - MIN_POWER);
    size_t total_queries = loops * BATCH_SIZE_MIXED;

    // Calculating Total plaintext loops 
    // -4 for 16 byes, -1 for only half of response is plaintext
    size_t plaintext_loops = 1UL << (power - 5);

    char *response = responses[index_from_power];
    if (!response) {
        http_send_error(request, 500);
        return;
    }

    // Postgres query and output copied to response.
    size_t response_offset = query_postgres(response, total_queries, 0);
    if (response_offset == 0) {
        http_send_error(request, 500);
        return;
    }

    // Fill the rest of the response with plaintext
    for (size_t i = 0; i < plaintext_loops; ++i) {
        memcpy(response + response_offset, PLAINTEXT_STR, PLAINTEXT_LEN);
        response_offset += PLAINTEXT_LEN;
    }

    // Send final response
    http_send_body(request, response, response_offset);
}


// Handler for the "/plaintext" endpoint
// Usage: /plaintext?power=16
static void on_plaintext(http_s *request) {
    // Parse the query string to get the "power" parameter
    int power = extract_power(request);

    // Calculate the total loops s
    // Determine how many times to repeat 'Hello, World!!!!' 16 bytes
    size_t loops = 1UL << (power - 4);
    int index_from_power = power_to_index(power);

    char *response = responses[index_from_power];
    size_t total_size = loops * PLAINTEXT_LEN;

    if (!response) {
        http_send_error(request, 500);
        return;
    }

    // Fill the rest of the response with plaintext
    for (size_t i = 0; i < loops; ++i) {
        memcpy(response + i * PLAINTEXT_LEN, PLAINTEXT_STR, PLAINTEXT_LEN);
    }

    // Send final response
    http_send_body(request, response, total_size);
}


// Listen to HTTP requests and start facil.io
int main(void) {

    // Initialize PostgreSQL connection
    init_db();

    // Initialize buffers
    init_buffers();

    // allocating values we use often
    HTTP_HEADER_X_DATA = fiobj_str_new("X-Data", 6);

    //FIO_LOG_LEVEL = FIO_LOG_LEVEL_DEBUG;

    const char *socket_path = "/tmp/facil.sock";

    // Remove existing socket file if it exists
    unlink(socket_path);

    // listen on port 3000 and any available network binding (NULL == 0.0.0.0)
    http_listen(NULL, socket_path, .on_request = on_request, .log = 1);

    // set the socket to be world writable
    chmod(socket_path, 0666);

    // start the server
    fio_start(.threads = 1);

    // deallocating the common values
    fiobj_free(HTTP_HEADER_X_DATA);

    // deallocating the buffers
    free_buffers();

    // close the PostgreSQL connection
    PQfinish(conn);
}

// Easy HTTP handling
void on_request(http_s *request) {
  FIOBJ path = request->path;
  if (fiobj_obj2cstr(path).len == 8 && memcmp(fiobj_obj2cstr(path).data, "/queries", 8) == 0) {
      on_queries(request);
  } else if (fiobj_obj2cstr(path).len == 6 && memcmp(fiobj_obj2cstr(path).data, "/mixed", 6) == 0) {
      on_mixed(request);
  } else if (fiobj_obj2cstr(path).len == 10 && memcmp(fiobj_obj2cstr(path).data, "/plaintext", 10) == 0) {
      on_plaintext(request);
  } else {
      http_send_error(request, 404);
  }
}
