import psycopg2
from flask import Flask, render_template, request, url_for, redirect

app = Flask(__name__)


def get_db_connection():
    conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")

    return conn


@app.route("/")
def index():
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT * FROM books;")
    books = cur.fetchall()
    cur.close()
    conn.close()
    return render_template("index.html", books=books)


@app.route("/create/", methods=("GET", "POST"))
def create():
    if request.method == "POST":
        title = request.form["title"]
        author = request.form["author"]
        pages_num = int(request.form["pages_num"])
        review = request.form["review"]

        conn = get_db_connection()
        cur = conn.cursor()
        cur.execute(
            "INSERT INTO books (title, author, pages_num, review)"
            "VALUES (%s, %s, %s, %s)",
            (title, author, pages_num, review),
        )
        conn.commit()
        cur.close()
        conn.close()
        return redirect(url_for("index"))

    return render_template("create.html")


if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
