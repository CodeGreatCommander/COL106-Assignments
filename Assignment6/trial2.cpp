// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
Node::Node() {
}

Node::Node(int b_code, int pg, int para, int s_no, int off){
    book_code = b_code;
    page = pg;
    paragraph = para;
    sentence_no = s_no;
    offset = off;
}
using namespace std;
//TrieNode SC:Optimisation Possible:present_word,children TC:
struct TrieNode{
	vector<TrieNode*> children;
	TrieNode* parent=nullptr;
	char ch;
	string word;
	Node* root=nullptr;
	TrieNode();
	~TrieNode();
	TrieNode* get_child(char c);
	void set_child(char c,TrieNode* i);
};
//Trie SC:
class Trie{
private:
	TrieNode* root;
	Node* make_copy(const Node* root);
	void recur(const string pattern,int pos,TrieNode* root,Node*& ans,int& length);
public:
	Trie();
	~Trie();
	void insert(const string word,const int book_code,const int page,const int paragraph,const int sentence_no,int offset);
	Node* return_LL(const string pattern,int& n_matched);
};
TrieNode::TrieNode():children(vector<TrieNode*>(35,nullptr)),word(""),ch(' '){}
TrieNode::~TrieNode(){
    //clear the root linked list
	Node* i=root;
	while(i){
		Node* temp=i;
		i=i->right;
		delete temp;
	}
	for(TrieNode* a:children)delete a;
}
TrieNode* TrieNode::get_child(char c){
	if(c>='A'&&c<='Z')return children[c-'A'];
	else if(c>='a'&&c<='z')return children[c-'a'];
	else return children[c-'0'+26];
}
void TrieNode::set_child(char c,TrieNode* i){
	if(c>='A'&&c<='Z')children[c-'A']=i;
	else if(c>='a'&&c<='z')children[c-'a']=i;
	else children[c-'0'+26]=i;
}



//Trie Implementation
Trie::Trie(){
	root=new TrieNode();
}
void Trie::insert(const string word,const int book_code,const int page,const int paragraph,const int sentence_no,int offset){
	TrieNode* i=root;
	for(int _=0;_<word.size();_++){
		char c=word[_];
		if(!i->get_child(c)){
			i->set_child(c,new TrieNode());
			i->get_child(c)->parent=i;
			i=i->get_child(c);
			i->ch=c;
			i->word=i->parent->word+c;//TODO:optimise chance
		}
		else{
			i=i->get_child(c);
		}
	}
	Node* temp=new Node(book_code,page,paragraph,sentence_no,offset);
	temp->left=nullptr;
	temp->right=i->root;
	if(i->root)
	i->root->left=temp;
	i->root=temp;
}
Node* Trie::make_copy(const Node* root){
	return new Node(root->book_code,root->page,root->paragraph,root->sentence_no,root->offset);
}
void Trie::recur(const string pattern,int pos,TrieNode* root,Node*& ans,int& length){
	if(pos==pattern.size()||(pos==pattern.size()-1&& pattern[pos]==root->ch)){
		Node* i=root->root;
		while(i){
			Node* temp=make_copy(i);
			temp->right=ans;
			temp->left=nullptr;
			if(ans)ans->left=temp;
			ans=temp;
			i=i->right;
			length++;
		}
		for(TrieNode* x:root->children){
			if(x)recur(pattern,pattern.size(),x,ans,length);
		}
	}
	else if(root->ch==pattern[pos]){
		for(TrieNode* x:root->children){
			if(x)recur(pattern,pos+1,x,ans,length);
		}
	}
	else{
		for(TrieNode* x:root->children){
			if(x)recur(pattern,0,x,ans,length);
		}
	}
}
Node* Trie::return_LL(const string pattern,int& length){
	Node* ans=nullptr;
	for(TrieNode* a:root->children){
		if(a)recur(pattern,0,a,ans,length);
	}
	return ans;
}
Trie::~Trie(){
	delete root;
}

#include<iostream>
using namespace std;
int main(){
    Trie t;
    t.insert("hello",1,2,3,4,5);
    t.insert("hell",2,2,3,4,5);
    t.insert("hella",3,2,3,4,5);
    int x=0;
    Node* a=t.return_LL("hell",x);
    while(a){
        cout<<a->book_code<<" "<<a->page<<" "<<a->paragraph<<" "<<a->sentence_no<<" "<<a->offset<<endl;
        a=a->right;
    }
    return 0;
}