#include <iostream>
#include "binary_tree.h"
using std::cout;
using std::cin;

int main() {

    BinaryTree<char> tree;

    tree.AddNode('C');
    tree.AddNode('A');
    tree.AddNode('B');
    tree.AddNode('D');
    tree.AddNode('E');

    tree.BFS();
    cout << '\n';
    tree.LNR();
    cout << '\n';
    tree.LRN();
    cout << '\n';
    tree.NLR();

    return 0;
}