# Container image that runs your code
# FROM alpine:3.10

# Copies your code file from your action repository to the filesystem path `/` of the container
# COPY entrypoint.sh /entrypoint.sh

# Code file to execute when the docker container starts up (`entrypoint.sh`)
# ENTRYPOINT ["/entrypoint.sh"]

FROM ubuntu:20.04

RUN apt-get update && \
    apt-get upgrade -y &&  \
    apt-get install -y build-essential valgrind clang && \
    rm -fr /var/lib/apt/lists/*

WORKDIR /code

ENTRYPOINT ["valgrind --leak-check=full --show-leak-kinds=all ./minishell"]
