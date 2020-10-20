.PHONY: all build clean

all: build clean

build:
	g++ -std=c++11 -I./ main.cpp -lnuma

clean:
	rm -rf a.out
