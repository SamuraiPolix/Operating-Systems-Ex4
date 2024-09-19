DEBUG ?= 1
COVERAGE ?= 0
PROFILING ?= 0

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
GCOV = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

ifeq ($(DEBUG), 1)
	CXXFLAGS += -DDEBUG
endif

ifeq ($(COVERAGE), 1)
	CXXFLAGS += $(GCOV)
endif

ifeq ($(PROFILING), 1)
	CXXFLAGS += -pg
endif

# Source files
SRCS = main.cpp euler_circuit.cpp
DEPS = euler_circuit.hpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target
TARGET = euler_circuit

# Directories
OUTPUTS_FOLDER = outputs
INPUTS_FOLDER = inputs
EXPECTED_FOLDER = expected
GCOV_OUTPUTS = gcov_outputs
GPROF_OUTPUTS = gprof_outputs
VALGRIND_OUTPUTS = valgrind_outputs

all: $(TARGET)

.PHONY: all clean clean_gcov coverage profile valgrind callgrind

coverage:
	make clean
	make all COVERAGE=1 DEBUG=0
	@echo "\033[34m Valid input \033[0m"
	./$(TARGET) -n 100 -e 300 -s 1 > /dev/null || true
	gcov $(SRCS) > $(GCOV_OUTPUTS)/stdout1.txt
	@echo "\033[34m Invalid argument \033[0m"
	./$(TARGET) -x 5 > /dev/null || true
	gcov $(SRCS) > $(GCOV_OUTPUTS)/stdout2.txt
	@echo "\033[34m Invalid argument values \033[0m"
	./$(TARGET) -n -1 -e 300 -s 1 > /dev/null || true
	./$(TARGET) -n 100 -e -1 -s 1 > /dev/null || true
	./$(TARGET) -n 2 -e 300 -s 1 > /dev/null || true
	gcov $(SRCS) > $(GCOV_OUTPUTS)/stdout3.txt
	@echo "\033[34m 0 edges \033[0m"
	./$(TARGET) -n 100 -e 0 -s 1 > /dev/null || true
	gcov $(SRCS) > $(GCOV_OUTPUTS)/stdoutFinal.txt
	mv *.gcov $(GCOV_OUTPUTS) || true
	mv *.gcda $(GCOV_OUTPUTS) || true
	mv *.gcno $(GCOV_OUTPUTS) || true

# use -pg flag for gprof
profile:
	make clean
	make all PROFILING=1
	./$(TARGET) -n 100000 -e 300000 -s 1 > /dev/null || true
	mv gmon.out $(GPROF_OUTPUTS)/gmon.out
	gprof $(TARGET) $(GPROF_OUTPUTS)/gmon.out > $(GPROF_OUTPUTS)/gmon.txt

valgrind: $(TARGET)
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(TARGET) -n 10000 -e 30000 -s 1 2> $(VALGRIND_OUTPUTS)/valgrind_stdout.txt

callgrind: $(TARGET)
	valgrind --tool=callgrind --callgrind-out-file=$(VALGRIND_OUTPUTS)/callgrind.out ./$(TARGET) -n 100000 -e 300000 -s 1 2> $(VALGRIND_OUTPUTS)/callgrind_stdout.txt
	callgrind_annotate $(VALGRIND_OUTPUTS)/callgrind.out > $(VALGRIND_OUTPUTS)/callgrind_annotate.txt
	kcachegrind $(VALGRIND_OUTPUTS)/callgrind

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

main.o: main.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c main.cpp

euler_circuit.o: euler_circuit.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c euler_circuit.cpp

clean:
	rm -f $(OBJS) $(TARGET)

clean_gcov:
	rm -f $(GCOV_OUTPUTS)/*.gcov $(GCOV_OUTPUTS)/*.gcda $(GCOV_OUTPUTS)/*.gcno $(GCOV_OUTPUTS)/stdout.txt $(GCOV_OUTPUTS)/*.gcda