from flask import Flask, request, Response, abort
import psycopg2
import os

app = Flask(__name__)

MIN_POWER = 16          # original MIN_POWER
MAX_POWER = 30          # original MAX_POWER
POWER_STEP = 2          # original POWER_STEP
BATCH_SIZE_QUERIES = 32  # original BATCH_SIZE_QUERIES
BATCH_SIZE_MIXED = 16    # original BATCH_SIZE_MIXED
ROW_SIZE = 2048         # original ROW_SIZE (e.g. CHAR(2048))
PLAINTEXT_STR = b"Hello, World!!!!"
PLAINTEXT_LEN = len(PLAINTEXT_STR)

conn = psycopg2.connect(dbname="postgres", user="lind", host="/tmp")
conn.autocommit = True

def extract_power():
    p = request.args.get("power", type=int, default=MIN_POWER)
    if (
        p < MIN_POWER or
        p > MAX_POWER or
        (p - MIN_POWER) % POWER_STEP != 0
    ):
        abort(400, "Invalid `power` parameter")
    return p

def query_postgres(total_queries):
    cur = conn.cursor()
    cur.execute("SELECT * FROM world LIMIT %s;", (total_queries,))
    rows = cur.fetchall()
    cur.close()

    nrows = len(rows)
    if nrows == 0:
        abort(500, "No rows in `world` table")

    buf = bytearray()

    idx = 0
    for i in range(total_queries):
        value = rows[idx][1]
        chunk = value.encode() if isinstance(value, unicode) else value
        buf.extend(chunk[:ROW_SIZE])
        idx = (idx + 1) % nrows

    return bytes(buf)

@app.route('/queries')
def on_queries():
    power = extract_power()
    loops = 1 << (power - MIN_POWER)
    total = loops * BATCH_SIZE_QUERIES

    data = query_postgres(total)
    return Response(data, mimetype='text/plain')

@app.route('/mixed')
def on_mixed():
    power = extract_power()
    loops = 1 << (power - MIN_POWER)
    total = loops * BATCH_SIZE_MIXED

    plaintext_loops = 1 << (power - 5)

    data = bytearray(query_postgres(total))
    data.extend(PLAINTEXT_STR * plaintext_loops)
    return Response(bytes(data), mimetype='text/plain')

@app.route('/plaintext')
def on_plaintext():
    power = extract_power()
    loops = 1 << (power - 4)
    data = PLAINTEXT_STR * loops
    return Response(data, mimetype='text/plain')

if __name__ == '__main__':

    app.run(host='0.0.0.0', debug=True, threaded=False)
    conn.close()
