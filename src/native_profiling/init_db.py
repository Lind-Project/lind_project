import os 
import psycopg2

conn = psycopg2.connect(
        host = "localhost", 
        database ="np_db",
        user=os.environ['DB_USERNAME'],
        password = os.environ['DB_PASSWORD']
        )
#conn = psycopg2.connect(
#        database="postgres",
#        user="lind",
#        host="/tmp"
#)

cur = conn.cursor()

cur.execute('DROP TABLE IF EXISTS np_table;')
cur.execute('CREATE TABLE np_table (id serial PRIMARY KEY, '
                                    'title varchar (65535) NOT NULL, '
                                    'author varchar (65535) NOT NULL, ' 
                                    'pages_num integer NOT NULL,' 
                                    'review text,'
                                    'date_added date DEFAULT CURRENT_TIMESTAMP);'
                                    )

# Insert data into the table

cur.execute('INSERT INTO np_table (title, author, pages_num, review)'
            'VALUES (%s, %s, %s, %s)',
            ('A Tale of Two Cities',
             'Charles Dickens',
             489,
             'A great classic!')
            )


conn.commit()

cur.close()
conn.close()
