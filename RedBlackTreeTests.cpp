#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	// cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	// cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30); // leak here
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	// more tests go here
	// consider some symmetry!
	
	cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);

	cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  B13  R12  B20 ");
	delete rbt;
	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;
	
	RedBlackTree *rbt1 = new RedBlackTree();
	rbt1->Insert(30);
	rbt1->Insert(15);
	rbt1->Insert(45);
	rbt1->Insert(10);
	rbt1->Insert(25);

	try {
		rbt1->Insert(25);
		assert(false);
	} catch (invalid_argument &e) {
		assert(true);
	}

	delete rbt1;
	
	cout << "PASSED!" << endl << endl;
}

void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;

	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	rbt->Insert(11);
	rbt->Insert(10);
	rbt->Insert(9);
	rbt->Insert(8);
	rbt->Insert(7);
	rbt->Insert(6);
	rbt->Insert(5);
	rbt->Insert(4);
	rbt->Insert(3);
	rbt->Insert(2);
	rbt->Insert(1);

	delete rbt;

	rbt = new RedBlackTree();

	rbt->Insert(1);
	rbt->Insert(2);
	rbt->Insert(3);
	rbt->Insert(4);
	rbt->Insert(5);
	rbt->Insert(6);
	rbt->Insert(7);
	rbt->Insert(8);

	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);
	// cout << "rbt1: " << rbt1.ToPrefixString() << endl;
	// cout << "rbt2: " << rbt2.ToPrefixString() << endl;
	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	// cout << "rbt1: " << rbt1.ToPrefixString() << endl;
	// cout << "rbt2: " << rbt2.ToPrefixString() << endl;
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	RedBlackTree rbt3 = RedBlackTree();
	RedBlackTree rbt4 = RedBlackTree(rbt3);
	assert(rbt4.ToPrefixString() == rbt3.ToPrefixString());
	assert(rbt4.ToPrefixString() == "");

	cout << "PASSED!" << endl << endl;
}

void TestContains(){
	cout << "Testing Contains..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	assert(!rbt->Contains(0));
	assert(!rbt->Contains(100));

	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree *rbt = new RedBlackTree();

	try {
		rbt->GetMin();
		rbt->GetMax();
		assert(false);
	} catch (invalid_argument &e) {
		assert(true);
	}

	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);

	assert(rbt->GetMin() == 12);
	assert(rbt->GetMax() == 55);

	delete rbt;
	cout << "PASSED!" << endl << endl;
}

void TestRemove() {
	cout << "Testing Remove..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	cout << rbt->ToPrefixString() << endl;

	assert(rbt->Contains(34));
	rbt->Remove(34);
	assert(!rbt->Contains(34));
	cout << rbt->ToPrefixString() << endl;
	// assert(rbt->ToPrefixString() == "");

	assert(rbt->Contains(22));
	rbt->Remove(22);
	assert(!rbt->Contains(22));
	cout << rbt->ToPrefixString() << endl;
	// assert(rbt->ToPrefixString() == "");

	assert(rbt->Contains(40));
	rbt->Remove(40);
	assert(!rbt->Contains(40));
	cout << rbt->ToPrefixString() << endl;
	// assert(rbt->ToPrefixString() == "");

	assert(rbt->Contains(15));
	rbt->Remove(15);
	assert(!rbt->Contains(15));
	cout << rbt->ToPrefixString() << endl;
	// assert(rbt->ToPrefixString() == "");

	try {
		rbt->Remove(15);
		assert(false);
	} catch (invalid_argument &e) {
		e.what();
	}

	assert(rbt->Contains(31));
	rbt->Remove(31);
	assert(!rbt->Contains(31));
	cout << rbt->ToPrefixString() << endl;
	// assert(rbt->ToPrefixString() == "");

	assert(rbt->Contains(55));
	rbt->Remove(55);
	assert(!rbt->Contains(55));
	cout << rbt->ToPrefixString() << endl;
	// assert(rbt->ToPrefixString() == "");

	assert(rbt->Contains(12));
	rbt->Remove(12);
	assert(!rbt->Contains(12));
	cout << rbt->ToPrefixString() << endl;
	// assert(rbt->ToPrefixString() == "");

	assert(rbt->Contains(17));
	rbt->Remove(17);
	assert(!rbt->Contains(17));
	cout << rbt->ToPrefixString() << endl;
	// assert(rbt->ToPrefixString() == "");

	assert(rbt->Contains(29));
	rbt->Remove(29);
	assert(!rbt->Contains(29));
	cout << rbt->ToPrefixString() << endl;
	// assert(rbt->ToPrefixString() == "");

	try {
		rbt->Remove(29);
		assert(false);
	} catch (invalid_argument &e) {
		e.what();
	}

	delete rbt;
	cout << "PASSED!" << endl << endl;
}



int main(){

	
	TestSimpleConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();

	TestRemove();
	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
