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
Node::Node():children(new AVLTree()),word(""),word_count(0),pres_word(""){}
Node::Node(string word):children(new AVLTree()),word(word),word_count(0),pres_word(""){}
Node::Node(string word,string past):children(new AVLTree()),word(word),word_count(0),pres_word(past){}
Node* Node::get_child(char c){
		return children->find(c);
}
void Node::set_child(char c,Node* i){
		children->insert(i,c);
}
//AVL tree implementation
int AVLTree::height(AVLNode* i){
	if(!i)return -1;
	return i->height;
}
AVLNode* AVLTree::rotate_left(AVLNode* i){
	AVLNode* j=i->left;
	i->left=j->right;
	j->right=i;
	i->height=max(height(i->left),height(i->right))+1;
	j->height=max(height(j->left),height(j->right))+1;
	return j;
}
AVLNode* AVLTree::rotate_right(AVLNode* i){
	AVLNode* j=i->right;
	i->right=j->left;
	j->left=i;
	i->height=max(height(i->left),height(i->right))+1;
	j->height=max(height(j->left),height(j->right))+1;
	return j;
}
AVLNode* AVLTree::recur(Node* i,char c,AVLNode* r){
	if(!r){
		return new AVLNode(c,i);
	}
	if(r->c>c)r->left=recur(i,c,r->left);
	else if(r->c<c)r->right=recur(i,c,r->right);
	else r->next=i;//TODO:check memorey leaks
	int l=height(r->left),rr=height(r->right);
	r->height=max(l,rr)+1;
	if(abs(l-rr)>1){
		if(l>rr){
			if(height(r->left->left)>height(r->left->right))r=rotate_left(r);
			else{
				r->left=rotate_right(r->left);
				r=rotate_left(r);
			}
		}
		else{
			if(height(r->right->right)>height(r->right->left))r=rotate_right(r);
			else{
				r->right=rotate_left(r->right);
				r=rotate_right(r);
			}
		}
	}
	return r;
}
void AVLTree::insert(Node* i,char c){
	root=recur(i,c,root);
}
Node* AVLTree::find(char c){
	AVLNode* i=root;
	while(i){
		if(i->c>c)i=i->left;
		else if(i->c<c)i=i->right;
		else return i->next;
	}
	return nullptr;
}
void AVLTree::addALL(vector<Node*>& st,AVLNode* i){
	if(!i)return;
	if(i->next)st.push_back(i->next);
	addALL(st,i->left);
	addALL(st,i->right);
}
void AVLTree::addALL(vector<Node*>& st){
	addALL(st,root);
}

//Trie implementation,Note this is a radix trie
Trie::Trie(){
	root=new Node();
}
void Trie::insert(string word){
    if(word.size()==0)return;
	if(!root->get_child(word[0])){
		root->set_child(word[0],new Node(word,word));
		root->get_child(word[0])->par=root;
		root->get_child(word[0])->word_count++;
		return;
	}
	int c=0,l=word.size();
	Node* i=root->get_child(word[c]);
	while(c<l){
		int j=0;
		for(j=0;c<l&&j<i->word.size()&&word[c]==i->word[j];j++,c++);
		if(j<i->word.size()){//improve complexity of substr
			Node* temp=new Node(i->word.substr(0,j),i->par->pres_word+i->word.substr(0,j));
			temp->par=i->par;
            temp->par->set_child(i->word[0],temp);
            i->word=i->word.substr(j);
			temp->set_child(i->word[0],i);
			i->par=temp;
			i=temp;
		}
		if(c==l)break;
		if(!i->get_child(word[c])){i->set_child(word[c],new Node(word.substr(c),word));i->get_child(word[c])->par=i;i=i->get_child(word[c]);break;}
		else i=i->get_child(word[c]);
	}
	i->word_count++;
}
int Trie::get_count(string word){
	int c=0;Node* i=root;
	while(c<word.size()){
        if(!i)return 0;
		for(int j=0;j<i->word.size();j++,c++)if(c==word.size()||word[c]!=i->word[j])return 0;
        if(c==word.size())break;
		i=i->get_child(word[c]);
	}
    if(!i)return 0;
	return i->word_count;
}
void Trie::write_to_file(string filename){
    fstream file;
    file.open(filename,ios::out);
    if(!file.is_open())return;
    vector<Node*> stack;
    stack.push_back(root);
    while(!stack.empty()){
        Node* i=stack.back();
        stack.pop_back();
        if(i->word_count)file<<i->pres_word<<", "<<i->word_count<<endl;
        // for(int j=0;j<36;j++)if(i->children[j])stack.push_back(i->children[j]);
		i->children->addALL(stack);
    }
    file.close();
}
Trie::~Trie(){
	delete root;
}

//Dict Implementation
Dict::Dict(){
    // Implement your function here    
    t=new Trie();
}

Dict::~Dict(){
    // Implement your function here
    delete t;    
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    	string ans="";
      	for (int i=0,l=sentence.size();i<l;i++){
            string x=" .,-:!\"\'()?—[]“”‘’˙;@";
            if(x.find(sentence[i])!=string::npos){
                if(ans.size()!=0)
				t->insert(ans);
				ans="";	
            }
	    else ans+=sentence[i]>='A'&&sentence[i]<='Z'?(char)(sentence[i]-'A'+'a'):sentence[i];//check complexity and handle upper case number issues
        }
	if(ans.size()!=0)
	t->insert(ans);
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here  
 	
    return t->get_count(word);
}

void Dict::dump_dictionary(string filename){
    // Implement your function here
   	t->write_to_file(filename);  
    return;
}

#include<fstream>
int main(){
    Dict d;
    fstream file;
    file.open("mahatma-gandhi-collected-works-volume-1.txt",ios::in);
    if(!file.is_open())return 1;
    for(int i=0;i<10000;i++){
        string s;
        getline(file,s);
        s=s.substr(s.find_first_of(')')+1);
        d.insert_sentence(1,1,1,1,s);
    }
    cout<<d.get_word_count("the")<<endl;
    file.close();
    cout<<"mission accomplished"<<endl;
    d.dump_dictionary("dict.txt");
    cout<<"fails here"<<endl;
    return 0;

}