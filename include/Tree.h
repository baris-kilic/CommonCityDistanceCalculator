/* @Author
Student Name: Barış Kılıç
E-mail: kilicb20@itu.edu.tr
Date: 29.12.2021
*/
#include "Node.h"
using namespace std;
#include <string>
#include <iostream>

class Tree {
    private:
        Node* root;

    public:
        Tree(const string& file_name);
        void tree_construct(Node* traversal, string source_city, string destination_city , int duration);
        int get_linecount(const string& file_name);
        void get_prunecount(Node* traversal, bool prune, int &prune_count);
        Node* preorder_search(Node* traversal, string source_city);
        void preorder_search_fordist(Node* traversal, bool prune, int &distance1, int &distance2, int dist, int &control, string source_city);
        void preorder_prune(Node* traversal, Node* prev, bool prune, int &distance, int dist, string source_city);
        string preorder_search_forprune(Node* traversal, bool prune);
        void prune_tree();
        void find_meetingpoint(Node* root2);
        void preorder_search_formeeting(Node* traversal, Node* root2, string temp_meeting, string &meeting_point, int &distance, int dist);
        void preorder_calculatedist(Node* traversal, string meeting_point, int &distance, int dist);
        void preorder_print(Node* traversal);
        Node* get_root();
};
