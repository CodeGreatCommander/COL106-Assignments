#include "Chaining.h"
void Chaining::merge_sort(std::vector<int>& k){
    if(k.size()==1)return;
    std::vector<int> a,b;
    for(int i=0;i<k.size()/2;i++){
        a.push_back(k[i]);
    }
    for(int i=k.size()/2;i<k.size();i++){
        b.push_back(k[i]);
    }
    merge_sort(a);
    merge_sort(b);
    int i=0,j=0;
    while(i<a.size()&&j<b.size()){
        if(a[i]>b[j]){
            k[i+j]=a[i];
            i++;
        }
        else{
            k[i+j]=b[j];
            j++;
        }
    }
    while(i<a.size()){
        k[i+j]=a[i];
        i++;
    }
    while(j<b.size()){
        k[i+j]=b[j];
        j++;
    }
}
Chaining::Chaining() {
    size=9973;
    total=0;
    for(int i=0;i<size;i++){
        bankStorage2d.push_back(std::vector<Account>{});
    }
}

void Chaining::swap(int &a,int &b){
    a=a^b;
    b=a^b;
    a=a^b;
}

void Chaining::compare(std::vector<int> &v,int a){
    if (v.size() == 0) {
        return;
    }
    if(a <= v[0]) {
        return;
    }
    v[0] = a;
    int i = 0;
    int n = v.size();
    
    while (true) {
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;
        int min_index = i;

        if (left_child < n && v[left_child] < v[min_index]) {
            min_index = left_child;
        }

        if (right_child < n && v[right_child] < v[min_index]) {
            min_index = right_child;
        }

        if (min_index != i) {
            swap(v[i], v[min_index]);
            i = min_index;
        } else {
            break;
        }
    }
}

void Chaining::createAccount(std::string id, int count) {
    total++;
    int i=hash(id);
    bankStorage2d[i].push_back(Account{id,count});
}


std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> result(k,-1);
    for(int i=0;i<size;i++){
        for(int j=0;j<bankStorage2d[i].size();j++){
            compare(result,bankStorage2d[i][j].balance);
        }
    }
    std::vector<int> ans;
    for(auto i:result){
        if(i!=-1)ans.push_back(i);
    }
    merge_sort(ans);
    return ans;
}

int Chaining::linearSearch(std::string id,std::vector<Account> &v){
    for(int i=0;i<v.size();i++){
        if(v[i].id==id){
            return i;
        }
    }
    return -1;
}
int Chaining::getBalance(std::string id) {
    int i=hash(id);
    int j=linearSearch(id,bankStorage2d[i]);
    if(j!=-1)
    return bankStorage2d[i][j].balance;
    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    int i=hash(id);
    int j=linearSearch(id,bankStorage2d[i]);
    if(j==-1){
        bankStorage2d[i].push_back(Account{id,count});
        total++;
    }
    else{
        bankStorage2d[i][j].balance+=count;
    }
}

bool Chaining::doesExist(std::string id) {
    int i=hash(id);
    return -1!=linearSearch(id,bankStorage2d[i]);
}

bool Chaining::deleteAccount(std::string id) {
    int i=hash(id);
    int j=linearSearch(id,bankStorage2d[i]);
    if(j==-1)return false;
    bankStorage2d[i].erase(bankStorage2d[i].begin()+j);
    total--;
    return true;
}
int Chaining::databaseSize() {
    return total;
}

int Chaining::hash(std::string id) {
    long long int ans=0,size=9973,x=119;
    for(int i=id.size()-1;i>=0;i--){
        ans+=((id[i]%size)*x)%size;
        x=(x*x)%size;
    }
    return (ans%size);
}

