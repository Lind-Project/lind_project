import psycopg2

# Establish a connection to the PostgreSQL database
conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")

# Open a cursor to perform database operations
cur = conn.cursor()

# Drop the existing 'pgbench_accounts' table if it exists
cur.execute("DROP TABLE IF EXISTS pgbench_accounts;")
cur.execute("DROP TABLE IF EXISTS pgbench_branches;")
cur.execute("DROP TABLE IF EXISTS pgbench_tellers;")
cur.execute("DROP TABLE IF EXISTS pgbench_history;")

# Create the 'pgbench_accounts' table with two columns: id and word
cur.execute(
    "CREATE TABLE pgbench_accounts ("
    "aid INT,"      
    "abalance INT" 
    ");"
)
cur.execute(
    "CREATE TABLE pgbench_branches ("
    "bid INT,"      
    "bbalance INT" 
    ");"
)
cur.execute(
    "CREATE TABLE pgbench_tellers ("
    "tid INT,"      
    "tbalance INT" 
    ");"
)
cur.execute(
    "CREATE TABLE pgbench_history ("
    "tid INT,"      
    "bid INT," 
    "aid INT," 
    "delta INT" 
    # "mtime TIMESTAMP" 
    ");"
)
# Commit the changes to the database
conn.commit()

# Copy data from the specified CSV file into the 'world' table
# Since our code is running as a client script, PostgreSQL cannot access ./lines.csv 
# on the server's file system. Instead, we will read the file with Python and insert 
# the data directly. 
# We don't have csv module been compiled in Lind, so copying manually instead.
pgbench_accounts = 'pgbench_accounts.txt'
pgbench_branches = 'pgbench_branches.txt'
pgbench_tellers = 'pgbench_tellers.txt'
# Open the pgbench_accounts file and read the data
with open(pgbench_accounts, 'r') as f:
    # Skip the header row
    next(f)
    for line in f:
        # Split each line by comma to parse the id and word columns
        row = line.strip().split(',')
        # Insert each row into the 'world' table
        cur.execute("INSERT INTO pgbench_accounts (aid, abalance) VALUES (%s, %s);", row)
with open(pgbench_branches, 'r') as f:
    # Skip the header row
    next(f)
    for line in f:
        # Split each line by comma to parse the id and word columns
        row = line.strip().split(',')
        # Insert each row into the 'world' table
        cur.execute("INSERT INTO pgbench_branches (bid, bbalance) VALUES (%s, %s);", row)
with open(pgbench_tellers, 'r') as f:
    # Skip the header row
    next(f)
    for line in f:
        # Split each line by comma to parse the id and word columns
        row = line.strip().split(',')
        # Insert each row into the 'world' table
        cur.execute("INSERT INTO pgbench_tellers (tid, tbalance) VALUES (%s, %s);", row)

# Commit the changes to the database after data insertion
conn.commit()

# Close the cursor and the connection
cur.close()
conn.close()
