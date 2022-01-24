CPP=g++ -lncurses --std=c++17
CFLAGS= -Wall

all : exec

exec : main.o Gate.o InputGate.o OutputGate.o LogicGate.o OneArgGate.o TwoArgGate.o Utils.o
	$(CPP) $(CFLAGS) -o $@ $^

main.o : main.cpp 
	$(CPP) $(CFLAGS) -c $<

Gate.o: Gate.cpp Gate.hpp 
	$(CPP) $(CFLAGS) -c $<

InputGate.o : InputGate.cpp InputGate.hpp
	$(CPP) $(CFLAGS) -c $<

OutputGate.o : OutputGate.cpp OutputGate.hpp
	$(CPP) $(CFLAGS) -c $<

LogicGate.o : LogicGate.cpp LogicGate.hpp
	$(CPP) $(CFLAGS) -c $<

OneArgGate.o: OneArgGate.cpp OneArgGate.hpp 
	$(CPP) $(CFLAGS) -c $<

TwoArgGate.o: TwoArgGate.cpp TwoArgGate.hpp 
	$(CPP) $(CFLAGS) -c $<

Utils.o : Utils.cpp Utils.hpp
	$(CPP) $(CFLAGS) -c $<

clean :
	rm *.o

test: all 
		./exec