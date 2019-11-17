MAINPROG=unitTests

BOOST_DIR?=/usr/local/boost_1_71_0
SOURCES:=$(wildcard *.cpp)  
OBJECTS=$(SOURCES:.cpp=.o) 
INC_DIR = ../include 
BINS = $(-L../build)
FLAGS=-std=c++17 $(addprefix -I,$(INC_DIR),  $(BOOST_DIR))

all: $(SOURCES) $(MAINPROG)

$(MAINPROG): $(OBJECTS)
		g++ $(FLAGS) $(OBJECTS) ../build/src/matrixSolver.cpp.o $(BINS) -o $@

.cpp.o:
		g++ $(FLAGS) -c $< -o $@

clean:
		$(RM) *.o $(MAINPROG)

