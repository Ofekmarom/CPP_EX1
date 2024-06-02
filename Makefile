#ID : 208336701
#mail : ofekmarom9@gmail.com


CXX = clang++
CXXFLAGS = -std=c++11 -Werror -g -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

# Source files
SRC_DEMO = Demo.cpp Graph.cpp Algorithms.cpp
SRC_TEST = Test.cpp Graph.cpp Algorithms.cpp

# Object files
OBJ_DEMO = $(SRC_DEMO:.cpp=.o)
OBJ_TEST = $(SRC_TEST:.cpp=.o)

# Targets
all: demo test

run: demo
	./$^
runtest: test
	./$^

demo: $(OBJ_DEMO)
	$(CXX) $(CXXFLAGS) $(OBJ_DEMO) -o demo

test: $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) $(OBJ_TEST) -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test
