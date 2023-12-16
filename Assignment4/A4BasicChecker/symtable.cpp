/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
SymbolTable::SymbolTable():root(nullptr),size(0){}
SymbolTable::~SymbolTable(){if(root&&root->left)delete root->left;if(root&&root->right)delete root->right;}
UnlimitedRational* SymbolTable::search(string k){
	SymEntry* i=root;
	while(i){
		if(i->key==k)return i->val;
		else if(i->key<k)i=i->right;
		else i=i->left;
	}
	return nullptr;
}
void update(string k,UnlimitedRational* d,SymEntry* root){
	SymEntry* i=root;
	while(i){
		if(i->key==k){delete i->val;i->val=d;return;}
		else if(i->key<k)i=i->right;
		else i=i->left;
	}
}
SymEntry* ins(string k,UnlimitedRational* d,SymEntry* n){
	if(!n)return new SymEntry(k,d);
	if(n->key<k)n->right=ins(k,d,n->right);
	else n->left=ins(k,d,n->left);
	return n;
}
void SymbolTable::insert(string k,UnlimitedRational* d){
	if(search(k)){update(k,d,root);return;}
	root=ins(k,d,root);
	size++;
}
SymEntry* succeed(string k,SymEntry* n){
	SymEntry* i=n->right;
	while(i->left)i=i->left;
	return i;
}
SymEntry* del(string k,SymEntry* n,int& s){
	if(!n)return nullptr;
	if(n->key==k&&!n->left){SymEntry* x=n->right; delete n;return x;s--;}
	if(n->key==k&&!n->right){SymEntry* x=n->left;delete n;return x;s--;}
	if(n->key==k){
		SymEntry* nex=succeed(k,n);
		n->key=nex->key;n->val=nex->val;
		n->right=del(n->key,n->right,s);
		return n;
	}
	else if(n->key<k){n->right=del(k,n->right,s);return n;}
	else {n->left=del(k,n->left,s);return n;}
}	
void SymbolTable::remove(string k){
	root=del(k,root,size);
}
int SymbolTable::get_size(){return size;}
SymEntry* SymbolTable::get_root(){return root;}
