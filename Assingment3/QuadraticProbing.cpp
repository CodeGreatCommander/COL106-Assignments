#include "QuadraticProbing.h"
void QuadraticProbing::merge_sort(std::vector<int>& k){
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
QuadraticProbing::QuadraticProbing() {
    size=100019;
    total=0;
    for(int i=0;i<size;i++){
        isOccupied.push_back(false);
        bankStorage1d.push_back(Account{"",0});
    }
}

void QuadraticProbing::createAccount(std::string id, int count) {
    long long int s=hash(id),i=1;
    if(!isOccupied[s]){
        isOccupied[s]=true;
        bankStorage1d[s]=Account{id,count};
        total++;
    }
    else{
        while(i!=size&&isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]){
            i++;
        }
        isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]=true;
        bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size]=Account{id,count};
        total++;
    }
}

void QuadraticProbing::swap(int &a,int &b){
    a=a^b;
    b=a^b;
    a=a^b;
}

void QuadraticProbing::compare(std::vector<int> &v,int a){
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
std::vector<int> QuadraticProbing::getTopK(int k) {
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

int QuadraticProbing::getBalance(std::string id) {
    long long int s=hash(id),i=1;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        return bankStorage1d[s].balance;
    }
    else{
        while(i!=size&&(!isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]||bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size].id!=id)){
            i++;
        }
        if(isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]&&bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size].id==id){
            return bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size].balance;
        }
        return -1;
    }
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    long long int s=hash(id),i=1;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        bankStorage1d[s].balance+=count;
    }
    else{
        while(i!=size&&(!isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]||bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size].id!=id)){
            i++;
        }
        if(isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]&&bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size].id==id){
            bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size].balance+=count;
        }
        else{
            createAccount(id,count);
        }
    }
}

bool QuadraticProbing::doesExist(std::string id) {
    long long int s=hash(id)%size,i=1;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        return true;
    }
    else{
        // std::cout<<s<<" "<<i<<" "<<size<<" "<<((s+(i%2?-1:1)*i*i)%size+size)%size<<std::endl;
        while(i!=size&&(!isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]||bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size].id!=id)){
            i++;
        }
        if(isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]&&bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size].id==id){
            return true;
        }
        return false;
    }
}

bool QuadraticProbing::deleteAccount(std::string id) {
    long long int s=hash(id),i=1;
    if(isOccupied[s]&&bankStorage1d[s].id==id){
        isOccupied[s]=false;
        total--;
        return true;
    }
    else{
        while(i!=size&&(!isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]||bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size].id!=id)){
            i++;
        }
        if(isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]&&bankStorage1d[((s+(i%2?-1:1)*i*i)%size+size)%size].id==id){
            isOccupied[((s+(i%2?-1:1)*i*i)%size+size)%size]=false;
            total--;
            return true;
        }
        return false;
    }
}
int QuadraticProbing::databaseSize() {
    return total;
}

int QuadraticProbing::hash(std::string id) {
    long long int ans=0,size=100019,x=119;
    for(int i=id.size()-1;i>=0;i--){
        ans+=((id[i]%size)*x)%size;
        x=(x*x)%size;
    }
    return (ans%size);
}

