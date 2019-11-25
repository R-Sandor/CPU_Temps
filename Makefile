TARGET_EXEC ?= CPUTemps
CC=g++
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS = include 
BOOST_ROOT ?= /usr/local/boost_1_71_0
INC_FLAGS := $(addprefix -I,$(INC_DIRS), $(BOOST_ROOT))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -O3 -std=c++17

$(TARGET_EXEC): $(OBJS) test
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo ".------..------.\n|R.--. ||S.--. |\n| :(): || :/\: |\n| ()() || :\/: |\n| '--'R|| '--'S|\n\`------'\`------'"
	@echo "github.com/R-Sandor"


# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean test test_clean

test:  
	@(cd test; make "BOOST_ROOT=$(BOOST_ROOT)"; echo "Done compiling");
	@(cd test; ./unitTests)

run_test: 
	@(cd test;  ./unitTests)

test_clean:
	cd test; make clean
	

clean: test_clean
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(TARGET_EXEC)
	$(RM) -f res/*"-core-"*
-include $(DEPS)

MKDIR_P ?= mkdir -p
