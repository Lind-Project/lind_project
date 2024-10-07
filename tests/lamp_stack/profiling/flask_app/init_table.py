import psycopg2
import csv

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
# Since our code is running as a client script, PostgreSQL cannot access ./lines.csv 
# on the server's file system. Instead, we will read the file with Python and insert 
# the data directly
csv_file_path = 'flask_app/lines.csv'
# Open the CSV file and read the data
with open(csv_file_path, 'r') as f:
    reader = csv.reader(f)
    next(reader)  # Skip the header row
    for row in reader:
        # Insert each row into the 'world' table
        cur.execute("INSERT INTO world (id, word) VALUES (%s, %s);", row)

# Commit the changes to the database after data insertion
conn.commit()

# Close the cursor and the connection
cur.close()
conn.close()
