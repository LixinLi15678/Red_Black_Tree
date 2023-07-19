all:
	g++ -Wall -std=c++14 -g RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests

run:
	./rbt-tests

try: all run

testv:
	g++ -Wall -std=c++14 -g RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests
	valgrind --leak-check=full ./rbt-tests
	
tests:
	g++ -Wall -std=c++14 -g RedBlackTree.cpp SpeedTest.cpp -o rbt-sptest
	./rbt-sptest