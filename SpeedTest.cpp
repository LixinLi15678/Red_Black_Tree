#include <cstdlib>
#include <ctime>
#include "RedBlackTree.h"

using namespace std;


int main(){

	// create a simulated 3.7 million ID number system.
	const int N = 3700000;

	clock_t start = clock();
	RedBlackTree rbt = RedBlackTree();
	for(int i = 0; i < N; i++){
		rbt.Insert(i);
	}
	clock_t stop = clock();

	double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
	cout << "Collected " << rbt.Size() << " ID numbers in " << (duration) << " seconds." << endl;


	// Your code goes here to simulate leaving / joining.
	unsigned short num = 0;

	while (num < 5) {
		int delNum = rand();
		try {
			start = clock();
			rbt.Remove(delNum);
			stop = clock();
			duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
			cout << "Delete " << (num + 1) << " ID number in " << (duration) << " seconds." << endl;
			num++;
		}
		catch (exception &e) {}
	}

	while (num > 0) {
		int insNum = rand();
		try {
			start = clock();
			rbt.Insert(insNum);
			stop = clock();
			duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
			cout << "Add " << (6 - num) << " ID number in " << (duration) << " seconds." << endl;
			num--;
		}
		catch (exception &e) {}
	}


	return 0;
}