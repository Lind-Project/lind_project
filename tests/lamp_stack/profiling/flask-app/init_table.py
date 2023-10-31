import psycopg2


conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")

# Open a cursor to perform database operations
cur = conn.cursor()

# Execute a command: this creates a new table
cur.execute("DROP TABLE IF EXISTS books;")
cur.execute(
    "CREATE TABLE books (id serial PRIMARY KEY,"
    "title varchar (150) NOT NULL,"
    "author varchar (50) NOT NULL,"
    "pages_num integer NOT NULL,"
    "review text,"
    "date_added date DEFAULT CURRENT_TIMESTAMP);"
)

conn.commit()

cur.close()
conn.close()
