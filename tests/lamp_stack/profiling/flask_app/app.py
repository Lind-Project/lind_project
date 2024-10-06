import psycopg2
import string
import random
from flask import Flask, jsonify, request

app = Flask(__name__)

html_size_128KBs = 2 ** 0
size = 2 ** 16
num_pages = int((html_size_128KBs * (2 ** 17)) / (2 * size)) # size * num_pages = html_size_128KBs


def rand_generator(size=size, chars=string.ascii_uppercase + string.digits):
    return "".join(random.choice(chars) for _ in range(size - 1))

data = []
for n in range(num_pages):
    title = rand_generator()
    review = rand_generator()
    data.append((title, n, review))

def get_db_connection():
    conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")
    return conn

def initialize_data():
    conn = get_db_connection()
    cur = conn.cursor()

    # Check if the table already has data
    cur.execute('SELECT COUNT(*) FROM books')
    count = cur.fetchone()[0]
    
    # Only insert data if the table is empty
    if count == 0:
        for n in range(num_pages):
            cur.execute(
                "INSERT INTO books (title, pages_num, review)"
                "VALUES (%s, %s, %s)",
                data[n],
            )
            if n % 5 == 0:
                conn.commit()
        conn.commit()
    cur.close()
    conn.close()

def _get_random_row():
    conn = get_db_connection()
    cur = conn.cursor()

    # Select a valid pages_num to query
    value = random.randint(0, num_pages - 1)  # pages_num is within range [0, num_pages)
    cur.execute('SELECT * FROM books WHERE pages_num = %s;', (value,))
    result = cur.fetchall()
    cur.close()
    conn.close()
    return result

@app.route('/db')
def db():
    initialize_data()  # Only initialize if necessary
    result = _get_random_row()
    return jsonify(result)

@app.route('/queries')
def queries():
    initialize_data()  # Only initialize if necessary
    num_queries = int(request.args.get('queries', 1))  # Default to 1 if not provided
    num_queries = min(500, max(num_queries, 1))
    result = [_get_random_row()[0] for i in range(num_queries)]
    return jsonify(result)

@app.route('/plaintext')
def plaintext():
    return 'Hello, world'

if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
