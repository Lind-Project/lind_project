#
# Makefile - Builds the Docker images and host SDK for Lind
#
# AUTHOR: Joey Pabalinas <alyptik@protonmail.com>

all lind:
	@./mklind -e

.PHONY: Makefile all lind run shell bash list show latest prebuiltsdk base stack deploy pull clean prune

%:
	@$(MAKE) "lind/$(basename $(notdir $*))"

lind/%:
	@./mklind -e $*

run shell bash: | pull
	docker run --privileged --ipc=host --cap-add=SYS_PTRACE -it alyptik/lind /bin/bash

list show:
	docker image list -f label=lind -a
	docker container list -f label=lind -a

latest: | prebuiltsdk
	docker build --compress=true --cache-from=alyptik/lind:$| -t alyptik/lind:$@ ./docker/$|

prebuiltsdk: | base
	docker build --compress=true -t alyptik/lind:$@ ./docker/$@

base:
	docker build --compress=true -t alyptik/lind:$@ ./docker/$@

stack deploy:
	docker stack deploy -c ./docker/docker-compose.yml lindstack

pull:
	docker pull alyptik/lind

clean prune:
	docker image prune
	docker container prune
	docker stack rm lindstack
