import psycopg2
import string
import random

from flask import Flask, render_template

app = Flask(__name__)
html_size_128KBs = 2 ** 0
size = 2 ** 16
num_pages = int((html_size_128KBs * (2 ** 17)) / (2 * size)) # size * num_pages = html_size_128KBs
conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")


def rand_generator(size=size, chars=string.ascii_uppercase + string.digits):
    return "".join(random.choice(chars) for _ in range(size - 1))


data = []
for n in range(num_pages):
    title = rand_generator()
    review = rand_generator()
    data.append((title, n, review))


@app.route("/")
def index():
    cur = conn.cursor()

    for n in range(num_pages):
        cur.execute(
            "INSERT INTO books (title, pages_num, review)"
            "VALUES (%s, %s, %s)",
            data[n],
        )
        if n % 5 == 0:
            conn.commit()
    conn.commit()

    books = []
    for n in range(num_pages):
        cur.execute("SELECT * FROM books WHERE pages_num = %s", (n,))
        books.append(cur.fetchone())

    for n in range(num_pages):
        cur.execute("DELETE FROM books WHERE pages_num = %s", (n,))
        if n % 5 == 0:
            conn.commit()
    conn.commit()

    cur.close()
    return render_template("index.html", books=books)


if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
    conn.close()
