/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
	symtable=new SymbolTable();
	last_deleted=-1;
}
bool is_number(string s){
	for(int i=0;i<s.length();i++){
		if((s[i]<'0'||s[i]>'9')&&s[i]!='+'&&s[i]!='-')return false;
	}
	return true;
}
ExprTreeNode* par(vector<string>&code,int&i){
	if(code[i]!="("&&is_number(code[i])){
		ExprTreeNode* t=new ExprTreeNode("VAL",stoi(code[i++]));
		return t;
	}
	else if(code[i]!="("){
		ExprTreeNode* t=new ExprTreeNode("VAR",0);
		t->id=code[i++];
		return t;
	}
	else{
		ExprTreeNode* l=par(code,++i);
		if(code[i]==")"){i++;return l;}
		ExprTreeNode* r=nullptr;
		if(code[i]=="+")r=new ExprTreeNode("ADD",0);
		else if(code[i]=="-")r=new ExprTreeNode("SUB",0);
		else if(code[i]=="*")r=new ExprTreeNode("MUL",0);
		else if(code[i]=="/")r=new ExprTreeNode("DIV",0);
		else r=new ExprTreeNode("MOD",0);
		r->left=l;i++;
		r->right=par(code,i);
		i++;
		return r;
	}
}
void Parser::parse(vector<string> expression){
	int i=2;
    ExprTreeNode* right=par(expression,i),*n=new ExprTreeNode(":=",0),*left=nullptr;
    if(expression[0]=="del"){left=new ExprTreeNode("DEL",0);last_deleted=symtable->search(expression[2]);symtable->remove(expression[2]);}//Check I am using search
    else if(expression[0]=="ret")left=new ExprTreeNode("RET",0);
    else{ left=new ExprTreeNode("VAR",0);left->id=expression[0];symtable->insert(expression[0]);}
    n->left=left;n->right=right;
    expr_trees.push_back(n);
}

Parser::~Parser(){
  delete symtable;
  for(int i=0;i<expr_trees.size();i++)delete expr_trees[i];
}
