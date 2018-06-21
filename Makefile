#
# Makefile - Builds the Docker images and host SDK for Lind
#
# AUTHOR: Joey Pabalinas <alyptik@protonmail.com>

# default target shows `select` menu
all lind:
	@./mklind -e

.PHONY: Makefile all lind run shell bash list show latest prebuiltsdk base stack deploy pull clean prune

# targets like `make nacl` and `make lind/nacl` run their respective `./mklind -e nacl` command
%:
	@$(MAKE) "lind/$(basename $(notdir $*))"

lind/%:
	@./mklind -e $*

# "--privileged" and "--ipc=host" are needed to set /dev/shm as PROT_EXEC
run shell bash: | pull
	docker run --privileged --ipc=host --cap-add=SYS_PTRACE -it alyptik/lind /bin/bash

list show:
	docker image list -f label=lind -a
	docker container list -f label=lind -a

latest: | prebuiltsdk
	docker build -cache-from=alyptik/lind:$| -t alyptik/lind:$@ ./docker/$|

prebuiltsdk: | base
	docker build -t alyptik/lind:$@ ./docker/$@

base:
	docker build -t alyptik/lind:$@ ./docker/$@

stack deploy:
	docker stack deploy -c ./docker/docker-compose.yml lindstack

pull:
	docker pull alyptik/lind

clean:
	@$(MAKE) cleanall

prune:
	docker image prune
	docker container prune
	docker stack rm lindstack
