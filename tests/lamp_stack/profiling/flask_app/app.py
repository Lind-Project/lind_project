import psycopg2
import string
import random
from flask import Flask, jsonify, request

app = Flask(__name__)

html_size_128KBs = 2 ** 0
size = 2 ** 16
num_pages = int((html_size_128KBs * (2 ** 17)) / (2 * size))  # size * num_pages = html_size_128KBs

conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")

def rand_generator(size=size, chars=string.ascii_uppercase + string.digits):
    return "".join(random.choice(chars) for _ in range(size - 1))

def _get_random_row():
    cur = conn.cursor()
    value = random.randint(1, 10000)
    cur.execute('SELECT * FROM world WHERE id = %s;', (value,))
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
    num_queries  = int(request.args.get('queries'))
    num_queries = min(500, max(num_queries, 1))
    result = [_get_random_row()[0]  for i in range(num_queries)]
    return jsonify(result)

@app.route('/plaintext')
def plaintext():
    return 'Hello, world'

if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
    conn.close()
