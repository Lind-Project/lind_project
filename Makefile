#
# Makefile for Docker build
#
# AUTHOR: Joey Pabalinas <alyptik@protonmail.com>


%: | pull
	@$(MAKE) "lind/$(basename $(notdir $*))"

lind/%:
	docker run --label=lind -it alyptik/lind:latest /bin/bash -c './caging.sh $*'

.PHONY: Makefile lind run shell bash list show container build push swarm stack deploy manager pull clean

lind run: | pull
	docker run --label=lind -it alyptik/lind:latest /bin/bash -c './caging.sh'

shell bash: | pull
	docker run --label=lind -it alyptik/lind:latest /bin/bash

list show:
	docker container list -f=label=lind -sa

container build:
	docker build --label=lind -t lind:latest -f ./docker/Dockerfile ./docker

push:
	docker tag lind:latest alyptik/lind:latest
	docker push alyptik/lind:latest

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
