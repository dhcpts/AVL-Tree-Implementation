/*
@filename: AVL Search Tree Template Class

@author: Doc Holloway
@date: 10/15/2025

@description: This program contains all of the function declarations and definitions used to implement the AVL rebalancing algorithm on a binary search tree.
The program uses templates with DATA_TYPE to create tree and node objects to interact with via movement, insertion, deletion, searching, counting, and rebalancing.

Compilation Instructions:
    Using Ubuntu 22.04:
        g++ -c AVLTreeTestMain.cpp -o main.o
        g++ -c AVLTemplateClass.cpp -o templateCode.o
        g++ main.o templateCode.o -o AVLTreeTest
    Using Visual Studio:
        Run local Windows debugger
*/
#pragma once
//Library inclusions in case DATA_TYPE is string.
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;
using std::string;
using std::stringstream;

/*
General exception class serves as template for specific exceptions that may occur within the program. Holds protected variables for exception info and 
the output string for an exception.

@param[in]: Error message and number from throw line later in program.
@return: Text output stating the error that has occurred.
*/
class Exception
{
protected:
	string message;
	int errorNumber;
public:
    Exception(int errNo, string msg) : errorNumber(errNo), message(msg) {}
    virtual string toString()
    {
        stringstream sstream;
        sstream << "Exception: " << errorNumber << " ERROR: " << message;
        return sstream.str();
    }
};
/*
Duplicate item error class inherits from the exception class and identifies the exception performed was that an insertion failed due to an item already
existing.

@param[in]: Inherited info on error from Exception class.
@return: Text output stating duplicateitem error has occurred.
*/
class DuplicateItemException : public Exception
{
public:
    DuplicateItemException(int eNo, string msg) : Exception(eNo, msg) {}
    string toString()
    {
        stringstream sstream;
        sstream << "DuplicatItemException: " << errorNumber << " ERROR: " << message;
        return sstream.str();
    }
};
/*
Empty tree exception class inherits from exception class and reports an error occurred due to the tree being empty. 

@param[in]: Inherited info on error from Exception class.
@return: Text output stating empty tree error has occurred.
*/
class TreeEmptyException : public Exception
{
public:
    TreeEmptyException(int eNo, string msg) : Exception(eNo, msg) {}
    string toString()
    {
        stringstream sstream;
        sstream << "TreeEmptyException: " << errorNumber << " ERROR: " << message;
        return sstream.str();
    }
};
/*
Item not found exception inherits from the general exception class and reports an error for a failed search/deletion stating the item was not found in the tree.

@param[in]: Inherited info on error from Exception class.
@return: Text output stating no item found error has occurred.
*/
class ItemNotFoundException : public Exception
{
public:
    ItemNotFoundException(int eNo, string msg) : Exception(eNo, msg) {}
    string toString()
    {
        stringstream sstream;

        sstream << "ItemNotFoundException: " << errorNumber << " ERROR: " << message;
        return sstream.str();
    }
};
/*
Massive Binary Search Tree class contains all the public and private information needed to create, manipulate, and delete a tree and its nodes. Each function and 
class contains a description of its role in the program.

@param[in]: Constructor takes function pointer to compare function in main.
@return: An AVL balancing binary search tree object able to be used by class functions.
*/
template <typename DATA_TYPE>
class BinarySearchTree
{
    /*
    Binary tree node class serves to identify the information held in each node of the tree, such as value assigned to it and its height. This also includes 
    pointers to the parent node, and left and right children.

    @param[in]: Nothing. Nodes are created using new and delete.
    @return: A tree node with pointers set to either null or the addresses of connected nodes, as well as node height and value.
    */
    class BinaryTreeNode
    {
    public:
        DATA_TYPE nodeValue;
        //Tree height represents subtree where a certain node is the root.
        int treeHeight;
        BinaryTreeNode* leftChild;
        BinaryTreeNode* rightChild;
        BinaryTreeNode* parent;

        BinaryTreeNode() { parent = leftChild = rightChild = nullptr; }
    };

    BinaryTreeNode* root;
    //NodeCount used for count function.
    int nodeCount;

