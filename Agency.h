// DNI 78008606N BIBILEISHVILI MAMALADZE, NIKOLOZ

#ifndef _AGENCY_H_
#define _AGENCY_H_


#include <string>
#include <iostream>
#include <sstream>
#include "Influencer.h"
using namespace std;
class Influencer;

struct BinAgency{
    char name[KMAXNAME];
    double money;
    int numInfluencers;
};

class Agency{
    friend ostream& operator<<(ostream &os,const Agency &ag);
private:
    string name;
    double money;
    vector <Influencer> influencers;
public:
    Agency(string filename);
    unsigned int getNumberInfluencers() const { return influencers.size();};
    BinAgency toBinAgency() const;
    void saveData(string filename) const;
    Agency(string name,double initialMoney);
    Influencer *searchInfluencer (string infName);
    void addInfluencer (string infName,double commission);
    void addFollowers (string infName,string snName,int nFollowers);
    void newEvent( vector<string> infNames,int nsns, string snNames[],double evRats[]);
    void deleteInfluencer (string infName);
    double collectCommissions();
    string getName() const {return name;};
    double getMoney() const {return money;};
};
#endif
