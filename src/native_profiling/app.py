import os 
import psycopg2
from flask import Flask, render_template, request, url_for, redirect
import string 
import random

app = Flask(__name__)
size = 65535
num_pages = 5

def get_db_connection():
    conn = psycopg2.connect(
        host = "localhost",
        database ="np_db",
        user=os.environ['DB_USERNAME'],
        password = os.environ['DB_PASSWORD']
        )
    #conn = psycopg2.connect(
    #    database="postgres",
    #    user="lind",
    #    host="/tmp"
    #)
    return conn

#maxsize=65535
def rand_generator(size=size, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

@app.route('/')
def index():
    conn = get_db_connection()
    cur = conn.cursor()
    n=0
    title = rand_generator()
    author = rand_generator()
    review = rand_generator()
    while n < num_pages: 
            cur.execute('INSERT INTO np_table (title, author, pages_num, review)'
            'VALUES (%s, %s, %s, %s)',
            (title,
             author,
             n,
             review)
            )
            n+=1
            
    conn.commit()

    n=0 

    np_table=[]
    while n < num_pages: 
        cur.execute("SELECT * FROM np_table WHERE pages_num = %s", (n,))
        np_table.append(cur.fetchone())
        n+=1

    while n < num_pages:
        cur.execute("DELETE * FROM np_table WHERE pages_num = %s", (n,))
        n+=1

    #np_table = rows
    cur.close()
    conn.commit()
    conn.close()
    return render_template('index.html', np_table=np_table)


if __name__ == "__main__":
    app.run(host = "0.0.0.0", debug=True)
