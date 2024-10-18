#!/bin/bash

# Execute (17, 27, 2)
for param in {17..27..2}; do
    python /home/lind/lind_project/tests/lamp_stack/profiling/flask_app/gen_static_html.py -s $param -o static_${param}.html
    echo "Generated static_${param}.html"

    # lindfs cp /home/lind/lind_project/tests/lamp_stack/profiling/flask_app/static_${param}.html /static_${param}.html
    echo "Copied static_${param}.html to /static_${param}.html"
done


cp /home/lind/lind_project/tests/lamp_stack/profiling/flask_app/static_${param}.html /home/lind/lind_project/static_${param}.html
echo "Copied static_${param}.html to /home/lind/lind_project/static_${param}.html"
