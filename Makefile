#
# Makefile for Docker build
#
# AUTHOR: Joey Pabalinas <alyptik@protonmail.com>

all:
	@cd docker
	docker build -t lind -f Dockerfile .
