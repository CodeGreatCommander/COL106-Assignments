#include <string>
using namespace std;

class HeapNode{
  public:
  int val;
  HeapNode* par = NULL;
  HeapNode* left = NULL;
  HeapNode* right = NULL;
  
  HeapNode();
  HeapNode(int _val);
  
  ~HeapNode();
};
class MinHeap{
  private:
  int size = 0;
  HeapNode* root = NULL;
  
  public:
  MinHeap();
  ~MinHeap();

  void push_heap(int num); // Insert num into the heap
  int get_min(); // Returns min of the heap (which must be at root)
  void pop(); // Deletes the min element from the heap
};
HeapNode::HeapNode(){
	val=-1;
}

HeapNode::HeapNode(int _val){
	val=_val;
}

HeapNode::~HeapNode(){
  
}
MinHeap::MinHeap(){
	
}

string binary(int x){
	string bi="";
	while(x!=0){
		bi=(char)('0'+x%2)+bi;
		x/=2;
	}
	return bi;
}
int swap(int&a,int&b){
	a=a^b;b=a^b;a=a^b;
}
void MinHeap::push_heap(int num){
	if(!root){size++;root=new HeapNode(num);return;}
	size++;
	string s=binary(size);
	HeapNode* i=root;
	for(int j=1;j!=s.size()-1;j++){
		if(s[j]=='1')i=i->right;
		else i=i->left;
	}
	if(s[s.size()-1]=='0'){i->left=new HeapNode(num);i->left->par=i;i=i->left;}
	else {i->right=new HeapNode(num);i->right->par=i;i=i->right;}
	while(i->par){
		if(i->par->val>i->val){
			swap(i->par->val,i->val);
			i=i->par;
		}
		else break;
	}
}

int MinHeap::get_min(){
	if(!root)return -1;
	else return root->val;
}

void MinHeap::pop(){
	if(!root||size==0)return;
    if(size==1){delete root;root=NULL;size--;return;}
	string s=binary(size);
	HeapNode* i=root;
	for(int j=1;j!=s.size()-1;j++){
		if(s[j]=='1')i=i->right;
		else i=i->left;
	}
	if(s[s.size()-1]=='1'){swap(root->val,i->right->val);delete i->right;i->right=NULL;size--;}
	else {swap(root->val,i->left->val);delete i->left;i->left=NULL;size--;}
	i=root;
	while(i->left){
		if(!i->right){
			if(i->val<i->left->val)break;
			else{swap(i->val,i->left->val);i=i->left;}
		}
		else{
			if(i->left->val<i->right->val){
				if(i->left->val>i->val)break;
				else{swap(i->val,i->left->val);i=i->left;}
			}
			else{
				if(i->right->val>i->val)break;
				else {swap(i->val,i->right->val);i=i->right;}
			}
		}	
	}
}
void delHeap(HeapNode* n){
	if(!n)return;
	delHeap(n->left);
	delHeap(n->right);
	delete n;
}
MinHeap::~MinHeap(){
	delHeap(root);
}	
#include <iostream>
int main(){
    MinHeap h;
    h.push_heap(6);
    h.push_heap(5);
    cout<<h.get_min()<<endl;
}