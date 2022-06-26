/* @Author
Student Name: Barış Kılıç
E-mail: kilicb20@itu.edu.tr
Date: 29.12.2021
*/
#include <string>
using namespace std;

class Node {
    private:
        int dist1;
        int dist2;
        string name;
        Node* left;
        Node* right;
        bool prune;

    public:
        Node(int, string);
        void set_left(Node*);
        void set_right(Node*);
        void set_dist1(int);
        void set_dist2(int);
        void set_name(string);
        void set_prune(bool);

        Node* get_left();
        Node* get_right();
        string get_name();
        int get_dist1();
        int get_dist2();
        bool get_prune();
};

