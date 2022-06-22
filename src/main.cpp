/* @Author
Student Name: Barış Kılıç
Student ID: 150200111
E-mail: kilicb20@itu.edu.tr
Date: 29.12.2021
*/
#include <iostream>
#include <fstream>
#include "Tree.h"

using namespace std; 

int main(int argc, char* argv[])
{
    Tree friend1_tree(argv[1]);
    Tree friend2_tree(argv[2]);
    friend1_tree.prune_tree();
    friend2_tree.prune_tree();
    friend1_tree.find_meetingpoint(friend2_tree.get_root());
    return EXIT_SUCCESS;
}