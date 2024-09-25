#!/bin/bash    

scripts/compile-lind.sh

mkdir data/

echo "Loading files into file system of Native-lind"
lindfs cp $PWD/scripts/pipescript.sh /pipescript.sh
lindfs cp $PWD/scripts/writepipe.nexe /writepipe
lindfs cp $PWD/scripts/readpipe.nexe /readpipe

echo -e "\nRunning with: -p lind /bin/bash /pipescript.sh -w 16 -r x -c $1"
python3 gen_pipedata.py -w 16 -r x -p "lind /bin/bash /pipescript.sh" -c $1

echo -e "\nRunning with: -p lind /bin/bash /pipescript.sh -w x -r x -c $1"
python3 gen_pipedata.py -w x -r x -p "lind /bin/bash /pipescript.sh" -c $1

echo -e "\nRunning with: -p lind /bin/bash /pipescript.sh -w x -r 16 -c $1"
python3 gen_pipedata.py -w x -r 16 -p "lind /bin/bash /pipescript.sh" -c $1