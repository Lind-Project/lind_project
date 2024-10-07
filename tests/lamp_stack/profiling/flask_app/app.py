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
    return result

@app.route('/db')
def db():
    result = _get_random_row()
    # Convert Python data structures (such as dictionaries, lists, strings, etc.) to HTTP 
    # response objects in JSON format. It can automatically serialize data into JSON format 
    # and set the appropriate Content-Type to application/json so that the client can 
    # recognize and parse it.
    return jsonify(result)

# Check the average queries size return (just printout)
@app.route('/queries')
def queries():
    num_queries  = int(request.args.get('queries'))
    num_queries = min(500, max(num_queries, 1))

    total_size = 0
    results = []

    for _ in range(num_queries):
        row = _get_random_row()
        results.append(row[0])
        
        # Calculate the size of the query result in bytes and add to total
        result_size = sum(len(str(item)) for item in row[0])
        total_size += result_size

    # Calculate the average size of the queries
    average_size = total_size / num_queries if num_queries > 0 else 0

    # Print out the average size
    print("Average query result size: {} bytes".format(average_size))

    return jsonify(results)

# Add 4 terminator at the end of str to extend the sentence to 16 bytes
# We want to test with the 2^16 to 2^26 skipping by 2 
# Usage: /plaintext?power=16
@app.route('/plaintext')
def plaintext():
    # Get the power from the query parameter or default to 16 if not provided
    power = int(request.args.get('power', 16))
    
    # Calculate the total size in bytes
    total_size = 2 ** power
    
    # Determine how many times to repeat 'Hello, World!!!!'
    base_string = "Hello, World!!!!"
    repeat_count = total_size // len(base_string)
    
    # Generate the response string of the required size
    response_string = base_string * repeat_count
    
    # Return the generated string
    return response_string

if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
    conn.close()
