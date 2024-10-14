import psycopg2
import random
from datetime import datetime
import time
# import pytz

conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")

def transaction():
    cur = conn.cursor()
    results = []

    mtime = datetime.now()
    aid = random.randint(1, 100000)
    tid = random.randint(1, 10)
    bid = 1
    delta = random.randint(1, 100)

    query = 'UPDATE pgbench_accounts SET abalance = abalance + {} WHERE aid = {};'.format(delta, aid)
    cur.execute(query)

    query = 'SELECT abalance FROM pgbench_accounts WHERE aid = {};'.format(aid)
    cur.execute(query)
    results.extend(cur.fetchall())

    query = 'UPDATE pgbench_tellers SET tbalance = tbalance + {} WHERE tid = {};'.format(delta, tid) 
    cur.execute(query)

    query = 'UPDATE pgbench_branches SET bbalance = bbalance + {} WHERE bid = {};'.format(delta, bid) 
    cur.execute(query)

    query = "INSERT INTO pgbench_history (tid, bid, aid, delta, mtime) VALUES ({}, {}, {}, {}, '{}');".format(tid, bid, aid, delta, mtime) 
    cur.execute(query)

    conn.commit()
    cur.close()
    return results

def main():
    transactions = 1000
    t0 = time.time()
    for i in range(0, transactions):
        transaction()
    t1 = time.time()

    totaltime = t1 - t0
    print(totaltime)

if __name__ == "__main__":
    main()
    conn.close()
    