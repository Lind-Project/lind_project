import psycopg2
import random
from flask import Flask, jsonify, request

app = Flask(__name__)

conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")

def _get_random_rows(loops, batch_size):
    cur = conn.cursor()
    results = []

    # Calculate how many loops do we want when exceeding 1000
    for i in range(0, loops):
        id = i % 1000
        # Generate a random ID
        # random_id = random.randint(0, 1000)
        for _ in range(0, batch_size):
            # Query for each individual ID
            query = 'SELECT * FROM world WHERE id = %s;'
            cur.execute(query, (id,))

            # Append the result of each query to the results list
            results.extend(cur.fetchall())
        

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
    loop = 2**(power-16) # subtract 2^16 because each iter of get random rows gens 64kb
    result = _get_random_rows(loop, 32) #32 * 2kb 64kb
    return jsonify(result)


@app.route('/mixed')
def mixed():

    power = int(request.args.get('power', 16))

    ##generate queries
    loop = 2**(power-16) #subtract one more from power here because only half queries
    result = _get_random_rows(loop, 16) #16 * 2kb 32kb

    ## generate plaintext
    # Calculate the total size in bytes
    total_size = 2 ** (power - 1) #subtract 1 here bc only half from plaintext
    
    # Determine how many times to repeat 'Hello, World!!!!'
    base_string = "Hello, World!!!!"
    base_str_utf8 = base_string.encode('utf-8')
    
    # Ignore the remainder after the decimal point
    repeat_count = total_size // len(base_str_utf8)
    
    # Generate the response string 
    # repeat_str = base_str_utf8 * repeat_count

    response_list = [base_str_utf8] * repeat_count

    # # Check again the final data length and remove extra chars
    # response_string = repeat_str.encode('utf-8')[:total_size].decode('utf-8', 'ignore')
    
    return jsonify(result + response_list)

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
    base_str_utf8 = base_string.encode('utf-8')
    
    # Ignore the remainder after the decimal point
    repeat_count = total_size // len(base_str_utf8)
    
    # # Generate the response string 
    response_list = [base_str_utf8] * repeat_count
    
    # Return the generated string
    return jsonify(response_list)

if __name__ == "__main__":
    app.run(host="0.0.0.0")
    conn.close()