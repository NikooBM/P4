// DNI 78008606N BIBILEISHVILI MAMALADZE, NIKOLOZ

#ifndef _INFLUENCER_H_
#define _INFLUENCER_H_

#include "Util.h"
#include "SNFollowers.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
class SNFollowers;

struct BinInfluencer{
    char name[KMAXNAME];
    double commission;
    int numFollowers;
};

class Influencer{
    friend ostream& operator<<(ostream &os,const Influencer &inf);
private:
    string name;
    double commission;
    vector <SNFollowers> followers;
    
public:
    Influencer(const BinInfluencer &bI);
    void addFollowers(const SNFollowers &follower);
    BinInfluencer toBinInfluencer() const;
    Influencer (string name);
    void setCommission(double commission);
    void addFollowers(string snName,int nFollowers);
    void addEvent(int nsns,string sn[],double rat[]);
    double collectCommission();
    string getName() const {return name;};
    double getCommission() const {return commission;};
    vector <SNFollowers> getFollowers() const {return followers;};
};

#endif
