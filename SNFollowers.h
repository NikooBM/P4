// DNI 78008606N BIBILEISHVILI MAMALADZE, NIKOLOZ

#ifndef _SNFOLLOWERS_H_
#define _SNFOLLOWERS_H_

#include "Util.h"

#include <string>
#include <iostream>
using namespace std;

struct BinSNFollowers{
    char name[KMAXNAME];
    int numFollowers;
    double money;
};

class SNFollowers{
    friend ostream& operator<<(ostream &os,const SNFollowers &snf);
private:
    string name;
    int numFollowers;
    double money;

public:
    SNFollowers(const BinSNFollowers &bSNF);
    BinSNFollowers toBinSNFollowers() const;
    SNFollowers(string name,int initialFollowers);
    void addFollowers(int nFollowers);
    void addEvent(double rating);
    double collectCommission(double commission);
    string getName() const {return name;};
    int getNumFollowers() const {return numFollowers;};
    double getMoney() const {return money;};
};

#endif
