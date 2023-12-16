#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    int hash2(std::string id);
    Comp();
private:
    int size,total,primeIndex;
    std::vector<Account> bankStorage1d;
    std::vector<bool> isOccupied;
    void compare(std::vector<int> &v,int a);
    void swap(int &a,int &b);
    void merge_sort(std::vector<int> &v);
    std::vector<int> primes;
    void increaseSize();
};

#endif // COMP_H
