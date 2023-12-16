/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
	memory_size=0;
	output_file="";
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
	memory_size=mem_limit;
	output_file=out_file;
	for(int i=0;i<mem_limit;i++)least_mem_loc.push_heap(i);
}

void EPPCompiler::compile(vector<vector<string>> code){
	for(int i=0;i<code.size();i++){
		targ.parse(code[i]);
		if(code[i][0]=="del"){
			least_mem_loc.push_heap(targ.last_deleted);	
		}
		else if(code[i][0]!="ret"){
			targ.symtable->assign_address(code[i][0],least_mem_loc.get_min());
			least_mem_loc.pop();
		}
		write_to_file(generate_targ_commands());
	}
}
void gen(vector<string>& comm,ExprTreeNode* root,Parser& targ){
	if(!root)return;
	gen(comm,root->right,targ);
	gen(comm,root->left,targ);
	if(root->type=="VAL")comm.push_back("PUSH "+to_string(root->num));
	else if(root->type=="VAR")comm.push_back("PUSH mem["+to_string(targ.symtable->search(root->id))+"]");
	else if(root->type=="ADD"||root->type=="MUL"||root->type=="SUB"||root->type=="DIV")comm.push_back(root->type);
}
vector<string> EPPCompiler::generate_targ_commands(){
	ExprTreeNode* a=targ.expr_trees.back();
	vector<string> comm;
	if(a->left->type=="DEL")comm.push_back("DEL = mem["+to_string(targ.last_deleted)+"]");
	else if(a->left->type=="RET"){
		gen(comm,a->right,targ);comm.push_back("RET = POP");
	}
	else{
		gen(comm,a->right,targ);comm.push_back("mem["+to_string(targ.symtable->search(a->left->id))+"] = POP");
	}
	return comm;	
}

void EPPCompiler::write_to_file(vector<string> commands){
	fstream file;file.open(output_file,ios::out | ios::app);
	for(int i=0;i<commands.size();i++)
	file<<commands[i]<<endl;
	file.close();
}

EPPCompiler::~EPPCompiler(){
	
}
