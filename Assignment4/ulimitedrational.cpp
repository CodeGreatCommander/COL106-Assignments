/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
UnlimitedRational::UnlimitedRational(){
	p=new UnlimitedInt(0);q=new UnlimitedInt(1);
}
UnlimitedInt* abs(UnlimitedInt* a){
	int cap=a->get_capacity(),size=a->get_size(),sign=1,*c=new int[cap];
	for(int i=0;i<size;i++)c[i]=a->get_array()[i];
	if(a->get_sign()==0)size=0;
	return new UnlimitedInt(c,cap,sign,size);
}
UnlimitedInt* gcd_copy(UnlimitedInt* a,bool abs=false){
	int cap=a->get_capacity(),size=a->get_size(),sign=abs?1:a->get_sign(),*ar=new int[cap];
	for(int i=0;i<size;i++)ar[i]=a->get_array()[i];
	return new UnlimitedInt(ar,cap,sign,size);
}
UnlimitedInt* gcd(UnlimitedInt* a,UnlimitedInt* b){//make it so that it always receives positive a and b
	if(a->get_sign()==0||b->get_sign()==0)return new UnlimitedInt(0);
	UnlimitedInt *m=UnlimitedInt::mod(a,b);
	if(m->get_sign()==0){
		delete m;return gcd_copy(b);}
	UnlimitedInt *ans=gcd(b,m);
	delete m; 
	if(ans->get_sign()<0){UnlimitedInt* temp=abs(ans);delete ans;ans=temp;}
	return ans;
}
UnlimitedInt* lcm(UnlimitedInt* a,UnlimitedInt* b){
	UnlimitedInt* g=gcd(a,b),*p=UnlimitedInt::mul(a,b),*l=UnlimitedInt::div(p,g);
	delete p;delete g;
	return l;
}
UnlimitedRational::UnlimitedRational(UnlimitedInt*a,UnlimitedInt* b){
	UnlimitedInt* g=gcd(a,b);
	p=UnlimitedInt::div(a,g);q=UnlimitedInt::div(b,g);
	delete g;
}
UnlimitedRational::~UnlimitedRational(){
	delete p;delete q;
}
UnlimitedInt* UnlimitedRational::get_p(){return p;}
UnlimitedInt* UnlimitedRational::get_q(){return q;}
string UnlimitedRational::get_p_str(){return p->to_string();}
string UnlimitedRational::get_q_str(){return q->to_string();}
string UnlimitedRational::get_frac_str(){return get_p_str()+"/"+get_q_str();}
UnlimitedRational* UnlimitedRational::add(UnlimitedRational* a,UnlimitedRational* b){
	if(a->get_q()->get_sign()==0)return new UnlimitedRational(a->get_p(),a->get_q());
	if(b->get_q()->get_sign()==0)return new UnlimitedRational(b->get_p(),b->get_q());
	UnlimitedInt *p1=UnlimitedInt::mul(a->get_p(),b->get_q()),*p2=UnlimitedInt::mul(a->get_q(),b->get_p()),*s=UnlimitedInt::add(p1,p2),*d=UnlimitedInt::mul(a->get_q(),b->get_q());
	delete p1;delete p2;
	return new UnlimitedRational(s,d);	
}
UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* a,UnlimitedRational* b){
	if(a->get_q()->get_sign()==0)return new UnlimitedRational(a->get_p(),a->get_q());
	if(b->get_q()->get_sign()==0)return new UnlimitedRational(b->get_p(),b->get_q());
	UnlimitedInt *p1=UnlimitedInt::mul(a->get_p(),b->get_q()),*p2=UnlimitedInt::mul(a->get_q(),b->get_p()),*s=UnlimitedInt::sub(p1,p2),*d=UnlimitedInt::mul(a->get_q(),b->get_q());
	delete p1;delete p2;
	return new UnlimitedRational(s,d);	
}
UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* a,UnlimitedRational* b){
	if(a->get_q()->get_sign()==0)return new UnlimitedRational(a->get_p(),a->get_q());
	if(b->get_q()->get_sign()==0)return new UnlimitedRational(b->get_p(),b->get_q());
	UnlimitedInt *n=UnlimitedInt::mul(a->get_p(),b->get_p()),*d=UnlimitedInt::mul(a->get_q(),b->get_q());
	return new UnlimitedRational(n,d);
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* a,UnlimitedRational* b){
	if(a->get_q()->get_sign()==0)return new UnlimitedRational(a->get_p(),a->get_q());
	if(b->get_q()->get_sign()==0||b->get_p()->get_sign()==0)return new UnlimitedRational(b->get_q(),b->get_p());
	UnlimitedInt *n=UnlimitedInt::mul(a->get_p(),b->get_q()),*d=UnlimitedInt::mul(a->get_q(),b->get_p());
	return new UnlimitedRational(n,d);
}