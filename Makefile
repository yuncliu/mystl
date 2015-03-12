CPP=${CXX}
CC=${CC}
CFLAGS=-Wall -g  -DDEBUG
LINKS	=  -lgtest -lpthread -lstdc++


TESTOBJS	= test/pair_unitest.o \
			  test/functional_unitest.o \
			  test/rbtree_unitest.o \
			  test/map_unitest.o \
		      main.o

TEST=a.out

VPATH		 = ./

INC=-I.\
	-I./bits

LIB=-L.


all:clean $(TEST)


$(TEST):$(TESTOBJS)
		 $(CPP) $(CFLAGS) $(LIB) $(TESTOBJS) -o $@ $(LINKS)

%.o:%.cpp
		 $(CPP) $(CFLAGS) $(INC) -c $< -o $@

%.o:%.c
		 $(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(TESTOBJS) 
	rm -rf $(TEST) 
	rm -rf core*
