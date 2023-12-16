/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
	type="";id="";num=0;
}

ExprTreeNode::ExprTreeNode(string t,int v){
  	type=t;id="";num=v;
}

ExprTreeNode::~ExprTreeNode(){
	if(left)
	delete left;
	if(right)
	delete right;
}

