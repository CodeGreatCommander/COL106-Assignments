/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
	
}
int get_height(SymNode* x){
	if(!x)return -1;
	else return x->height;
}
SymNode* balance(SymNode* root){
	if(!root)return root;
	int l=get_height(root->left),r=get_height(root->right);
	root->height=max(l,r)+1;
	if(l-r<2&&l-r>-2)return root;
	if(l-r>=2&&get_height(root->left->left)>=get_height(root->left->right))return root->LeftLeftRotation();
	else if(l-r>=2)return root->LeftRightRotation();
	else if(l-r<-1&&get_height(root->right->right)>=get_height(root->right->left))return root->RightRightRotation();
	else return root->RightLeftRotation();
}
SymNode* find(SymNode* root,string k){
	SymNode* i=root;
	while(i){
		if(i->key==k)break;
		else if(i->key<k){
			if(!i->right)break;
			i=i->right;
		}
		else {
			if(!i->left)break;
			i=i->left;
		}
	}
	return i;
}
void SymbolTable::insert(string k){
	if(!root){root=new SymNode(k);size++;return;}
	SymNode* i=find(root,k);
	if(i->key==k)return;
	else if(i->key<k){i->right=new SymNode(k);i->right->par=i;}
	else{i->left=new SymNode(k);i->left->par=i;}
	size++;
	while(i){
		i=balance(i);
		root=i;
		i=i->par;
	}
}
SymNode* getSuccessor(SymNode* root){
	if(!root->right)return root;
	SymNode* i=root->right;
	while(i->left)i=i->left;
	return i;
}
void SymbolTable::remove(string k){
	SymNode* i=find(root,k);
	if(!i||i->key!=k)return;
	size--;
	if(i->right&&i->left){
		SymNode* temp=getSuccessor(i);
		//just check what to do with address
		i->key=temp->key;
		i->address=temp->address;
		i=temp;
	}
	if(!i->par){
        if(i->left){
            SymNode* t=root;
            root=i->left;
            root->par=NULL;
            delete t;
            return;
        }
        else if(i->right){
            SymNode* t=root;
            root=i->right;
            root->par=NULL;
            delete t;
            return;
        }
        else{
            delete root;
            root=NULL;
            return;
        }
    }
    else if(!i->right){
        if(i->par->left==i){
            i->par->left=i->left;
        }
        else{
            i->par->right=i->left;
        }
        if(i->left)
        i->left->par=i->par;
    }
    else{
        if(i->par->left==i){
        i->par->left=i->right;
        }
        else{
        i->par->right=i->right;
        }
        if(i->right)
        i->right->par=i->par;
    }
	SymNode* temp=i->par;
	delete i;
	i=temp;
	while(i){
		i=balance(i);
		root=i;
		i=i->par;
	}
}

int SymbolTable::search(string k){
	SymNode* i=find(root,k);
	if(i->key==k)return i->address;
	return -2;
}

void SymbolTable::assign_address(string k,int idx){
	SymNode* i=find(root,k);
	if(i&&i->key==k)
	i->address=idx;
}

int SymbolTable::get_size(){
	return size;
}

SymNode* SymbolTable::get_root(){
	return root;
}
void clear(SymNode* r){
	if(!r)return;
	clear(r->right);clear(r->left);
	delete r;
}
SymbolTable::~SymbolTable(){
	clear(root);	
}

