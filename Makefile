#
# Makefile for Docker build
#
# AUTHOR: Joey Pabalinas <alyptik@protonmail.com>

all:
	$(MAKE) lind

.PHONY: lind shell bash run container build swarm stack deploy manager pull clean

lind: pull
	docker run --rm -it alyptik/lind:latest /bin/bash ./caging.sh

shell bash run: pull
	docker run --rm -it alyptik/lind:latest /bin/bash

container build:
	docker build -t alyptik/lind:latest -f ./docker/Dockerfile ./docker

swarm stack deploy:
	docker stack deploy -c ./docker/docker-compose.yml lindstack

manager:
	docker swarm join-token manager

pull:
	docker pull alyptik/lind:latest

clean:
	docker image prune
	docker container prune
	docker swarm leave --force
