#!/bin/bash

./select_accept &
sleep 5
./select_accept_client
pkill select_accept
