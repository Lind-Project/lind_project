import psycopg2
import random
from flask import Flask, jsonify, request

app = Flask(__name__)

conn = psycopg2.connect(database="postgres", user="lind", host="/tmp")

def _get_random_rows(loops, batch_size):
    cur = conn.cursor()
    results = []

    queries_list = [None] * (loops * batch_size)

    # Calculate how many loops do we want when exceeding 1000
    for i in range(0, loops):
        id = i % 1000
        # Generate a random ID
        # random_id = random.randint(0, 1000)
        for j in range(0, batch_size):
            # Query for each individual ID
            query = 'SELECT * FROM world WHERE id = %s;'
            cur.execute(query, (id,))

            # Append the result of each query to the results list
            queries_list[(batch_size*i) + j] = cur.fetchall()
        

    cur.close()
    return results


@app.route('/queries')
def queries():
    power = int(request.args.get('power', 16))
    loop = 2**(power-16) # subtract 2^16 because each iter of get random rows gens 64kb
    queries_list = _get_random_rows(loop, 32) #32 * 2kb 64kb
    return ''.join(queries_list)


@app.route('/mixed')
def mixed():

    power = int(request.args.get('power', 16))

    ##generate queries
    loop = 2**(power-16) #subtract one more from power here because only half queries
    queries_list = _get_random_rows(loop, 16) #16 * 2kb 32kb


    # Calculate the total loops s
    # Determine how many times to repeat 'Hello, World!!!!'

    loops = 2 ** (power - 5) # -4 for 16 byes, -1 for only half of response is plaintext

    plaintext_list = [None] * loops
        
    for i in range(0, loops): plaintext_list[i] = "Hello, World!!!!"

    # # Check again the final data length and remove extra chars
    # response_string = repeat_str.encode('utf-8')[:total_size].decode('utf-8', 'ignore')
    
    return ''.join(queries_list + plaintext_list)

# Add 4 terminator at the end of str to extend the sentence to 16 bytes
# We want to test with the 2^16 to 2^26 skipping by 2 
# Usage: /plaintext?power=16
@app.route('/plaintext')
def plaintext():
    # Get the power from the query parameter or default to 16 if not provided
    power = int(request.args.get('power', 16))
    
    # Calculate the total loops s
    # Determine how many times to repeat 'Hello, World!!!!' 16 bytes

    loops = 2 ** (power - 4)

    plaintext_list = [None] * loops
        
    for i in range(0, loops): plaintext_list[i] = "Hello, World!!!!"
    
    # Return the generated string
    return "".join(plaintext_list)

if __name__ == "__main__":
    app.run(host="0.0.0.0")
    conn.close()