MAINPROG=unitTests
SOURCES:=$(wildcard *.cpp)  
OBJECTS=$(SOURCES:.cpp=.o) 
BOOST_ROOT ?= 
INC_DIR = ../include 
BINS = $(-L../build)
FLAGS=-std=c++17 $(addprefix -I,$(INC_DIR), $(BOOST_ROOT))

all: $(SOURCES) $(MAINPROG)

$(MAINPROG): $(OBJECTS)
		g++ $(FLAGS) $(OBJECTS) ../build/src/matrixSolver.cpp.o $(BINS) -o $@

.cpp.o:
		g++ $(FLAGS) -c $< -o $@

clean:
		$(RM) *.o $(MAINPROG)


phony: test
	$(MAINPROG)
