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
    "word1 VARCHAR(4000),"
    "word2 VARCHAR(4000),"
    "word3 VARCHAR(4000),"
    "word4 VARCHAR(4000)"
    ");"
)

# Commit the changes to the database
conn.commit()

# Copy data from the specified CSV file into the 'world' table
# Since our code is running as a client script, PostgreSQL cannot access ./lines.csv 
# on the server's file system. Instead, we will read the file with Python and insert 
# the data directly. 
# We don't have csv module been compiled in Lind, so copying manually instead.
csv_file_path = 'hitchdata4.csv'
# Open the CSV file and read the data
with open(csv_file_path, 'r') as f:
    # Skip the header row
    next(f)
    for line in f:
        # Split each line by comma to parse the id and word columns
        row = line.strip().split(',')
        # Insert each row into the 'world' table
        cur.execute("INSERT INTO world (id, word1, word2, word3, word4) VALUES (%s, %s, %s, %s, %s);", row)

# Commit the changes to the database after data insertion
conn.commit()

# Close the cursor and the connection
cur.close()
conn.close()
