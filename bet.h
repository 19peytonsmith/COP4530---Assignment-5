#ifndef TREE5_BET_H
#define TREE5_BET_H
#include <iostream>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;

class BET
{
public:
    BET();
    BET(const string& postfix);
    BET(const BET&);
    ~BET();
    bool buildFromPostfix(const string& postfix);
    const BET & operator= (const BET &);
    void printInfixExpression();
    void printPostfixExpression();
    size_t size();
    size_t leaf_nodes();
    bool empty();

private:
    struct BinaryNode{
        string element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const string & theElement = string{}, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr) : element{theElement}, left{lt}, right{rt} {}
    };

    BinaryNode *root;

    void printInfixExpression(BinaryNode *n);
    void makeEmpty(BinaryNode* &t);
    BinaryNode * clone(BinaryNode *t);
    void printPostfixExpression(BinaryNode *n);
    size_t size(BinaryNode *t);
    size_t leaf_nodes(BinaryNode *t);

};

#include "bet.hpp"
#endif //TREE5_BET_H
