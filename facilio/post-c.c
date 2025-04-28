#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

int main() {
    PGconn *conn;
    
    /* Connect to the database */
    conn = PQconnectdb("host=localhost port=5432 dbname=mydb user=postgres password=password");
    
    /* Check connection status */
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }
    
    printf("Connected to PostgreSQL database successfully!\n");
    
    /* Execute a simple query */
    PGresult *res = PQexec(conn, "SELECT version()");
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    
    /* Print query result */
    printf("PostgreSQL version: %s\n", PQgetvalue(res, 0, 0));
    
    /* Free result and close connection */
    PQclear(res);
    PQfinish(conn);
    
    return 0;
}
