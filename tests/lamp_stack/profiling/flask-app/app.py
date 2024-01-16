import psycopg2
from flask import Flask, render_template
import string
import random

app = Flask(__name__)
size = 65535
num_pages = 5
conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")


def rand_generator(size=size, chars=string.ascii_uppercase + string.digits):
    return "".join(random.choice(chars) for _ in range(size))


data = []
for n in range(num_pages):
    title = rand_generator()
    author = rand_generator()
    review = rand_generator()
    data.append((title, author, n, review))


@app.route("/")
def index():
    cur = conn.cursor()

    for n in range(num_pages):
        cur.execute(
            "INSERT INTO books (title, author, pages_num, review)"
            "VALUES (%s, %s, %s, %s)",
            data[n],
        )
    conn.commit()

    books = []
    for n in range(num_pages):
        cur.execute("SELECT * FROM books WHERE pages_num = %s", (n,))
        books.append(cur.fetchone())

    for n in range(num_pages):
        cur.execute("DELETE FROM books WHERE pages_num = %s", (n,))

    cur.close()
    conn.commit()
    return render_template("index.html", books=books)


if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
    conn.close()
