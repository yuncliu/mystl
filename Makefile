CPP=${CXX}
CC=${CC}
CFLAGS=-std=c++11 -Wall -g  -DDEBUG
LINKS	=  -lgtest -lpthread -lstdc++


TESTOBJS	= c++/src/new.o \
			  test/pair_unitest.o \
			  test/rbtree_unitest.o \
			  test/map_unitest.o \
			  test/utility_unitest.o \
		      main.o

TEST=a.out

VPATH		 = ./

INC=-I. \
	-I./c++ \
	-I./googletest/googletest/include

LIB=-L. \
	-L./googletest/build/googlemock/gtest

all:clean $(TEST)

gtest:
	git submodule init
	git submodule update
	mkdir googletest/build
	cd googletest/build;cmake ..;make



$(TEST):$(TESTOBJS)
	 $(CPP) $(CFLAGS) $(LIB) $(TESTOBJS) -o $@ $(LINKS)

%.o:%.cpp
	 $(CPP) $(CFLAGS) $(INC) -c $< -o $@

%.o:%.c
	 $(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(TESTOBJS)
	rm -rf $(TEST)
	rm -rf core
