#include "main.h"
#include <math.h>

#define PGSTRLEN 2048
// We'll use this callback in `http_listen`, to handles HTTP requests
void on_request(http_s *request);

// These will contain pre-allocated values that we will use often
FIOBJ HTTP_HEADER_X_DATA;
// Set logging level to DEBUG

static PGconn *conn = NULL;

// Buffers for each endpoint and power level
// New pre-allocated response buffers
static char *responses[MAX_POWER_INDEX] = {0};

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



static void free_buffers(void) {
    for (int i = 0; i < MAX_POWER_INDEX; ++i) {
        free(responses[i]);
    }
}

static void on_queries(http_s *request) {
    http_parse_query(request);
    FIOBJ key = fiobj_str_new("power", 5);
    FIOBJ power_param = fiobj_hash_get(request->params, key);
    int power = power_param ? atoi(fiobj_obj2cstr(power_param).data) : MIN_POWER;
    if (power < MIN_POWER || power > MAX_POWER || (power - MIN_POWER) % POWER_STEP != 0) {
        http_send_error(request, 400);
        return;
    }

    fiobj_free(key);

    int index = power_to_index(power);
    size_t loops = 1UL << (power - MIN_POWER);
    size_t total_queries = loops * BATCH_SIZE_QUERIES;

    // Estimate max response size: assuming ~64 bytes per query result
    size_t estimated_size = total_queries * 2048;
    char *response = responses[index];
    if (!response) {
        http_send_error(request, 500);
        return;
    }
    //memset(response, 0, estimated_size);
    char *resp_copy_ptr = response;

    for (size_t i = 0; i < loops; ++i) {
        for (int j = 0; j < BATCH_SIZE_QUERIES; ++j) {
            int id = i % 1000 + 1;
            char query[64];
            snprintf(query, sizeof(query), "SELECT * FROM world WHERE id = %d;", id);
            PGresult *res = PQexec(conn, query);
            if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
                PQclear(res);
                continue;
            }
            resp_copy_ptr = PQgetvalue(res, 0, 1);
            resp_copy_ptr = resp_copy_ptr + PGSTRLEN;

            PQclear(res);
        }
    }

    http_send_body(request, response, response_offset);
}



static void on_mixed(http_s *request) {
    http_parse_query(request);
    FIOBJ key = fiobj_str_new("power", 5);
    FIOBJ power_param = fiobj_hash_get(request->params, key);
    int power = power_param ? atoi(fiobj_obj2cstr(power_param).data) : MIN_POWER;
    if (power < MIN_POWER || power > MAX_POWER || (power - MIN_POWER) % POWER_STEP != 0) {
        http_send_error(request, 400);
        return;
    }

    fiobj_free(key);

    int index = power_to_index(power);
    char *response = responses[index];
    if (!response) {
        http_send_error(request, 500);
        return;
    }

    size_t loops = 1UL << (power - MIN_POWER);
    size_t total_queries = loops * BATCH_SIZE_MIXED;
    size_t plaintext_loops = 1UL << (power - 5);

    size_t response_offset = 0;

    // Fetch database entries
    for (size_t i = 0; i < loops; ++i) {
        for (int j = 0; j < BATCH_SIZE_MIXED; ++j) {
            int id = rand() % 1000 + 1;
            char query[64];
            snprintf(query, sizeof(query), "SELECT * FROM world WHERE id = %d;", id);
            PGresult *res = PQexec(conn, query);
            if (PQresultStatus(res) != PGRES_TUPLES_OK) {
                fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
                PQclear(res);
                continue;
            }
            char *value = PQgetvalue(res, 0, 1);
            size_t val_len = strlen(value);

            memcpy(response + response_offset, value, val_len-1);
            response_offset += val_len-1;

            PQclear(res);
        }
    }

    for (size_t i = 0; i < plaintext_loops; ++i) {
        memcpy(response + response_offset, PLAINTEXT_STR, PLAINTEXT_LEN);
        response_offset += PLAINTEXT_LEN;
    }

    // Send final response
    http_send_body(request, response, response_offset);
}



static void on_plaintext(http_s *request) {
    http_parse_query(request);
    FIOBJ key = fiobj_str_new("power", 5);
    FIOBJ power_param = fiobj_hash_get(request->params, key);
    int power = power_param ? atoi(fiobj_obj2cstr(power_param).data) : MIN_POWER;
    if (power < MIN_POWER || power > MAX_POWER || (power - MIN_POWER) % POWER_STEP != 0) {
        http_send_error(request, 400);
        return;
    }

    fiobj_free(key);

    size_t loops = 1UL << (power - 4);
    int index = power_to_index(power);

    char *response = responses[index];
    size_t total_size = loops * PLAINTEXT_LEN;

    if (!response) {
        http_send_error(request, 500);
        return;
    }

    for (size_t i = 0; i < loops; ++i) {
        memcpy(response + i * PLAINTEXT_LEN, PLAINTEXT_STR, PLAINTEXT_LEN);
    }

    http_send_body(request, response, total_size);
}


void on_debug(http_s *request) {
  // SQL query to count rows in the 'world' table
  const char *query = "SELECT COUNT(*) FROM world;";

  // Execute the query
  PGresult *res = PQexec(conn, query);

  // Check for successful execution
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      // Send error response
      http_send_error(request, 500);
      PQclear(res);
      return;
  }

  // Retrieve the count result
  char *count_str = PQgetvalue(res, 0, 0);

  // Format the response
  char response[128];
  snprintf(response, sizeof(response), "Number of rows in 'world' table: %s\n", count_str);

  // Send the response
  http_send_body(request, response, strlen(response));

  // Clean up
  PQclear(res);
}


// Listen to HTTP requests and start facil.io
int main(void) {

  init_db();

  init_buffers();
  // allocating values we use often
  HTTP_HEADER_X_DATA = fiobj_str_new("X-Data", 6);

  FIO_LOG_LEVEL = FIO_LOG_LEVEL_DEBUG;

  const char *socket_path = "/tmp/facil.sock";

  // Remove existing socket file if it exists
  unlink(socket_path);
  // listen on port 3000 and any available network binding (NULL == 0.0.0.0)
  http_listen(NULL, socket_path, .on_request = on_request, .log = 1);

  chmod(socket_path, 0666);
  // start the server
  fio_start(.threads = 1);
  // deallocating the common values
  fiobj_free(HTTP_HEADER_X_DATA);
  free_buffers();
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
  } else if (fiobj_obj2cstr(path).len == 6 && memcmp(fiobj_obj2cstr(path).data, "/debug", 6) == 0) {
      on_debug(request);
  } else {
      http_send_error(request, 404);
  }
}