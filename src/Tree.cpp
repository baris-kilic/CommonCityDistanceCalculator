/* @Author
Name: Barış Kılıç
E-mail: kilicb20@itu.edu.tr
Date: 29.12.2021
*/
#include "Tree.h"
#include <iostream>
#include <fstream>

using namespace std;

int Tree::get_linecount(const string& file_name){
    int count = 0;
    ifstream in(file_name);
    std::string str;
    while (std::getline(in, str))
        ++count;
    return count;
}

Node* Tree::get_root(){
    return this->root;
};

Tree::Tree(const string& file_name){
    this->root = NULL;
    ifstream city_file (file_name);
    string sourcecity, destinationcity;
    int duration = 0;
    if (city_file.is_open())
    {
        for (int i = 0; i < get_linecount(file_name); i++)
        {
            city_file >> sourcecity >> destinationcity >> duration;
            Node* traversal = root;
            tree_construct(traversal,sourcecity,destinationcity,duration); 
        }   
    }
}

Node* Tree::preorder_search(Node* traversal, string source_city){
    Node* p = NULL;
    if (traversal == NULL)
        return NULL;
    if (traversal->get_name() == source_city)
        return traversal;
    p = preorder_search(traversal->get_left(), source_city);
    if (p == NULL)
        p = preorder_search(traversal->get_right(), source_city);
    return p;   
}

void Tree::tree_construct(Node* traversal, string source_city, string destination_city , int duration){
    if (traversal == NULL)
    {
        Node* newnode = new Node(0,source_city);
        root = newnode;
        traversal = root;
    }
    if (preorder_search(traversal,destination_city) != NULL)
    {
        Node* newnode = preorder_search(traversal,destination_city);
        traversal = preorder_search(traversal, source_city);
        if (traversal->get_left() == NULL)
        {
            traversal->set_left(newnode);
            traversal->get_left()->set_dist2(duration);
            traversal->get_left()->set_prune(true);
            return;
        }
        if (traversal->get_right() == NULL)
        {
            traversal->set_right(newnode);
            traversal->get_right()->set_dist2(duration);
            traversal->get_right()->set_prune(true);
            return;
        }        
    }    
    if (traversal->get_left() == NULL && traversal->get_name() == source_city)
    {
        Node* newnode = new Node(duration,destination_city);
        traversal->set_left(newnode);
        return;
    }
    if (traversal->get_right() == NULL && traversal->get_name() == source_city)
    {
        Node* newnode = new Node(duration,destination_city);
        traversal->set_right(newnode);
        return;
    }
    else
        tree_construct(preorder_search(traversal, source_city),source_city,destination_city,duration);
}

string Tree::preorder_search_forprune(Node* traversal, bool prune){
    string s = "";
    if (traversal == NULL)
        return "";
    if (traversal->get_prune() == prune)
        return traversal->get_name();
    s = preorder_search_forprune(traversal->get_left(), prune);
    if (s == "")
        s = preorder_search_forprune(traversal->get_right(), prune);
    return s;     
}

void Tree::get_prunecount(Node* traversal, bool prune, int &prune_count){
    if (traversal == NULL)
        return;
    if (traversal->get_prune() == prune){
        prune_count++;
        return;
    }   
    get_prunecount(traversal->get_left(),prune,prune_count);
    get_prunecount(traversal->get_right(),prune,prune_count); 
};

void Tree::preorder_search_fordist(Node* traversal, bool prune, int &distance1, int &distance2, int dist, int &control, string source_city){
    if (traversal == NULL)
        return;
    if (distance1 != 0 && distance2 != 0)
        return;    
    if (traversal->get_prune() == prune && control == 0 && traversal->get_name() == source_city)
    {
        distance1 = traversal->get_dist1() + dist;
        control++;
        return;
    }
    if (traversal->get_prune() == prune && control == 1 && traversal->get_name() == source_city)
    {
        distance2 = traversal->get_dist2() + dist;
        return;
    }      
    preorder_search_fordist(traversal->get_left(), prune, distance1, distance2, dist + traversal->get_dist1(), control, source_city);
    preorder_search_fordist(traversal->get_right(), prune, distance1, distance2, dist + traversal->get_dist1(), control, source_city); 
}

