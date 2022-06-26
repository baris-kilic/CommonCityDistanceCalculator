/* @Author
Name: Barış Kılıç
E-mail: kilicb20@itu.edu.tr
Date: 29.12.2021
*/
#include "Node.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

Node::Node(int dist1, string name){
    this->dist1 = dist1;
    this->dist2 = 0;
    this->name = name;
    this->left=NULL;
    this->right=NULL;
    this->prune=false;
}

void Node::set_left(Node* left){
    this->left = left;
}

void Node::set_right(Node* right){
    this->right = right;
}

void Node::set_dist1(int dist1){
    this->dist1 =dist1;
}

void Node::set_dist2(int dist2){
    this->dist2 = dist2;
}

void Node::set_name(string name){
    this->name = name;
}

void Node::set_prune(bool prune){
    this->prune = prune;
}

Node* Node::get_left(){
    return this->left;
}

Node* Node::get_right(){
    return this->right;
}

string Node::get_name(){
    return this->name;
}

int Node::get_dist1(){
    return this->dist1;
}

int Node::get_dist2(){
    return this->dist2;
}

bool Node::get_prune(){
    return this->prune;
}
