#!make -f

CXX=clang
CXXFLAGS=-std=c++17 -Werror -Wsign-conversion -g
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Catan.cpp Buildable.cpp DevelopmentCard.cpp Board.cpp Player.cpp Tile.cpp Catan.cpp Types.cpp
CODE_SOURCES=Catan.cpp Buildable.cpp DevelopmentCard.cpp Board.cpp Player.cpp Tile.cpp Catan.cpp Types.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

# run: catan
# 	./$^

catan: Main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o catan -lstdc++

demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo -lstdc++

test: Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test -lstdc++ -lm

tidy:
	clang-tidy $(CODE_SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --
	# clang-tidy $(CODE_SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test catan
