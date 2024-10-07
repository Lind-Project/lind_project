import psycopg2

# Establish a connection to the PostgreSQL database
conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")

# Open a cursor to perform database operations
cur = conn.cursor()

# Drop the existing 'world' table if it exists
cur.execute("DROP TABLE IF EXISTS world;")

# Create the 'world' table with two columns: id and word
cur.execute(
    "CREATE TABLE world ("
    "id INT, "
    "word VARCHAR(255)"
    ");"
)

# Commit the changes to the database
conn.commit()

# Copy data from the specified CSV file into the 'world' table
csv_file_path = './lines.csv'
cur.execute(
    "COPY world(id, word) FROM %s DELIMITER ',' CSV HEADER;",
    (csv_file_path,)
)

# Commit the changes to the database after data insertion
conn.commit()

# Select and display the first 10 rows from the 'world' table
cur.execute("SELECT * FROM world LIMIT 10;")
rows = cur.fetchall()
for row in rows:
    print(row)

# Close the cursor and the connection
cur.close()
conn.close()
