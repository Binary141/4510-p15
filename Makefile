all: build

run: build
	./p15

build:
	g++ -Wall -o p15 p15.cpp
