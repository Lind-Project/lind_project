#
# Makefile - Builds the Docker images and host SDK for Lind
#
# AUTHOR: Joey Pabalinas <alyptik@protonmail.com>

# default target shows `select` menu
all lind:
	@./mklind

.PHONY: Makefile all lind run shell list show
.PHONY: latest naclruntime prebuiltsdk base
.PHONY: stack deploy pull clean prune

# targets like `make nacl` and `make lind/nacl` run their respective `./mklind -e nacl` command
%:
	@$(MAKE) "lind/$(basename $(notdir $*))"

lind/%:
	@./mklind $*

# run a clean, temporary containter with target tag
docker/%:
	docker run --rm --label=lind --ipc=host --cap-add=SYS_PTRACE -it alyptik/lind:$*

# the `--ipc=host` flag is needed to mount /dev/shm with PROT_EXEC
run shell: | pull
	docker create --name=lind --label=lind --ipc=host --cap-add=SYS_PTRACE -it alyptik/lind
	docker start lind
	docker exec -it lind

list show:
	docker image list -f label=lind -a
	@echo
	docker container list -f label=lind -a

latest: | naclruntime
	docker build -cache-from=alyptik/lind:$| -t alyptik/lind:$@ ./docker/$|

naclruntime: | prebuiltsdk
	docker build -t alyptik/lind:$@ ./docker/$@

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
	docker stack rm lindstack
	docker container prune
	docker image prune

# vi:ft=make
