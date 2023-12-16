/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
UnlimitedInt::UnlimitedInt(){
	size=0;sign=0;capacity=5;unlimited_int=new int[capacity];
}
UnlimitedInt::UnlimitedInt(string s){
	capacity=s.size();size=0;unlimited_int=new int[capacity];int i=0;
	for(i=s.size()-1;i>=0&&s[i]>='0'&&s[i]<='9';i--){
		unlimited_int[size++]=s[i]-'0';
	}
	while(size>0&&unlimited_int[size-1]==0)size--;
	if(size==0)sign=0;
	else if(i>=0&&s[i]=='-')sign=-1;
	else sign=1;
}
UnlimitedInt::UnlimitedInt(int n){
	capacity=10;size=0;
	if(n==0)sign=0;
	else if(n>0)sign=1;
	else {sign=-1;n*=-1;}
	unlimited_int=new int[capacity];
	while(n!=0){unlimited_int[size++]=n%10;n/=10;}
}
UnlimitedInt::UnlimitedInt(int* arr,int c,int sgn,int si):unlimited_int(arr),capacity(c),sign(sgn),size(si){}
UnlimitedInt::~UnlimitedInt(){if(unlimited_int) delete unlimited_int;}
int UnlimitedInt::get_size(){if(size==0)return 1;return size;}
int* UnlimitedInt::get_array(){return unlimited_int;}
int UnlimitedInt::get_sign(){return sign;}
int UnlimitedInt::get_capacity(){return capacity;}

int max(int&a,int&b){return a>b?a:b;}

