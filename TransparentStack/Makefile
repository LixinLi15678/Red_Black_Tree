all:
	g++ -g -Wall -std=c++14 TransparentStack.h TransparentStackTests.cpp -o ts-tests

run:
	./ts-tests

try: all run

testv:
	g++ -Wall -std=c++14 TransparentStack.h TransparentStackTests.cpp -o ts-tests
	valgrind --leak-check=full ./ts-tests