    //Function declarations, and definitions for brief functions.
    int (*compare)(const DATA_TYPE& item1, const DATA_TYPE& item2);
    BinaryTreeNode* findParentOrDuplicate(const DATA_TYPE& item);
    /*
    Private inorder function carries out the processs of doing an inOrder tree traversal, and is used for findParentorDuplicate function.

    @param[in]: Node object used to visit various nodes until node doesn't exist, as well as a function pointer to visit to get a value.
    @return: Nothing, used to visit nodes along the tree.
    */
    void privateInOrder(BinaryTreeNode* node, void (*visit)(const DATA_TYPE& item))
    {
        if (!node)
            return;

        privateInOrder(node->leftChild, visit);
        visit(node->data);
        privateInOrder(node->rightChild, visit);
    }
    /*
    Post order delete function systematically deletes all nodes below and including the node inputted into the function. Used for destructor of tree.

    @param[in]: Node to be deleted, along with all children.
    @return: The deletion of said nodes, usually destroying the tree.
    */
    void postOrderDelete(BinaryTreeNode* node)
    {
        if (!node)
            return;

        postOrderDelete(node->leftChild);
        postOrderDelete(node->rightChild);
        delete node;
    }

    void rotateRight(BinaryTreeNode* node);
    void rotateLeft(BinaryTreeNode* node);
    int getHeight(BinaryTreeNode* node);

public:
    //Public function declarations, and definitions for simple functions.
    BinarySearchTree(int (*cmp)(const DATA_TYPE& item1, const DATA_TYPE& item2));
    ~BinarySearchTree();

    void insert(DATA_TYPE item);
    void remove(const DATA_TYPE& item);
    DATA_TYPE search(const DATA_TYPE& item);
    void insertRebalance(BinaryTreeNode* offBalanceNode, BinaryTreeNode* preNode, BinaryTreeNode* prepreNode);
    void removeRebalance(BinaryTreeNode* offbalanceNode, BinaryTreeNode* preNode, BinaryTreeNode* prepreNode);
    /*
    Count function simply returns nodeCount to display number of nodes in a tree.

    @param[in]: Nothing.
    @return: The current number of nodes in a tree.
*/
    int count()
    {
        return nodeCount;
    }
    /*
    In order function uses the visit function to call on privateInOrder, serving as a public call to the InOrder traversal.

    @param[in]: A function pointer to visit, meant to visit a certain item.
    @return: Nothing. Calls on private function to carry out task.
    */
    void inOrder(void (*visit)(const DATA_TYPE& item))
    {
        privateInOrder(root, visit);
    }

    /*
    Public rotation functions are simply accessors to the private rotation functions. These functions find the node that is meant to be rotated, and call on their
    private counterparts to carry out the operation.

    @param[in]: The value of the node being rotated.
    @return: A rotated node in the tree.
    */
    void rightRotatePublic(DATA_TYPE item)
    {
        BinaryTreeNode* rotatedNode = findParentOrDuplicate(item);
        rotateRight(rotatedNode);
    }
    void leftRotatePublic(DATA_TYPE item)
    {
        BinaryTreeNode* rotatedNode = findParentOrDuplicate(item);
        rotateLeft(rotatedNode);
    }
    /*
    Return height function is used in test cases to check the heights of key nodes to ensure operations have been done correctly. Function finds node and then returns
    the height of the node.

    @param[in]: Value of the node being searched for for its height.
    @return: The height of the node searched for.
    */
    int returnHeight(DATA_TYPE item)
    {
        BinaryTreeNode* node = findParentOrDuplicate(item);
        return node->treeHeight;
    }
};
/*
Constructor for the tree object takes in a function pointer to the compare function in main, and uses it to facilitate the binary search property. Also sets the 
initial conditions for an empty search tree.

@param[in]: Constructor takes function pointer to compare function in main.
@return: An empty binary search tree.
*/
template <typename DATA_TYPE>
BinarySearchTree<DATA_TYPE>::BinarySearchTree(int (*cmp)(const DATA_TYPE& item1, const DATA_TYPE& item2))
{
    compare = cmp;
    nodeCount = 0;
    root = nullptr;
}
/*
Destructor runs postOrderDelete starting at the root to fully empty a binary search tree.

@param[in]: Nothing.
@return: A newly empty tree.
*/
template <typename DATA_TYPE>
BinarySearchTree<DATA_TYPE>::~BinarySearchTree()
{
    postOrderDelete(root);
}

