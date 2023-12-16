#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;

class Set {
private:
    int lower_bound(int x, const vi& set) {
        int u = set.size() - 1, l = 0;
        while (l <= u) {
            int m = (u + l) / 2;
            if (set[m] == x || ((m == 0 && set[m] > x) || (m != 0 && m != set.size() && set[m - 1] < x && set[m] > x))) {
                return m;
            } else if (set[m] < x) {
                l = m + 1;
            } else {
                u = m - 1;
            }
        }
        return set.size();
    }
    int binary_search(int x,const vi& set){
        int u=set.size()-1,l=0;
        while(l<=u){
            int m=(u+l)/2;
            if(set[m]==x)return m;
            else if(set[m]<x)l=m+1;
            else u=m-1;       
        }
        return -1;
    }
    vi id;
    int index(int id){
        for(int i=0;i<this->id.size();i++){
            if(this->id[i]==id)return i;
        }
        sets.push_back(vi());
        this->id.push_back(id);
        return sets.size()-1;
    }
public:
    vector<vi> sets;
    
    void insert() {
        int i, x;
        cin >> i >> x;
        i=index(i);
        int pos = lower_bound(x, sets[i]);
        if (pos == sets[i].size()) {
            sets[i].push_back(x);
        }
        else if(sets[i][pos]==x);
         else {
            sets[i].insert(sets[i].begin() + pos, x);
        }
        cout<<sets[i].size()<<endl;
    }
    void pop(){
        int i,x;cin>>i>>x;
        i=index(i);
        int pos=binary_search(x,sets[i]);
        if(pos!=-1){
            sets[i].erase(sets[i].begin()+pos);
        }
        cout<<sets[i].size()<<endl;   
    }
    void belongs_to(){
        int i,x;cin>>i>>x;i=index(i);
        cout<<(binary_search(x,sets[i])!=-1?1:0)<<endl;
    }
    void unio(){
        int i,j;
        cin>>i>>j;i=index(i);j=index(j);
        vi temp;
        int c1=0,c2=0;
        while(c1!=sets[i].size()&&c2!=sets[i].size()){
            if(sets[i][c1]==sets[j][c2]){
                temp.push_back(sets[i][c1]);
                c1++;c2++;
            }
            else if(sets[i][c1]<sets[j][c2]){
                temp.push_back(sets[i][c1]);
                c1++;
            }
            else{temp.push_back(sets[j][c2]);c2++;}
        }
        while(c1!=sets[i].size()){
            temp.push_back(sets[i][c1]);
            c1++;
        }
        while(c2!=sets[j].size()){
            temp.push_back(sets[j][c2]);
            c2++;
        }
        sets[i]=temp;
        cout<<sets[i].size()<<endl;
    }
    void intersection(){
        int i,j;
        cin>>i>>j;i=index(i);j=index(j);
        vi temp;
        int c1=0,c2=0;
        while(c1!=sets[i].size()&&c2!=sets[i].size()){
            if(sets[i][c1]==sets[j][c2]){
                temp.push_back(sets[i][c1]);
                c1++;c2++;
            }
            else if(sets[i][c1]<sets[j][c2]){
                // temp.push_back(sets[i][c1]);
                c1++;
            }
            else{/*temp.push_back(sets[i][c2]);*/c2++;}
        }
        sets[i]=temp;
        cout<<sets[i].size()<<endl;
    }
    void size(){
        int i;cin>>i;i=index(i);
        if(i<sets.size())cout<<sets[i].size()<<endl;
        else cout<<0<<endl;
    }
    void difference(){
        int i,j;
        cin>>i>>j;i=index(i);j=index(j);
        vi temp;
        int c1=0,c2=0;
        while(c1!=sets[i].size()&&c2!=sets[i].size()){
            if(sets[i][c1]==sets[j][c2]){
                // temp.push_back(sets[i][c1]);
                c1++;c2++;
            }
            else if(sets[i][c1]<sets[j][c2]){
                temp.push_back(sets[i][c1]);
                c1++;
            }
            else{/*temp.push_back(sets[i][c2]);*/c2++;}
        }
        while(c1!=sets[i].size()){
            temp.push_back(sets[i][c1]);
            c1++;
        }
        // while(c2!=sets[i].size()){
        //     temp.push_back(sets[i][c2]);
        //     c2++;
        // }
        sets[i]=temp;
        cout<<sets[i].size()<<endl;
    }
    void sym_difference(){
        int i,j;
        cin>>i>>j;i=index(i);j=index(j);
        vi temp;
        int c1=0,c2=0;
        while(c1!=sets[i].size()&&c2!=sets[i].size()){
            if(sets[i][c1]==sets[j][c2]){
                // temp.push_back(sets[i][c1]);
                c1++;c2++;
            }
            else if(sets[i][c1]<sets[j][c2]){
                temp.push_back(sets[i][c1]);
                c1++;
            }
            else{temp.push_back(sets[j][c2]);c2++;}
        }
        while(c1!=sets[i].size()){
            temp.push_back(sets[i][c1]);
            c1++;
        }
        while(c2!=sets[j].size()){
            temp.push_back(sets[j][c2]);
            c2++;
        }
        sets[i]=temp;
        cout<<sets[i].size()<<endl;
    }
    void print(){
        int i;cin>>i;i=index(i);
        for(int j=0;j<sets[i].size()-1;j++){
            cout<<sets[i][j]<<",";
        }
        cout<<sets[i][sets[i].size()-1]<<endl;
    }
};

int main() {
    Set mySet;
    while(true){
    int i;
    cin>>i;
    switch(i){
        case 1:
        mySet.insert();
        break;
        case 2:
        mySet.pop();
        break;
        case 3:
        mySet.belongs_to();
        break;
        case 4:
        mySet.unio();
        break;
        case 5:
        mySet.intersection();
        break;
        case 6:
        mySet.size();
        break;
        case 7:
        mySet.difference();
        break;
        case 8:
        mySet.sym_difference();
        break;
        case 9:
        mySet.print(); 
        break;
    }
    }
    return 0;
}