void Tree::preorder_prune(Node* traversal, Node* prev, bool prune, int &distance, int dist, string source_city){
    if (traversal == NULL)
        return;
    if (traversal->get_prune() == prune && distance == traversal->get_dist1() + dist && traversal->get_name() == source_city)
    {
        if (prev->get_left() == traversal)
        {
            prev->get_left()->set_dist1(traversal->get_dist2());
            prev->get_left()->set_dist2(0);
            prev->get_left()->set_prune(false);
            prev->set_left(NULL);
            return;
        }
        if (prev->get_right() == traversal)
        {
            prev->get_right()->set_dist1(traversal->get_dist2());
            prev->get_right()->set_dist2(0);
            prev->get_right()->set_prune(false);
            prev->set_right(NULL);
            return;
        }        
    }
    else if (traversal->get_prune() == prune && distance == traversal->get_dist2() + dist && traversal->get_name() == source_city)
    {
        if (prev->get_left() == traversal)
        {
            prev->get_left()->set_dist2(0);
            prev->get_left()->set_prune(false);
            prev->set_left(NULL);
            return;
        }
        if (prev->get_right() == traversal)
        {
            prev->get_right()->set_dist2(0);
            prev->get_right()->set_prune(false);
            prev->set_right(NULL);
            return;
        }
    }
    prev = traversal;
    preorder_prune(traversal->get_left(), prev, prune, distance, dist + prev->get_dist1(), source_city);
    prev = traversal;  
    preorder_prune(traversal->get_right(), prev, prune, distance, dist + prev->get_dist1(), source_city);                
}

void Tree::prune_tree(){
    int prune_count = 0;
    get_prunecount(root, true, prune_count);
    for (int i = 0; i < prune_count - 1; i++)
    {
        int dist = 0, distance1 = 0, distance2 = 0, control = 0;
        string sourcecity = preorder_search_forprune(root, true);
        preorder_search_fordist(root, true, distance1, distance2, dist, control, sourcecity);
        dist = 0;
        Node* prev = root;
        if (distance1 > distance2)
        {
            preorder_prune(root, prev, true, distance1, dist, sourcecity);
        }
        else if (distance2 > distance1)
        {
            preorder_prune(root, prev, true, distance2, dist, sourcecity);
        }
    }
}

void Tree::preorder_calculatedist(Node* traversal, string meeting_point, int &distance, int dist){
    if (traversal == NULL)
        return;
    if (traversal->get_name() == meeting_point){
        distance = traversal->get_dist1() + dist;
        return;
    }
    preorder_calculatedist(traversal->get_left(), meeting_point, distance, dist + traversal->get_dist1());
    preorder_calculatedist(traversal->get_right(), meeting_point, distance, dist + traversal->get_dist1());
};

void Tree::preorder_search_formeeting(Node* traversal, Node* root2, string temp_meeting, string &meeting_point, int &distance, int dist){
    if (traversal == NULL)
        return;
    temp_meeting = traversal->get_name();
    dist += traversal->get_dist1();
    if (preorder_search(root2,temp_meeting) != NULL){
        int dist2 = 0, distance2 = 0;
        preorder_calculatedist(root2, temp_meeting, distance2, dist2);
        if (dist + distance2 < distance){
            distance = dist + distance2;
            meeting_point = temp_meeting;
        }
    }
    preorder_search_formeeting(traversal->get_left(), root2, temp_meeting, meeting_point, distance, dist);
    preorder_search_formeeting(traversal->get_right(), root2, temp_meeting, meeting_point, distance, dist);
};

void Tree::preorder_print(Node* traversal){
    if (traversal == NULL)
        return;
    cout << traversal->get_name() << " ";
    preorder_print(traversal->get_left());
    preorder_print(traversal->get_right());
};

void Tree::find_meetingpoint(Node* root2){
    int distance = INT16_MAX;
    int dist = 0;
    string temp_meeting, meeting_point;
    preorder_search_formeeting(root, root2, temp_meeting, meeting_point, distance, dist);
    cout << "FRIEND-1: ";
    preorder_print(root);
    cout << endl << "FRIEND-2: ";
    preorder_print(root2);
    cout << endl << "MEETING POINT: " << meeting_point << endl;
    cout << "TOTAL DURATION COST: " << distance;
};
