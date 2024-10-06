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

def _get_random_row():
    conn = get_db_connection()
    cur = conn.cursor()

    # Initialize data table
    for n in range(num_pages):
        cur.execute(
            "INSERT INTO books (title, ID, review)"
            "VALUES (%s, %s, %s)",
            data[n],
        )
        if n % 5 == 0:
            conn.commit()
    conn.commit()

    value = random.randint(1, 10000)
    cur.execute('SELECT * FROM books WHERE ID=%s;' % value)
    result = cur.fetchall()
    cur.close()
    conn.close()
    return result

@app.route('/db')
def db():
    result = _get_random_row()
    return jsonify(result)

@app.route('/queries')
def queries():
    num_queries = int(request.args.get('queries'))
    num_queries = min(500, max(num_queries, 1))
    result = [_get_random_row()[0] for i in range(num_queries)]
    return jsonify(result)

@app.route('/plaintext')
def plaintext():
    return 'Hello, world'

if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
