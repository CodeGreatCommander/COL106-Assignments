#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    Chaining();
private:
    int size,total;
    std::vector<std::vector<Account>> bankStorage2d;
    int linearSearch(std::string id,std::vector<Account> &v);
    void compare(std::vector<int> &v,int a);
    void swap(int &a,int &b);
    void merge_sort(std::vector<int> &v);
};

#endif // CHAINING_H
