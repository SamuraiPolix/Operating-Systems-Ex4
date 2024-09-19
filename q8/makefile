CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra


SRCS = race2.cpp Guard.cpp Singleton.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = race2

all: $(TARGET)

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

Guard.o: Guard.cpp Guard.hpp
	$(CXX) $(CXXFLAGS) -c Guard.cpp

Singleton.o: Singleton.cpp Singleton.hpp
	$(CXX) $(CXXFLAGS) -c Singleton.cpp

valgrind: $(TARGET)
	# valgrind --vgdb-error=0 --tool=memcheck -v --leak-check=full --show-leak-kinds=all  --error-exitcode=99 --track-origins=yes ./$(TARGET)
	valgrind --tool=helgrind ./$(TARGET)

clean:
	rm -f *.o $(TARGET)