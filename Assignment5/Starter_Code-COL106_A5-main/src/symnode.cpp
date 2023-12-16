/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
	key="";height=0;
}

SymNode::SymNode(string k){
	key=k;height=0;
}

inline int get_h(SymNode* x){
	if(!x)return -1;
	else return x->height;
}
inline int max(int a,int b){
	return a>b?a:b;
}
void update_height(SymNode* x){
	x->height=max(get_h(x->left),get_h(x->right))+1;
}
SymNode* SymNode::LeftLeftRotation(){
	if(!left)return this;
	SymNode* temp=left;
	this->left=temp->right;
	if(this->left)
    this->left->par=this;
	temp->right=this;
	temp->par=this->par;
	this->par=temp;
	if(temp->par){
		if(temp->par->left==this)temp->par->left=temp;
		else temp->par->right=temp;
	}
	update_height(this);
	update_height(temp);
	return temp;
}

SymNode* SymNode::RightRightRotation(){
	if(!right)return this;
       	SymNode* temp=right;
	this->right=temp->left;
	if(this->right)
    this->right->par=this;
	temp->left=this;
	temp->par=this->par;
	this->par=temp;
	if(temp->par){
		if(temp->par->left==this)temp->par->left=temp;
		else temp->par->right=temp;
	}
	update_height(this);
	update_height(temp);
	return temp;
}

SymNode* SymNode::LeftRightRotation(){
	if(!left)return this;
	left=left->RightRightRotation();
	return this->LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation(){
	if(!right)return this;
	right=right->LeftLeftRotation();
	return this->RightRightRotation();
}

SymNode::~SymNode(){
	
}
