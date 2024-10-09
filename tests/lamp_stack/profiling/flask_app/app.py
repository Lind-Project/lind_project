import psycopg2
import random
from flask import Flask, jsonify, request

app = Flask(__name__)

conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")

def _get_random_rows(num_rows):
    cur = conn.cursor()
    results = []

    # At most 1000 IDs each time
    batch_size = 1000

    # Calculate how many loops do we want when exceeding 1000
    for _ in range((num_rows + batch_size - 1) // batch_size):
        # Calculate current rows
        current_batch_size = min(batch_size, num_rows)

        ids = tuple(random.randint(1, 10000) for _ in range(current_batch_size))

        query = f'SELECT * FROM world WHERE id IN {ids};'
        cur.execute(query)

        results.extend(cur.fetchall())

        num_rows -= current_batch_size

    cur.close()
    return results


@app.route('/db')
def db():
    result = _get_random_rows(1)
    # Convert Python data structures (such as dictionaries, lists, strings, etc.) to HTTP 
    # response objects in JSON format. It can automatically serialize data into JSON format 
    # and set the appropriate Content-Type to application/json so that the client can 
    # recognize and parse it.
    return jsonify(result)

@app.route('/queries')
def queries():
    power = int(request.args.get('power', 16))

    # The average size of each query is 16 bytes
    num_queries = 2**(power-4)
    result = _get_random_rows(num_queries)
    return jsonify(result)

# Add 4 terminator at the end of str to extend the sentence to 16 bytes
# We want to test with the 2^16 to 2^26 skipping by 2 
# Usage: /plaintext?power=16
@app.route('/plaintext')
def plaintext():
    # Get the power from the query parameter or default to 16 if not provided
    power = int(request.args.get('power', 16))
    
    # Calculate the total size in bytes
    total_size = 2 ** (power-4)
    
    # Determine how many times to repeat 'Hello, World!!!!'
    base_string = "Hello, World!!!!"
    base_str_utf8 = base_string.encode('utf-8')
    
    # Ignore the remainder after the decimal point
    repeat_count = total_size // len(base_str_utf8)
    
    # Generate the response string 
    repeat_str = base_str_utf8 * repeat_count

    # Check again the final data length and remove extra chars
    response_string = repeat_str.encode('utf-8')[:total_size].decode('utf-8', 'ignore')
    
    # Return the generated string
    return response_string

if __name__ == "__main__":
    app.run(host="0.0.0.0")
    conn.close()
# import psycopg2
# import random
# from flask import Flask, jsonify, request

# app = Flask(__name__)

# conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")

# def _get_random_row():
#     cur = conn.cursor()
#     value = random.randint(1, 10000)
#     cur.execute('SELECT * FROM world WHERE id = %s;', (value,))
#     result = cur.fetchall()
#     cur.close()
#     return result

# @app.route('/db')
# def db():
#     result = _get_random_row()
#     # Convert Python data structures (such as dictionaries, lists, strings, etc.) to HTTP 
#     # response objects in JSON format. It can automatically serialize data into JSON format 
#     # and set the appropriate Content-Type to application/json so that the client can 
#     # recognize and parse it.
#     return jsonify(result)

# @app.route('/queries')
# def queries():
#     power = int(request.args.get('power', 16))

#     # The average size of each query is 16 bytes
#     num_queries = 2**(power-4)
#     result = [_get_random_row()[0] for _ in range(num_queries)]

#     return jsonify(result)

# # Add 4 terminator at the end of str to extend the sentence to 16 bytes
# # We want to test with the 2^16 to 2^26 skipping by 2 
# # Usage: /plaintext?power=16
# @app.route('/plaintext')
# def plaintext():
#     # Get the power from the query parameter or default to 16 if not provided
#     power = int(request.args.get('power', 16))
    
#     # Calculate the total size in bytes
#     total_size = 2 ** (power-4)
    
#     # Determine how many times to repeat 'Hello, World!!!!'
#     base_string = "Hello, World!!!!"
#     base_str_utf8 = base_string.encode('utf-8')
    
#     # Ignore the remainder after the decimal point
#     repeat_count = total_size // len(base_str_utf8)
    
#     # Generate the response string 
#     repeat_str = base_str_utf8 * repeat_count

#     # Check again the final data length and remove extra chars
#     response_string = repeat_str.encode('utf-8')[:total_size].decode('utf-8', 'ignore')
    
#     # Return the generated string
#     return response_string

# if __name__ == "__main__":
#     app.run(host="0.0.0.0")
#     conn.close()
