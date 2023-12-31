/**
 * @file main.cpp
 * This file contains code for output testing of the
 *  BinaryTree class.
 * @author Daniel Hoodin, modified by Jack Toole for colored output
 * @date March 2009
 */

#include <algorithm>
#include <iostream>
#include <random>
#include "binarytree.h"
#include "coloredout.h"

using namespace std;

template <typename T>
void printTreeInfo(const BinaryTree<T>& tree, const string& name,
                   const string& description);

template <typename T>
void shuffle(vector<T>& vec, mt19937 rng) {
    for (int i = vec.size() - 1; i > 0; i--) {
        swap(vec[i], vec[rng() % (i + 1)]);
    }
}

int main(int argc, char** argv)
{
    // Color the output
    bool is_colored
        = (argc > 1 && tolower(argv[1][0]) == 'c') && isatty(STDOUT_FILENO);
    colored_out coloroutput;
    if (is_colored) {
        coloroutput.set_expected_file("soln_treefun.out");
        int status = coloroutput.start();
        if (status < 0)
            return 0;
    }

    // Make a random unsorted tree with nodes for 1 through 10
    BinaryTree<int> myTree;
    vector<int> ordering;
    for (int num = 1; num <= 10; num++)
        ordering.push_back(num);
    shuffle(ordering, mt19937(86));

    for (int i = 0; i < 10; i++) {
        myTree.insert(ordering[i]);
    }

    // Print the tree
    printTreeInfo(myTree, "Tree", "random unordered tree");

    // Mirror the tree
    myTree.mirror();
    printTreeInfo(myTree, "Mirrored", "the mirror image of the above tree");

    ordering.clear();

    // Make a sorted tree
    // First, create a random ordering to insert 1..10 into the tree
    for (int num = 1; num <= 10; num++)
        ordering.push_back(num);
    shuffle(ordering, mt19937(314));

    // Then create a tree and insert 1..10 shuffled
    BinaryTree<int> myBST;
    for (int index = 0; index < 10; index++) {
        myBST.insert(ordering[index], true);
    }

    // Print the tree
    printTreeInfo(myBST, "BST", "random ordered tree");

    // Mirror the tree
    myBST.mirror();
    printTreeInfo(myBST, "BST Mirrored", "the mirror image of the above BST");

    ordering.clear();

    // Make an almost sorted tree
    for (int num = 1; num <= 10; num++)
        ordering.push_back(num);
    shuffle(ordering, mt19937(221221));

    // Then create a tree and insert 1..10 shuffled
    myBST.clear();
    for (int index = 0; index < 4; index++)
        myBST.insert(ordering[index], true);
    myBST.insert(ordering[4]);
    for (int index = 5; index < 10; index++)
        myBST.insert(ordering[index], true);

    printTreeInfo(myBST, "Almost BST",
                  "a tree that has one element out of place");

    return 0;
}

void output_header(string name, string desc)
{
    const string bar(79, '~');
    cout << bar << endl;
    colored_out::output_bold(name);
    cout << " - " << desc << endl;
    cout << bar << endl;
}

template <typename T>
void printTreeInfo(const BinaryTree<T>& tree, const string& name,
                   const string& description)
{
    output_header(name, description);
    cout << "height: " << tree.height() << endl;
    cout << "ordered: " << boolalpha << tree.isOrdered() << endl;
    cout << "sumDistances: " << tree.sumDistances() << endl;
    tree.printLeftToRight();
    cout << endl;
    cout << "printLeftRight: ";
    tree.printLeftToRight();
    tree.printPaths();
    cout << endl << endl;
}
