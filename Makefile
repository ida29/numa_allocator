.PHONY: all build clean

all: build clean

build:
	g++ -std=c++11 -lnuma -I./ main.cpp

clean:
	rm -rf a.out
