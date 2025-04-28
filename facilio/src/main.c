#include "main.h"

// We'll use this callback in `http_listen`, to handles HTTP requests
void on_request(http_s *request);

// These will contain pre-allocated values that we will use often
FIOBJ HTTP_HEADER_X_DATA;
// Set logging level to DEBUG

static PGconn *conn = NULL;

// Buffers for each endpoint and power level
static char **queries_buffers[MAX_POWER_INDEX] = {0};
static char **mixed_buffers[MAX_POWER_INDEX] = {0};
static char **plaintext_buffers[MAX_POWER_INDEX] = {0};
static size_t queries_counts[MAX_POWER_INDEX] = {0};
static size_t mixed_counts[MAX_POWER_INDEX] = {0};
static size_t plaintext_counts[MAX_POWER_INDEX] = {0};

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



// Free all allocated buffers
static void free_buffers(void) {
  for (int i = 0; i < MAX_POWER_INDEX; ++i) {
      free(queries_buffers[i]);
      free(mixed_buffers[i]);
      free(plaintext_buffers[i]);
  }
}

// Handler for /queries endpoint
static void on_queries(http_s *request) {
  http_parse_query(request);
  FIOBJ power_param = fiobj_hash_get(request->params, fiobj_str_new("power", 5));
  int power = power_param ? atoi(fiobj_obj2cstr(power_param).data) : MIN_POWER;
  if (power < MIN_POWER || power > MAX_POWER || (power - MIN_POWER) % POWER_STEP != 0) {
      http_send_error(request, 400);
      return;
  }

  int index = power_to_index(power);
  size_t loops = 1 << (power - MIN_POWER);
  size_t total_queries = loops * BATCH_SIZE_QUERIES;

  // Allocate buffer if not already allocated
  if (!queries_buffers[index]) {
      queries_buffers[index] = malloc(sizeof(char *) * total_queries);
      queries_counts[index] = total_queries;
  }

  char **buffer = queries_buffers[index];

  for (size_t i = 0; i < loops; ++i) {
      for (int j = 0; j < BATCH_SIZE_QUERIES; ++j) {
          int id = rand() % 1000 + 1;
          char query[64];
          snprintf(query, sizeof(query), "SELECT * FROM world WHERE id = %d;", id);
          PGresult *res = PQexec(conn, query);
          if (PQresultStatus(res) != PGRES_TUPLES_OK) {
              fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
              PQclear(res);
              continue;
          }
          buffer[i * BATCH_SIZE_QUERIES + j] = strdup(PQgetvalue(res, 0, 0));
          PQclear(res);
      }
  }
  // Calculate total response size
  size_t response_size = 0;
  for (size_t i = 0; i < total_queries; ++i) {
      response_size += strlen(buffer[i]);
  }

  char *response = malloc(response_size + 1);
  response[0] = '\0';
  for (size_t i = 0; i < total_queries; ++i) {
      strcat(response, buffer[i]);
      free(buffer[i]); // Free individual strings after use
  }

  http_send_body(request, response, response_size);
  free(response);
}

// Handler for /mixed endpoint
static void on_mixed(http_s *request) {
  http_parse_query(request);
  FIOBJ power_param = fiobj_hash_get(request->params, fiobj_str_new("power", 5));
  int power = power_param ? atoi(fiobj_obj2cstr(power_param).data) : MIN_POWER;
  if (power < MIN_POWER || power > MAX_POWER || (power - MIN_POWER) % POWER_STEP != 0) {
      http_send_error(request, 400);
      return;
  }

  int index = power_to_index(power);
  size_t loops = 1 << (power - MIN_POWER);
  size_t total_queries = loops * BATCH_SIZE_MIXED;
  size_t plaintext_loops = 1 << (power - 5);
  size_t total_entries = total_queries + plaintext_loops;

  // Allocate buffer if not already allocated
  if (!mixed_buffers[index]) {
      mixed_buffers[index] = malloc(sizeof(char *) * total_entries);
      mixed_counts[index] = total_entries;
  }

  char **buffer = mixed_buffers[index];

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
          buffer[i * BATCH_SIZE_MIXED + j] = strdup(PQgetvalue(res, 0, 0));
          PQclear(res);
      }
  }

  // Add plaintext entries
  for (size_t i = 0; i < plaintext_loops; ++i) {
      buffer[total_queries + i] = strdup(PLAINTEXT_STR);
  }

  // Calculate total response size
  size_t response_size = 0;
  for (size_t i = 0; i < total_entries; ++i) {
      response_size += strlen(buffer[i]);
  }

  char *response = malloc(response_size + 1);
  response[0] = '\0';
  for (size_t i = 0; i < total_entries; ++i) {
      strcat(response, buffer[i]);
      free(buffer[i]); // Free individual strings after use
  }

  http_send_body(request, response, response_size);
  free(response);
}

// Handler for /plaintext endpoint
static void on_plaintext(http_s *request) {
  http_parse_query(request);
  FIOBJ power_param = fiobj_hash_get(request->params, fiobj_str_new("power", 5));
  int power = power_param ? atoi(fiobj_obj2cstr(power_param).data) : MIN_POWER;
  if (power < MIN_POWER || power > MAX_POWER || (power - MIN_POWER) % POWER_STEP != 0) {
      http_send_error(request, 400);
      return;
  }

  int index = power_to_index(power);
  size_t loops = 1 << (power - 4);
  size_t total_size = loops * PLAINTEXT_LEN;

  // Allocate buffer if not already allocated
  if (!plaintext_buffers[index]) {
      plaintext_buffers[index] = malloc(sizeof(char *) * loops);
      plaintext_counts[index] = loops;
  }

  char **buffer = plaintext_buffers[index];

  for (size_t i = 0; i < loops; ++i) {
      buffer[i] = strdup(PLAINTEXT_STR);
  }

  char *response = malloc(total_size + 1);
  response[0] = '\0';
  for (size_t i = 0; i < loops; ++i) {
      strcat(response, buffer[i]);
      free(buffer[i]); // Free individual strings after use
  }

  http_send_body(request, response, total_size);
  free(response);
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