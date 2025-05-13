#include "fio.h"

#include "fio_cli.h"
#include "http.h"
#include "libpq-fe.h"
#include "http.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "unistd.h"
#include "math.h"

#define MAX_POWER 26
#define MIN_POWER 16
#define POWER_STEP 2
#define MAX_POWER_INDEX ((MAX_POWER - MIN_POWER) / POWER_STEP + 1)
#define BATCH_SIZE_QUERIES 32
#define BATCH_SIZE_MIXED 16
#define PLAINTEXT_STR "Hello, World!!!!"
#define PLAINTEXT_LEN 16
#define ROW_SIZE 2048
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void on_request(http_s *request);
