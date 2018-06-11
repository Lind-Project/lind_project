#
# Makefile for Docker build
#
# AUTHOR: Joey Pabalinas <alyptik@protonmail.com>


%: | pull
	@$(MAKE) "lind/$(basename $(notdir $*))"

lind/%:
	docker run -it alyptik/lind /bin/bash -c './caging.sh $*'

.PHONY: Makefile lind run shell bash list show build container push swarm stack deploy manager pull clean prune

lind run shell bash: | pull
	docker run -it alyptik/lind /bin/bash

list show:
	docker image list -f=label=lind -a
	docker container list -f=label=lind -a

build container:
	@cd ./docker
	docker build -t alyptik/lind .

push:
	docker push alyptik/lind

swarm stack deploy:
	@cd ./docker
	docker stack deploy -c ./docker-compose.yml lindstack

manager:
	docker swarm join-token manager

pull:
	docker pull alyptik/lind

clean prune:
	docker image prune
	docker container prune
	docker stack rm lindstack
	docker swarm leave --force
