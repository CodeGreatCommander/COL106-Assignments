// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
//declaration
struct Node;
struct AVLNode;
class AVLTree;
class Trie;
//Node definition
struct Node{
	AVLTree* children;
	string word,pres_word;//pres_word stores word from root
	int word_count;
	Node* par=nullptr;
	Node();
	Node(string word);
	Node(string word,string past);
    ~Node(){}//TODO:check memory leaks
	Node* get_child(char c);
	void set_child(char c,Node* i);
};

//AVLNode tree definition
struct AVLNode{
    Node* next;
    char c;
    AVLNode* left=nullptr;
    AVLNode* right=nullptr;
    int height=0;
    AVLNode(char c,Node* next):next(next),c(c){}
    ~AVLNode(){if(left)delete left;if(right)delete right;delete next;}
};

//AVL tree declaration
class AVLTree{
private:
    AVLNode* root;
    int height(AVLNode* i);
    AVLNode* recur(Node* i,char c,AVLNode* r);
    AVLNode* rotate_left(AVLNode* i);
    AVLNode* rotate_right(AVLNode* i);
    void addALL(vector<Node*>& st,AVLNode* i);
public:
    AVLTree():root(nullptr){}
    void insert(Node* i,char c);
    Node* find(char c);
    ~AVLTree(){if(root)delete root;}
    void addALL(vector<Node*>& st);
};

//Trie definition
class Trie{
private:
	Node* root;
public:
	Trie();
	void insert(string word);
	int get_count(string word);
	void write_to_file(string filename);
	~Trie();
};
class Dict {
private:
    // You can add attributes/helper functions here
    Trie* t;
public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};