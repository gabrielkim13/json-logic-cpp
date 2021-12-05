FROM alpine:latest

LABEL description="Container for use with C/C++ CMake projects"

RUN apk add --no-cache gawk wget git make gcc g++ gdb cmake

RUN mkdir -p /usr/local/src
WORKDIR /usr/local/src
