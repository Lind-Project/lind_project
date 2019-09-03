#
# Makefile - Builds the Docker images and host SDK for Lind
#
# AUTHOR: Joey Pabalinas <alyptik@protonmail.com>

# default target shows `select` menu
all lind:
	@./src/mklind

.PHONY: Makefile all lind run shell list show
.PHONY: latest naclruntime prebuiltsdk base
.PHONY: stack deploy pull clean prune

# targets like `make nacl` and `make lind/nacl` run their respective `./ src/mklind -e nacl` command
%:
	@$(MAKE) "lind/$(basename $(notdir $*))"

lind/%:
	@./src/mklind $*

# run a clean, temporary containter with target tag
docker/%:
	docker run --rm --label=lind --ipc=host --cap-add=SYS_PTRACE -it securesystemslab/lind:$*

# the `--ipc=host` flag is needed to mount /dev/shm with PROT_EXEC
run shell: | pull
	docker create --name=lind --label=lind --ipc=host --cap-add=SYS_PTRACE -it securesystemslab/lind
	docker start lind
	docker exec -it lind

list show:
	docker image list -f label=lind -a
	@echo
	docker container list -f label=lind -a

latest: | naclruntime
	docker build -cache-from=securesystemslab/lind:$| -t securesystemslab/lind:$@ ./src/docker/$|

naclruntime: | prebuiltsdk
	docker build -t securesystemslab/lind:$@ ./src/docker/$@

prebuiltsdk: | base
	docker build -t securesystemslab/lind:$@ ./src/docker/$@

base:
	docker build -t securesystemslab/lind:$@ ./src/docker/$@

stack deploy:
	docker stack deploy -c ./src/docker/docker-compose.yml lindstack

pull:
	docker pull securesystemslab/lind

clean:
	@$(MAKE) cleanall

prune:
	docker stack rm lindstack
	docker container prune
	docker image prune

# vi:ft=make
