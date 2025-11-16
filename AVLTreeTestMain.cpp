/*
@filename: AVL Search Tree Test Main

@author: Doc Holloway
@date: 10/15/2025

@description: This program implements an AVL algorithm to automatically rebalance a binary search tree as items are inserted and deleted. The program also
includes the implementation of insertion, deletion, search, and count functions to interact with the tree.

Compilation Instructions:
	Using Ubuntu 22.04:
		g++ -c AVLTreeTestMain.cpp -o main.o
		g++ -c AVLTemplateClass.cpp -o templateCode.o
		g++ main.o templateCode.o -o AVLTreeTest
	Using Visual Studio:
		Run local Windows debugger
*/
#include "AVLTemplateClass.h"

/*
Compare function used as pointer parameter in tree construction. Function returns -1, 0, or 1 based on the comparison
of two items.

@param[in]: Two TYPE items to be compared.
@return: -1,0, or 1 based on the comparison of the inputs.
*/
template <typename TYPE>
int compare(const TYPE& item1, const TYPE& item2)
{
	if (item1 < item2)
		return -1;
	if (item1 == item2)
		return 0;
	return 1;
}

/*
Main function facilitates construction of 8 binary search trees to carry out 8 test cases to cover all insertion and deletion rebalancing cases. This is done using
commands to insert and delete into the tree, as well as additional tests for the search and count functions.
Test values are used to check the heights and positions of specific nodes in each case, and the test only passes if these values are correct to the expected outcome.

@param[in]: Nothing. Main creates tree objects and manipulates them itself.
@return: Text output into the output window stating which tests were conducted and which passed.
*/
int main(int argc, char* argv[])
{
	int testValue1 = -1;
	int testValue2 = -1;

	BinarySearchTree<int> testTree1(compare);
	cout << "Beginning Insertion cases" << endl;
	testTree1.insert(5);
	testTree1.insert(2);
	testTree1.insert(8);
	testTree1.insert(7);
	testTree1.insert(6);
	testValue1 = testTree1.returnHeight(7);
	testValue2 = testTree1.returnHeight(8);
	if (testValue1 == 2 && testValue2 == 1)
	{
		cout << "Left-Left Case Passed" << endl;
	}

	BinarySearchTree<int> testTree2(compare);
	testTree2.insert(5);
	testTree2.insert(2);
	testTree2.insert(9);
	testTree2.insert(7);
	testTree2.insert(8);
	testValue1 = testTree2.returnHeight(8);
	testValue2 = testTree2.returnHeight(9);
	if (testValue1 == 2 && testValue2 == 1)
	{
		cout << "Left-Right Case Passed" << endl;
	}

	BinarySearchTree<int> testTree3(compare);
	testTree3.insert(5);
	testTree3.insert(2);
	testTree3.insert(9);
	testTree3.insert(11);
	testTree3.insert(10);
	testValue1 = testTree3.returnHeight(10);
	testValue2 = testTree3.returnHeight(9);
	if (testValue1 == 2 && testValue2 == 1)
	{
		cout << "Right-Left Case Passed" << endl;
	}

	BinarySearchTree<int> testTree4(compare);
	testTree4.insert(5);
	testTree4.insert(2);
	testTree4.insert(9);
	testTree4.insert(3);
	testTree4.insert(4);
	testValue1 = testTree4.returnHeight(2);
	testValue2 = testTree4.returnHeight(3);
	if (testValue1 == 1 && testValue2 == 2)
	{
		cout << "Right-Right Case Passed" << endl << endl;
	}

	cout << "Beginning Deletion Cases" << endl;

	BinarySearchTree<int> testTree5(compare);
	testTree5.insert(5);
	testTree5.insert(2);
	testTree5.insert(8);
	testTree5.insert(3);
	testTree5.insert(7);
	testTree5.insert(9);
	testTree5.insert(10);
	testTree5.remove(3);
	testValue1 = testTree5.returnHeight(5);
	testValue2 = testTree5.returnHeight(8);
	if (testValue1 == 2 && testValue2 == 3)
	{
		cout << "Lefthand and 0/1 Case Passed" << endl;
	}

	BinarySearchTree<int> testTree6(compare);
	testTree6.insert(5);
	testTree6.insert(2);
	testTree6.insert(8);
	testTree6.insert(3);
	testTree6.insert(7);
	testTree6.insert(9);
	testTree6.insert(6);
	testTree6.remove(3);
	testValue1 = testTree6.returnHeight(7);
	testValue2 = testTree6.returnHeight(8);
	if (testValue1 == 3 && testValue2 == 2)
	{
		cout << "Lefthand and -1 Case Passed" << endl;
	}

	BinarySearchTree<int> testTree7(compare);
	testTree7.insert(8);
	testTree7.insert(5);
	testTree7.insert(10);
	testTree7.insert(2);
	testTree7.insert(6);
	testTree7.insert(9);
	testTree7.insert(11);
	testTree7.insert(3);
	testTree7.insert(7);
	testTree7.insert(1);
	testTree7.insert(12);
	testTree7.insert(4);
	testTree7.remove(7);
	testValue1 = testTree7.returnHeight(3);
	testValue2 = testTree7.returnHeight(8);
	if (testValue1 == 3 && testValue2 == 4)
	{
		cout << "Righthand and 1 Case Passed" << endl;
	}

	BinarySearchTree<int> testTree8(compare);
	testTree8.insert(8);
	testTree8.insert(5);
	testTree8.insert(10);
	testTree8.insert(3);
	testTree8.insert(6);
	testTree8.insert(9);
	testTree8.insert(2);
	testTree8.insert(4);
	testTree8.insert(7);
	testTree8.insert(11);
	testTree8.insert(12);
	testTree8.insert(1);
	testTree8.remove(7);
	testValue1 = testTree8.returnHeight(3);
	testValue2 = testTree8.returnHeight(5);
	if (testValue1 == 3 && testValue2 == 2)
	{
		cout << "Righthand and 0/-1 Case Passed" << endl << endl;
	}

	cout << "Beginning supplemental tests" << endl;
	testValue1 = testTree8.search(5);
	testValue2 = testTree8.count();
	if (testValue1 == 5 && testValue2 == 11)
	{
		cout << "Count and Search tests passed" << endl << endl;
	}

	cout << "All Tests Complete. Passed tests are above." << endl;
	return 0;
}