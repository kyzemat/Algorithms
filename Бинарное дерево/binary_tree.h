#pragma once

#include <iostream>
#include <unordered_map>
#include <queue>
using std::cout;
using std::unordered_map;
using std::queue;


template <typename T>
struct Node
{
    T data;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(const T &var) : data(var){}
};

template <typename T>
class BinaryTree {
    Node<T>* root = nullptr;
    
public:

    BinaryTree() = default;

    explicit BinaryTree(const T &var) {
        root = new Node<T>(var);
    }

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;
    
    ~BinaryTree() {
        clear(root);
    }

    void AddNode(const T &var) {
        Add(root, var);
    }

    void BFS() {
        Node<T>* node = nullptr; 
        queue<Node<T>*> active;
        unordered_map<Node<T>*, bool> searched;

        active.push(root);

        while(active.size()){
            node = active.front();
            active.pop();

            cout << node->data << ' ';
            if(node->left)
                active.push(node->left);
            if(node->right)
                active.push(node->right);
        }   
    }

    void NLR() {
        nlr(root);
    }

    void LNR() {
        lnr(root);
    }

    void LRN() {
        lrn(root);
    }

private:

    void clear(Node<T>* node) {
        if(!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void Add(Node<T>*& node, const T &var) {
        if(!node){
            node = new Node<T>(var);
            return;
        }
        if(var > node->data)
            Add(node->right, var);
        else 
            Add(node->left, var);
    }

    void nlr(Node<T>*& node) {
        if(!node) return;

        cout << node->data << ' ';
        nlr(node->left);
        nlr(node->right);
    }

    void lnr(Node<T>*& node) {
        if(!node) return;
        
        lnr(node->left);
        cout << node->data << ' ';
        lnr(node->right);
    }

    void lrn(Node<T>*& node) {
        if(!node) return;

        lrn(node->left);
        lrn(node->right);
        cout << node->data << ' ';
    }

};