#include "LinearProbing.h"
void LinearProbing::increaseSize(){
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
void LinearProbing::merge_sort(std::vector<int>& k){
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
LinearProbing::LinearProbing() {
    total=0;
    primes=std::vector<int>{1433,4127,10499,21977,52103,100019,150053};
    primeIndex=0;
    size=primes[primeIndex];
    for(int i=0;i<size;i++){
        isOccupied.push_back(false);
        bankStorage1d.push_back(Account{"",0});
    }
}

void LinearProbing::createAccount(std::string id, int count) {
    if(1.0*size/total<2.0)increaseSize();
    int s=hash(id),i=(s+1)%size;
    if(!isOccupied[s]){
        isOccupied[s]=true;
        bankStorage1d[s]=Account{id,count};
        total++;
    }
    else{
        while(isOccupied[i]&&i!=s){
            i=(i+1)%size;
        }
        isOccupied[i]=true;
        bankStorage1d[i]=Account{id,count};
        total++;
    }
}

void LinearProbing::swap(int &a,int &b){
    a=a^b;
    b=a^b;
    a=a^b;
}

void LinearProbing::compare(std::vector<int> &v,int a){
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
std::vector<int> LinearProbing::getTopK(int k) {
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

int LinearProbing::getBalance(std::string id) {
    int s=hash(id),i=(s+1)%size;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        return bankStorage1d[s].balance;
    }
    else{
        while(i!=s&&(!isOccupied[i]||bankStorage1d[i].id!=id)){
            i=(i+1)%size;
        }
        if(isOccupied[i]&&bankStorage1d[i].id==id){
            return bankStorage1d[i].balance;
        }
        return -1;
    }
}

void LinearProbing::addTransaction(std::string id, int count) {
    int s=hash(id),i=(s+1)%size;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        bankStorage1d[s].balance+=count;
    }
    else{
        while(i!=s&&(bankStorage1d[i].id!=id||!isOccupied[i])){
            i=(i+1)%size;
        }
        if(isOccupied[i]&&bankStorage1d[i].id==id){
            bankStorage1d[i].balance+=count;
        }
        else{
            createAccount(id,count);
        }
    }
}

bool LinearProbing::doesExist(std::string id) {
    int s=hash(id),i=(s+1)%size;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        return true;
    }
    else{
        while(i!=s&&(!isOccupied[i]||bankStorage1d[i].id!=id)){
            i=(i+1)%size;
        }
        if(isOccupied[i]&&bankStorage1d[i].id==id){
            return true;
        }
        return false;
    }
}

bool LinearProbing::deleteAccount(std::string id) {
    int s=hash(id),i=(s+1)%size;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        total--;
        isOccupied[s]=false;
        return true;
    }
    else{
        while(i!=s&&(!isOccupied[i]||bankStorage1d[i].id!=id)){
            i=(i+1)%size;
        }
        if(isOccupied[i]&&bankStorage1d[i].id==id){
            total--;
            isOccupied[i]=false;
            return true;
        }
        return false;
    }
}
int LinearProbing::databaseSize() {
    return total;
}

int LinearProbing::hash(std::string id) {
    long long int ans=0,size=this->size,x=119;
    for(int i=id.size()-1;i>=0;i--){
        ans+=((id[i]%size)*x)%size;
        x=(x*x)%size;
    }
    return (ans%size);
}