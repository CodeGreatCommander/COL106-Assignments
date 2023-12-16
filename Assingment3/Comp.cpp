#include "Comp.h"
#include <iostream>
void Comp::increaseSize(){
    std::vector<Account> temp=bankStorage1d;
    std::vector<bool> temp2=isOccupied;
    if(primeIndex==primes.size()-1){
        return;
    }
    primeIndex++;
    size=primes[primeIndex];
    // std::cout<<total<<" hi"<<std::endl;
    total=0;
    // std::cout<<total<<" 1"<<size<<std::endl;
    bankStorage1d=std::vector<Account>(size,Account{"",0});
    isOccupied=std::vector<bool>(size,false);
    for(int i=0;i<temp.size();i++){
        if(temp2[i])
        createAccount(temp[i].id,temp[i].balance);
    }
    // std::cout<<total<<" 1"<<size<<std::endl;

}

void Comp::merge_sort(std::vector<int>& k){
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
Comp::Comp() {
    total=0;
    primes=std::vector<int>{1433,4127,10499,21977,52103,100019,150053};
    primeIndex=0;
    size=primes[primeIndex];
    for(int i=0;i<size;i++){
        isOccupied.push_back(false);
        bankStorage1d.push_back(Account{"",0});
    }
}

void Comp::createAccount(std::string id, int count) {
    // std::cout<<size<<" 1 "<<total<<std::endl;
    if(1.0*size/total<2.0)increaseSize();
    long long int z=hash2(id);

    int s=hash(id),i=1;
    if(!isOccupied[s]){
        isOccupied[s]=true;
        bankStorage1d[s]=Account{id,count};
        total++;
    }
    else{
        while(i!=size&&isOccupied[(s+(z*i)%size)%size]){
            i++;
        }
        isOccupied[(s+(z*i)%size)%size]=true;
        bankStorage1d[(s+(z*i)%size)%size]=Account{id,count};
        total++;
    }
}
void Comp::swap(int &a,int &b){
    a=a^b;
    b=a^b;
    a=a^b;
}

void Comp::compare(std::vector<int> &v,int a){
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

std::vector<int> Comp::getTopK(int k) {
    std::vector<int> result(k,-1);
    for(int i=0;i<size;i++){
        if(isOccupied[i])
        compare(result,bankStorage1d[i].balance);
    }
    std::vector<int> ans;
    for(auto i:result){
        if(i!=-1)ans.push_back(i);
    }
    merge_sort(ans);
    return ans;
}

int Comp::getBalance(std::string id) {
    // std::cout<<size<<" 2 "<<total<<std::endl;
    long long int z=hash2(id);
    int s=hash(id),i=1;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        return bankStorage1d[s].balance;
    }
    else{
        while(i!=size&&(!isOccupied[(s+(z*i)%size)%size]||bankStorage1d[(s+(z*i)%size)%size].id!=id)){
            i++;
        }
        if(isOccupied[(s+(z*i)%size)%size]&&bankStorage1d[(s+(z*i)%size)%size].id==id){
            return bankStorage1d[(s+(z*i)%size)%size].balance;
        }
        return -1;
    }
}

void Comp::addTransaction(std::string id, int count) {
    // std::cout<<size<<" 3 "<<total<<std::endl;
    long long int z=hash2(id);
    int s=hash(id),i=1;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        bankStorage1d[s].balance+=count;
    }
    else{
        while(i!=size&&(!isOccupied[(s+(z*i)%size)%size]||bankStorage1d[(s+(z*i)%size)%size].id!=id)){
            i++;
        }
        if(isOccupied[(s+(z*i)%size)%size]&&bankStorage1d[(s+(z*i)%size)%size].id==id){
            bankStorage1d[(s+(z*i)%size)%size].balance+=count;
        }
        else{
            createAccount(id,count);
        }
    }
}

bool Comp::doesExist(std::string id) {
    // std::cout<<size<<" 4 "<<total<<std::endl;
    long long int z=hash2(id);
    int s=hash(id),i=1;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        return true;
    }
    else{
        while(i!=size&&(!isOccupied[(s+(z*i)%size)%size]||bankStorage1d[(s+(z*i)%size)%size].id!=id)){
            i++;
        }
        if(isOccupied[(s+(z*i)%size)%size]&&bankStorage1d[(s+(z*i)%size)%size].id==id){
            return true;
        }
        return false;
    }
}

bool Comp::deleteAccount(std::string id) {
    // std::cout<<size<<" 5 "<<total<<std::endl;
    long long int z=hash2(id);
    int s=hash(id),i=1;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        isOccupied[s]=false;
        total--;
        return true;
    }
    else{
        while(i!=size&&(!isOccupied[(s+(z*i)%size)%size]||bankStorage1d[(s+(z*i)%size)%size].id!=id)){
            i++;
        }
        if(isOccupied[(s+(z*i)%size)%size]&&bankStorage1d[(s+(z*i)%size)%size].id==id){
            isOccupied[(s+(z*i)%size)%size]=false;
            total--;
            return true;
        }
        return false;
    }
}
int Comp::databaseSize() {
    // std::cout<<total<<" "<<size<<std::endl;
    return total;
}

int Comp::hash(std::string id) {
    long long int ans=0,size=this->size,x=119;
    for(int i=id.size()-1;i>=0;i--){
        ans+=((id[i]%size)*x)%size;
        x=(x*x)%size;
    }
    return (ans%size);
}

int Comp::hash2(std::string id) {
    // long long int ans=0,size=7,x=221;
    // for(int i=id.size()-1;i>=0;i--){
    //     ans+=((id[i]%size)*x)%size;
    //     x=(x*x)%this->size;
    // }
    // return (ans%5);
    return 1;
}

// Feel free to add any other helper functions you need
// Good Luck!