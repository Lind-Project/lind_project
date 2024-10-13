#!/bin/bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install -y curl git vim build-essential libreadline-dev libpcre3 libpcre3-dev wrk python3 python3-pip python2.7
pip2 install gunicorn psycopg2-binary Flask
