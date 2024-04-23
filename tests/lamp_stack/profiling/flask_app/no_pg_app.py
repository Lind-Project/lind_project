from flask import Flask, render_template
import string
import random

app = Flask(__name__)
size = 1024
num_pages = 64


def rand_generator(size=size, chars=string.ascii_uppercase + string.digits):
    return "".join(random.choice(chars) for _ in range(size))


@app.route("/")
def index():
    books = []

    for n in range(num_pages):
        title = rand_generator()
        review = rand_generator()
        books.append((title, n, review))

    return render_template("index.html", books=books)


if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
