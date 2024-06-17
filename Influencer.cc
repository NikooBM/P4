// DNI 78008606N BIBILEISHVILI MAMALADZE, NIKOLOZ

#include "Influencer.h"
#include "Util.h"
#include "SNData.h"

#include <stdexcept>
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

Influencer::Influencer(const BinInfluencer &bI){
    this->name=bI.name;
    this->commission=bI.commission;
    this->followers.empty();
}

void Influencer::addFollowers(const SNFollowers &follower){
    SNFollowers newFollower(follower);

    followers.push_back(newFollower);
}

BinInfluencer Influencer::toBinInfluencer() const{
    BinInfluencer newInfluencer;

    if(name.size()>KMAXNAME){
        name.substr(0,KMAXNAME);
        strcpy(newInfluencer.name,name.c_str());
    }
    else{
        strcpy(newInfluencer.name,name.c_str());
    }
    newInfluencer.commission=commission;
    newInfluencer.numFollowers=followers.size();

    return newInfluencer;
}

Influencer::Influencer(string name){
    this->name=name;
    commission=0.1;
}

void Influencer::setCommission(double commission){
    if(commission>0.0 && commission<0.8){
        this->commission=commission;
    }
    else{
        throw EXCEPTION_WRONG_COMMISSION;
    }
}

void Influencer::addFollowers(string snName,int nFollowers){
    bool found =false;
    try{
        SNFollowers sn(snName, nFollowers);
        for(unsigned int i=0;i<followers.size();i++){
            found=false;
            string nombre=followers[i].getName();
            if(nombre==snName){
                followers[i].addFollowers(nFollowers);
                found = true;
                return;
            }
        }
        if(!found){
            followers.push_back(sn);
        }
    }
    catch(Exception e){
        if(e==EXCEPTION_UNKNOWN_SN){
            Util::error(ERR_UNKNOWN_SN);
        }
        else{
            Util::debug(e);
        }
    }
}

void Influencer::addEvent(int nsns,string sn[],double rat[]){
    if (nsns < 1) {
        return;
    }
    
    for (unsigned int i = 0; i < followers.size(); ++i) {
        for (int j = 0; j < nsns; ++j) {
            if (followers[i].getName() == sn[j] && SNData::checkSN(sn[j])) {
                followers[i].addEvent(rat[j]);
            }
        }
    }
}


double Influencer::collectCommission(){
    double totalCommission = 0;
    
    for (unsigned int i=0; i<followers.size();++i){
        if(followers[i].getMoney()>0){
            totalCommission += followers[i].collectCommission(commission);
        }
    }
    return totalCommission;
}

ostream& operator<<(ostream &os,const Influencer &inf){
    os << "Influencer: " << inf.getName() << " (" << inf.getCommission() << ")" << endl;
    for (unsigned int i = 0; i < inf.getFollowers().size(); ++i) {
        os << inf.getFollowers()[i];
        os << endl;
    }
    return os;
}
