.PHONY = all clean

CC = g++			

CPPFLAGS = -fopenmp -std=c++11

CPPSOURCES = $(wildcard *.cpp)
CPPOBJECTS = $(patsubst %.cpp,%,$(CPPSOURCES))


all: ${CPPOBJECTS}

%: %.cpp 
	${CC} ${CPPFLAGS} -o $@.o $<


clean:
	@echo "Cleaning up..."
	rm -rvf *.o