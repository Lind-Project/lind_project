#!/bin/bash

echo -e "Initializing postgres"
lind /bin/bash init_postgres.sh > /dev/null

params=(10 100 1000 10000 100000)
repeat_count=$1
json_file="tps_data.json"

total_tps_excluding=0

echo "{" > $json_file

for param in "${params[@]}"; do
  echo "Running tests with param = $param..."
  echo "  \"$param\": [" >> $json_file
  for ((i = 1; i <= repeat_count; i++)); do
    echo "Running iteration $i of $repeat_count for param = $param..."
    
    ./run_pg_lind.sh "$param" &> pg.log

    tps_excluding=$(grep "tps =" pg.log | grep "excluding" | awk '{print $3}')
    
    total_tps_excluding=$(echo "$total_tps_excluding + $tps_excluding" | bc)
    
    echo "TPS (excluding) for iteration $i with param $param: $tps_excluding"
    
    # JSON format: [param]: [tps_excluding]
    if [ "$i" -eq "$repeat_count" ]; then
      echo "    $tps_excluding" >> $json_file
    else
      echo "    $tps_excluding," >> $json_file
    fi
  done
  echo "  ]," >> $json_file
  average_tps_excluding=$(echo "$total_tps_excluding / $repeat_count" | bc -l)
  
  echo "Average TPS (excluding) for param $param: $average_tps_excluding"
done

echo "}" >> $json_file
