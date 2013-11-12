##Jeremy Thomas
##CSCI 211
##Market Sim Project
##Makefile

FILES = sim.cpp cust.cpp pqueue.cpp

OBJS = $(FILES:.cpp=.o)

sim: $(OBJS)
	g++ -o sim -g $(OBJS)

%.o: %.cpp
	g++ -c $< -o $@

clean:
	rm -f *.o sim

remove:
	rm -f *.o
