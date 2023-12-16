/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator():symtable(new SymbolTable()){}
Evaluator::~Evaluator(){
	delete symtable;
}
bool is_number(string s){
	for(int i=0;i<s.length();i++){
		if((s[i]<'0'||s[i]>'9')&&s[i]!='+'&&s[i]!='-')return false;
	}
	return true;
}
ExprTreeNode* par(vector<string>&code,int&i){
	if(code[i]!="("&&is_number(code[i])){
		ExprTreeNode* t=new ExprTreeNode("VAL",new UnlimitedInt(code[i++]));
		return t;
	}
	else if(code[i]!="("){
		ExprTreeNode* t=new ExprTreeNode("VAR",new UnlimitedInt(0));
		t->id=code[i++];
		return t;
	}
	else{
		ExprTreeNode* l=par(code,++i);
		if(code[i]==")"){i++;return l;}
		ExprTreeNode* r=nullptr;
		if(code[i]=="+")r=new ExprTreeNode("ADD",new UnlimitedInt(0));
		else if(code[i]=="-")r=new ExprTreeNode("SUB",new UnlimitedInt(0));
		else if(code[i]=="*")r=new ExprTreeNode("MUL",new UnlimitedInt(0));
		else if(code[i]=="/")r=new ExprTreeNode("DIV",new UnlimitedInt(0));
		else r=new ExprTreeNode("MOD",new UnlimitedInt(0));
		r->left=l;i++;
		r->right=par(code,i);
		i++;
		return r;
	}
}

void Evaluator::parse(vector<string>code){
	ExprTreeNode* v=new ExprTreeNode("VAR",new UnlimitedInt(0)),*i=new ExprTreeNode("VAR",new UnlimitedInt(0));
	v->id=code[0];int ir=2;
	i->left=v;i->right=par(code,ir);
	expr_trees.push_back(i);
}
void evaluat(ExprTreeNode* r,SymbolTable* s){
	if(!r)return;
	evaluat(r->left,s);
	evaluat(r->right,s);
	if(r->type=="VAL")r->evaluated_value=r->val;
	else if(r->type=="VAR"){r->evaluated_value=s->search(r->id);}
	else if(r->type=="ADD")r->evaluated_value=UnlimitedRational::add(r->left->evaluated_value,r->right->evaluated_value);
	else if(r->type=="SUB")r->evaluated_value=UnlimitedRational::sub(r->left->evaluated_value,r->right->evaluated_value);
	else if(r->type=="MUL")r->evaluated_value=UnlimitedRational::mul(r->left->evaluated_value,r->right->evaluated_value);
	else if(r->type=="DIV")r->evaluated_value=UnlimitedRational::div(r->left->evaluated_value,r->right->evaluated_value);
	else r->evaluated_value=new UnlimitedRational(UnlimitedInt::mod(r->left->evaluated_value->get_p(),r->right->evaluated_value->get_p()),new UnlimitedInt(1));
	return;
}	

void Evaluator::eval(){
	ExprTreeNode* r=expr_trees.back();
	evaluat(r->right,symtable);

	symtable->insert(r->left->id,r->right->evaluated_value);
}
	