UnlimitedInt* adsub(UnlimitedInt* a,UnlimitedInt* b,bool ad,bool invert){//assuming the absolute value of a is greater than that of b
	int cap=a->get_size()+2,size=0,sign=a->get_sign();
	if(invert)sign*=-1;
	int *ar=a->get_array(),*br=b->get_array(),*cr=new int[cap];
	int c=0;
	for(int i=0;i<b->get_size();i++){//a is absolutely larger
		if(ad){
			c+=ar[i]+br[i];
			cr[i]=c%10;c/=10;
		}
		else{
			c+=ar[i]-br[i];cr[i]=c%10;c/=10;
		}
		size++;
	}
	for(int i=b->get_size();i<a->get_size();i++){
		c+=ar[i];
		cr[i]=c%10;c/=10;
		size++;
	}
	while(c!=0){
		cr[size++]=c%10;c/=10;
	}
	for(int i=0;i<size;i++){
		if(cr[i]<0){cr[i]+=10;cr[i+1]--;
		}
	}
	while(size>0&&cr[size-1]==0)size--;
	if(size==0)sign=0;
	return new UnlimitedInt(cr,cap,sign,size);	
}
bool compare(UnlimitedInt* a,UnlimitedInt* b){//return whether |a| is greater than equal |b|
	if(a->get_size()!=b->get_size())
		return a->get_size()>b->get_size();
	int s=a->get_size()-1;
	while(s>0&&a->get_array()[s]==b->get_array()[s])s--;
	return a->get_array()[s]>=b->get_array()[s];
}
UnlimitedInt* copy(UnlimitedInt* a,bool abs=false,bool invert=false){
	int cap=a->get_capacity(),size=a->get_size(),sign=abs?1:a->get_sign(),*ar=new int[cap];
	if(invert)sign=-1*a->get_sign();
		if(sign==0)size=0;
	for(int i=0;i<size;i++)ar[i]=a->get_array()[i];
	return new UnlimitedInt(ar,cap,sign,size);
}
UnlimitedInt* UnlimitedInt::add(UnlimitedInt* a,UnlimitedInt* b){
	if(a->get_sign()==0)return copy(b,false,true);if(b->get_sign()==0)return copy(a);
	if(compare(a,b)){
		if(a->get_sign()*b->get_sign()==1)return  adsub(a,b,true,false);
		else return adsub(a,b,false,false);
	}
	else {
		if(a->get_sign()*b->get_sign()==1)return  adsub(b,a,true,false);
		else return adsub(b,a,false,false);
	}
}
UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* a,UnlimitedInt* b){
	if(a->get_sign()==0)return copy(b);if(b->get_sign()==0)return copy(a);
	if(compare(a,b)){
		if(a->get_sign()*b->get_sign()==1)return  adsub(a,b,false,false);
		else return adsub(a,b,true,false);
	}
	else {
		if(a->get_sign()*b->get_sign()==1)return  adsub(b,a,false,true);
		else return adsub(b,a,true,true);
	}
}
UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* a,UnlimitedInt* b){
	// cout<<a->to_string()<<"s"<<a->get_sign()<<endl<<b->to_string()<<endl<<"mul99"<<endl;
	
	if(a->get_sign()==0)return copy(a);if(b->get_sign()==0)return copy(b);
	int cap=(a->get_size()+1)+(b->get_size()+1),size=0,sign=a->get_sign()*b->get_sign();
	int *ar=a->get_array(),*br=b->get_array(),*cr=new int[cap];
	for(int i=0;i<cap;i++)cr[i]=0;
	for(int i=0;i<a->get_size();i++)
		for(int j=0;j<b->get_size();j++)
			cr[i+j]+=ar[i]*br[j];
	for(int i=0;i<cap;i++)if(cr[i]>9){cr[i+1]+=cr[i]/10;cr[i]%=10;}
	for(int i=cap-1;i>=0;i--){if(cr[i]!=0){size=i+1;break;}}
	return new UnlimitedInt(cr,cap,sign,size);
}
UnlimitedInt* extend(UnlimitedInt*a,int x){
	int cap=a->get_capacity(),size=a->get_size(),sign=a->get_sign(),*ar=new int[cap+x];
	if(sign==0)size=0;
	for(int i=0;i<size;i++)ar[i+x]=a->get_array()[i];
	for(int i=0;i<x;i++)ar[i]=0;
	return new UnlimitedInt(ar,cap+x,sign,size+x);
}
UnlimitedInt* UnlimitedInt::div(UnlimitedInt* a,UnlimitedInt* b){
	if(b->get_sign()==0||a->get_sign()==0){return new UnlimitedInt(0);}//handle this case
	if(!compare(a,b)&&a->get_sign()*b->get_sign()==1)return new UnlimitedInt(0);
	else if(!compare(a,b)&&a->get_sign()*b->get_sign()==-1)return new UnlimitedInt(-1);
	int cap=a->get_size()-b->get_size()+3,size=0,sign=a->get_sign()*b->get_sign();
	UnlimitedInt* cop=copy(a,true),*bcop=copy(b,true);
	int *ans=new int[cap];
	for(int i=0;i<cap;i++)ans[i]=0;
	for(int i=cap-1;i>=0;i--){
		for(int j=9;j>0;j--){
			UnlimitedInt *d=new UnlimitedInt(j),*z=UnlimitedInt::mul(d,bcop),*p=extend(z,i);
			delete d;delete z;
			if(compare(cop,p)){
				UnlimitedInt* temp=cop;
				cop=UnlimitedInt::sub(cop,p);
				delete temp;
				delete p;
				ans[i]=j;
				break;
			}
			delete p;
		}
		if(ans[i]!=0)size=max(size,i+1);
	}
	if(sign==-1&&cop->get_size()!=0)ans[0]++;
	for(int i=0;i<=size;i++)if(ans[i]>10){ans[i]+=10;ans[i+1]++;}
	if(ans[size]!=0)size++;
	delete cop;
	delete bcop;
	return new UnlimitedInt(ans,cap,sign,size);
}
UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* a,UnlimitedInt* b){
	UnlimitedInt *q=UnlimitedInt::div(a,b);
	UnlimitedInt *p=UnlimitedInt::mul(q,b),*ans=UnlimitedInt::sub(a,p);
	// cout<<a->to_string()<<endl<<b->to_string()<<endl<<"mod"<<endl;
	// cout<<q->to_string()<<"s"<<q->get_size()<<endl<<(p->to_string())<<endl<<ans->to_string()<<endl<<"mod2"<<endl;
	delete q;
	delete p;
	return ans;
}
string UnlimitedInt::to_string(){
	string s="";
	if(sign==0)return "0";
	for(int i=size-1;i>=0;i--)s+=unlimited_int[i]+'0';
	if(sign==-1)s="-"+s;
	return s;
}
// int main(){
// 	UnlimitedInt* a=new UnlimitedInt("0"),*b=new UnlimitedInt("815730721"),*c=UnlimitedInt::mod(a,b);
// 	cout<<a->to_string()<<"s"<<a->get_sign()<<endl<<b->to_string()<<endl<<c->to_string()<<endl;
// 	return 0;
// }