/*
Insert function takes in a value and creates a new node with that value. The node is inserted into the tree where it fits best based on the binary search property, or 
at the root if the tree is empty. Exception is thrown if the inserted item already exists. After inserting, a loop travels back up the tree from the point of insertion,
and updates the heights until it either reaches the root or finds a case where rebalancing using a function call is necessary.

@param[in]: An item to store in a new node.
@return: The tree with the new node, potentially rebalanced.
*/
template <typename DATA_TYPE>
void BinarySearchTree<DATA_TYPE>::insert(DATA_TYPE item)
{
    //Empty tree case
    if (!root)
    {
        root = new BinaryTreeNode();
        root->nodeValue = item;
        root->treeHeight = 1;
        nodeCount++;
        return;
    }

    // Find the parent node, or identify a duplicate entry
    BinaryTreeNode* searchNode = findParentOrDuplicate(item);
    if (!compare(searchNode->nodeValue, item)) // Check to see if the item already exists
    {
        // Duplicate item detected, throw an exception
        DuplicateItemException exception(__LINE__, "Duplicate item detected. Unable to insert");
        throw exception;
    }

    // Create new node
    BinaryTreeNode* node = new BinaryTreeNode();
    node->nodeValue = item;
    node->treeHeight = 1;

    // Link the parent
    node->parent = searchNode;

    // Determine if the node will be a left or right child
    // Attach the node to the appropriate side
    if (compare(searchNode->nodeValue, item) == 1)
        searchNode->leftChild = node;
    else
        searchNode->rightChild = node;

    nodeCount++;

    //Rebalance checks
    BinaryTreeNode* previousNode = nullptr;
    BinaryTreeNode* prePreviousNode = nullptr;
    int balanceFactor = 0;

    while (node->parent)
    {
        //Traversal up tree
        prePreviousNode = previousNode;
        previousNode = node;
        node = node->parent;
        
        //Calculation of balance factor
        int rightTreeHeight = 0;
        int leftTreeHeight = 0;
        BinaryTreeNode* right = node->rightChild;
        BinaryTreeNode* left = node->leftChild;
        if (right != nullptr)
        {
            rightTreeHeight = right->treeHeight;
        }
        if (left != nullptr)
        {
            leftTreeHeight = left->treeHeight;
        }
        balanceFactor = rightTreeHeight - leftTreeHeight;
        //Check of balance factor in case of rebalancing.
        if (balanceFactor < -1 || balanceFactor > 1)
        {
            insertRebalance(node, previousNode, prePreviousNode);
            break;
        }
        //Update height if no rebalance needed.
        node->treeHeight = getHeight(node);
    }
}
/*
Delete function takes in a value, and finds and deletes the node holding that value if it exists. If not, an item not found exception will be thrown. Function checks for
simple or complex deletion case, and handles it accordingly. Afterwards, delete loops back up the tree starting from the parent of the deleted node until it reaches
the root, rebalancing the tree in any cases where the balance factor of a node is off.

@param[in]: An item to delete out of the tree.
@return: The tree without the node, potentially rebalanced based on deletion changes.
*/
template <typename DATA_TYPE>
void BinarySearchTree<DATA_TYPE>::remove(const DATA_TYPE& item)
{
    // Find the item to remove
    BinaryTreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->nodeValue, item))
    {
        // Throw item not found exception
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    // Check to see if it is a simple or hard case
    if (searchResult->leftChild && searchResult->rightChild)
    {
        // Find the immediate predecessor
        BinaryTreeNode* current = searchResult->leftChild;
        while (current->rightChild)
            current = current->rightChild;
        // Swap the data items
        DATA_TYPE tmp = searchResult->nodeValue;
        searchResult->nodeValue = current->nodeValue;
        current->nodeValue = tmp;

        // Set searchResult to the immediate predecessor
        searchResult = current;
    }

    BinaryTreeNode* child = searchResult->rightChild ? searchResult->rightChild : searchResult->leftChild;
    BinaryTreeNode* parent = searchResult->parent;

    //Check for setting the new child to the proper child pointer of parent, and linking child to parent if it exists. Also setting child to root if no parent exists.
    if (parent)
    {
        BinaryTreeNode** side = parent->rightChild == searchResult ? &(parent->rightChild) : &(parent->leftChild);
        *side = child;
        if (child)
            child->parent = parent;
    }
    else
    {
        root = child;
    }

    delete searchResult;

    nodeCount--;

    //Rebalance checks
    BinaryTreeNode* previousNode = nullptr;
    BinaryTreeNode* prePreviousNode = nullptr;
    int balanceFactor = 0;

    while (parent)
    {
        //Calculate new height
        parent->treeHeight = getHeight(parent);

        //Calculate balance factor.
        int rightTreeHeight = 0;
        int leftTreeHeight = 0;
        BinaryTreeNode* right = parent->rightChild;
        BinaryTreeNode* left = parent->leftChild;
        if (right != nullptr)
        {
            rightTreeHeight = right->treeHeight;
        }
        if (left != nullptr)
        {
            leftTreeHeight = left->treeHeight;
        }
        balanceFactor = rightTreeHeight - leftTreeHeight;
        //Check for any necessary rebalance.
        if (balanceFactor < -1 || balanceFactor > 1)
        {
            removeRebalance(parent, previousNode, prePreviousNode);
        }
        //Traversal up tree.
        prePreviousNode = previousNode;
        previousNode = parent;
        parent = parent->parent;
    }
}
/*
Search function scans through tree and returns searched-for value, or an exception if the item was not found.

@param[in]: An item to search for in tree.
@return: The value of the node searched for.
*/
template <typename DATA_TYPE>
DATA_TYPE BinarySearchTree<DATA_TYPE>::search(const DATA_TYPE& item)
{
    BinaryTreeNode* searchResult = findParentOrDuplicate(item);
    if (!searchResult || compare(searchResult->nodeValue, item))
    {
        // Throw ItemNotFoundException
        throw ItemNotFoundException(__LINE__, "Item was not found");
    }

    return searchResult->nodeValue;
}
/*
Insert rebalance function takes in the previous few nodes after traveling up the tree, and determines which case of insertion rebalancing is needed using branching
conditionals. It then calls on certain rotation functions for certain nodes based on the case.

@param[in]: The node with an off-balance factor, the previous visited node, and the node visited before that.
@return: The tree rebalanced after insertion.
*/
template <typename DATA_TYPE>
void BinarySearchTree<DATA_TYPE>::insertRebalance(BinaryTreeNode* offbalanceNode, BinaryTreeNode* preNode, BinaryTreeNode* prepreNode)
{
    if (offbalanceNode->leftChild == preNode)
    {
        if (preNode->leftChild == prepreNode)
        {
            rotateRight(preNode);
        }
        else if (preNode->rightChild == prepreNode)
        {
            rotateLeft(prepreNode);
            rotateRight(prepreNode);
        }
    }
    else if (offbalanceNode->rightChild == preNode)
    {
        if (preNode->leftChild == prepreNode)
        {
            rotateRight(prepreNode);
            rotateLeft(prepreNode);
        }
        else if (preNode->rightChild == prepreNode)
        {
            rotateLeft(preNode);
        }
    }
}
/*
Remove rebalance function takes in the previous few nodes after traveling up the tree, and determines which case of deletion rebalancing is needed using branching
conditionals. It then calls on certain rotation functions for certain nodes based on the case.

@param[in]: The node with an off-balance factor, the previous visited node, and the node visited before that.
@return: The tree rebalanced after deletion.
*/
template <typename DATA_TYPE>
void BinarySearchTree<DATA_TYPE>::removeRebalance(BinaryTreeNode* offbalanceNode, BinaryTreeNode* preNode, BinaryTreeNode* prepreNode)
{
    int balanceFactor = 0;
    int leftTreeHeight = 0;
    int rightTreeHeight = 0;
    if (offbalanceNode->leftChild == preNode)
    {
        //Recalculate balance factor
        BinaryTreeNode* rightChild = offbalanceNode->rightChild;
        if (rightChild != nullptr)
        {
            BinaryTreeNode* rightrightChild = rightChild->rightChild;
            BinaryTreeNode* rightleftChild = rightChild->leftChild;
            if (rightrightChild != nullptr)
            {
                rightTreeHeight = rightrightChild->treeHeight;
            }
            if (rightleftChild != nullptr)
            {
                leftTreeHeight = rightleftChild->treeHeight;
            }
        }

        balanceFactor = rightTreeHeight - leftTreeHeight;

        if (balanceFactor == 0 || balanceFactor == 1)
        {
            rotateLeft(rightChild);
        }
        else if (balanceFactor == -1)
        {
            BinaryTreeNode* rightleftChild = rightChild->leftChild;
            rotateRight(rightleftChild);
            rotateLeft(rightleftChild);
        }
    }
   else if (offbalanceNode->rightChild == preNode)
    {
        //Recalculate balance factor
        BinaryTreeNode* leftChild = offbalanceNode->leftChild;
        if (leftChild != nullptr)
        {
            BinaryTreeNode* leftrightChild = leftChild->rightChild;
            BinaryTreeNode* leftleftChild = leftChild->leftChild;
            if (leftrightChild != nullptr)
            {
                rightTreeHeight = leftrightChild->treeHeight;
            }
            if (leftleftChild != nullptr)
            {
                leftTreeHeight = leftleftChild->treeHeight;
            }
        }

        balanceFactor = rightTreeHeight - leftTreeHeight;

        if (balanceFactor == 0 || balanceFactor == -1)
        {
            rotateRight(leftChild);
        }
        else if (balanceFactor == 1)
        {
            BinaryTreeNode* leftrightChild = leftChild->rightChild;
            rotateLeft(leftrightChild);
            rotateRight(leftrightChild);
        }
    }
}
/*
Find parent or duplicate function is used for tree traversal, and locating a particular node for manipulation or reading. Following the binary search property,
it traverses the tree until finding its object.

@param[in]: The item of the node being searched for.
@return: The node or its parent being searched for.
*/
template <typename DATA_TYPE>
typename BinarySearchTree<DATA_TYPE>::BinaryTreeNode* BinarySearchTree<DATA_TYPE>::findParentOrDuplicate(const DATA_TYPE& item)
{
    BinaryTreeNode* current = root;
    BinaryTreeNode* parent = current;

    while (current)
    {
        parent = current;
        if (!compare(current->nodeValue, item))
            break;
        // Next, decide if we need to go left or right.
        if (compare(current->nodeValue, item) == 1) // Go left
            current = current->leftChild;
        else // Go right. Duplicate is detected in the test of the while
            current = current->rightChild;
    }

    return parent;
}
/*
Right rotate function carries out the algorithm for a right rotation about the node used as a parameter, moving the node up the tree. A conditional accounts for a special
case if the parent of the node rotated is the root.

@param[in]: The node being rotated.
@return: The tree with the nodes rotated to the right.
*/
template <typename TYPE>
void BinarySearchTree<TYPE>::rotateRight(BinaryTreeNode* node)
{
    BinaryTreeNode* parent = node->parent;
    BinaryTreeNode* noderightChild = node->rightChild;

    if (parent != root)
    {
        BinaryTreeNode* grandparent = parent->parent;
        node->parent = grandparent;
        if (grandparent->leftChild == parent)
        {
            grandparent->leftChild = node;
        }
        else
        {
            grandparent->rightChild = node;
        }
        parent->leftChild = noderightChild;
        node->rightChild = parent;
        parent->parent = node;
        if (noderightChild != nullptr)
        {
            noderightChild->parent = parent;
        }
    }
    else
    {
        root = node;
        parent->leftChild = noderightChild;
        node->rightChild = parent;
        node->parent = nullptr;
        parent->parent = node;
        if (noderightChild != nullptr)
        {
            noderightChild->parent = parent;
        }
    }

    parent->treeHeight = getHeight(parent);
    node->treeHeight = getHeight(node);
}
/*
Left rotate function carries out the algorithm for a left rotation about the node used as a parameter, moving the node up the tree. A conditional accounts for a special
case if the parent of the node rotated is the root.

@param[in]: The node being rotated.
@return: The tree with the nodes rotated to the left.
*/
template <typename TYPE>
void BinarySearchTree<TYPE>::rotateLeft(BinaryTreeNode* node)
{
    BinaryTreeNode* parent = node->parent;
    BinaryTreeNode* nodeleftChild = node->leftChild;

    if (parent != root)
    {
        BinaryTreeNode* grandparent = parent->parent;
        node->parent = grandparent;
        if (grandparent->leftChild == parent)
        {
            grandparent->leftChild = node;
        }
        else
        {
            grandparent->rightChild = node;
        }
        parent->rightChild = nodeleftChild;
        node->leftChild = parent;
        parent->parent = node;
        if (nodeleftChild != nullptr)
        {
            nodeleftChild->parent = parent;
        }
    }
    else
    {
        root = node;
        parent->rightChild = nodeleftChild;
        node->leftChild = parent;
        node->parent = nullptr;
        parent->parent = node;
        if (nodeleftChild != nullptr)
        {
            nodeleftChild->parent = parent;
        }
    }

    parent->treeHeight = getHeight(parent);
    node->treeHeight = getHeight(node);
}
/*
Get height function calculates and updates the height of a node in the tree using the equation height = maxheight of two subtrees + 1.

@param[in]: The node needing its height calculated
@return: The height determined by the node's two subtrees.
*/
template <typename DATA_TYPE>
int BinarySearchTree<DATA_TYPE>::getHeight(BinaryTreeNode* node)
{
    BinaryTreeNode* right = node->rightChild;
    BinaryTreeNode* left = node->leftChild;
    int leftTreeHeight = 0;
    int rightTreeHeight = 0;
    if (right != nullptr)
    {
        rightTreeHeight = right->treeHeight;
    }
    if (left != nullptr)
    {
        leftTreeHeight = left->treeHeight;
    }

    if (rightTreeHeight <= leftTreeHeight)
    {
        return (leftTreeHeight + 1);
    }
    else
    {
        return (rightTreeHeight + 1);
    }
}