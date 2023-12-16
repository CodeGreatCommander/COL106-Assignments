#ifndef CUBICPROBING_H
#define CUBICPROBING_H

#include "BaseClass.h"
#include <iostream>

class CubicProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    CubicProbing();
private:
    int size,total;
    std::vector<Account> bankStorage1d;
    std::vector<bool> isOccupied;
    void compare(std::vector<int> &v,int a);
    void swap(int &a,int &b);
    void merge_sort(std::vector<int> &v);
};

#endif // CUBICPROBING_H
