CC = g++
CPPFLAGS = -std=c++11

.PHONY: all
all: gen convert

gen: rand_gen.cpp
	$(CC) $(CPPFLAGS) -o gen rand_gen.cpp

convert: mtx_to_pbm.cpp position.cc position.h
	$(CC) $(CPPFLAGS) -o convert mtx_to_pbm.cpp position.cc

.PHONY: clean
clean:
	-rm gen
	-rm convert

