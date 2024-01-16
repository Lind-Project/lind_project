import psycopg2
import string
import random
import time

size = 65535
num_pages = 5
conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")


def rand_generator(size=size, chars=string.ascii_uppercase + string.digits):
    return "".join(random.choice(chars) for _ in range(size))


def test():
    start_time = time.time()
    cur = conn.cursor()

    insert_start_time = time.time()
    for n in range(num_pages):
        title = rand_generator()
        author = rand_generator()
        review = rand_generator()
        cur.execute(
            "INSERT INTO books (title, author, pages_num, review)"
            "VALUES (%s, %s, %s, %s)",
            (title, author, n, review),
        )
    conn.commit()
    insert_end_time = time.time()

    books = []
    select_start_time = time.time()
    for n in range(num_pages):
        cur.execute("SELECT * FROM books WHERE pages_num = %s", (n,))
        books.append(cur.fetchone())
    select_end_time = time.time()

    delete_start_time = time.time()
    for n in range(num_pages):
        cur.execute("DELETE FROM books WHERE pages_num = %s", (n,))
    cur.close()
    conn.commit()
    delete_end_time = time.time()

    end_time = time.time()
    return {
        "insert": insert_end_time - insert_start_time,
        "select": select_end_time - select_start_time,
        "delete": delete_end_time - delete_start_time,
        "total": end_time - start_time,
    }


def run(num_requests=100):
    average_times = {"insert": 0, "select": 0, "delete": 0, "total": 0}
    for _ in range(num_requests):
        times = test()
        for key in times:
            average_times[key] += times[key] / num_requests

    print("Average times")
    for key in ["insert", "select", "delete", "total"]:
        print(key + ": " + str(round(average_times[key] * 1000, 3)) + " ms")


if __name__ == "__main__":
    run()
    conn.close()
