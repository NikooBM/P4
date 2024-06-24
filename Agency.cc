// DNI 78008606N BIBILEISHVILI MAMALADZE, NIKOLOZ
#include "SNData.h"
#include "Influencer.h"
#include "Agency.h"
#include "Util.h"

#include <stdexcept>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Agency::Agency(string filename){
ifstream ficheroBinLec;
ficheroBinLec.open(filename,ios::in|ios::binary);
if(!ficheroBinLec.is_open()){
    Util::error(ERR_FILE);
    throw EXCEPTION_FILE;
    return;
}
//Lee agency
BinAgency agency={};
ficheroBinLec.read(reinterpret_cast<char*>(&agency), sizeof(BinAgency));
this->name = agency.name;
this->money = agency.money;

 // Lee los influencers
for (unsigned int i = 0; i < static_cast<unsigned int>(agency.numInfluencers); ++i) {
    BinInfluencer inf = {};
    ficheroBinLec.read(reinterpret_cast<char*>(&inf), sizeof(BinInfluencer));
    Influencer newInf(inf);
    influencers.push_back(newInf);

     // Lee los seguidores de cada influencer
    for (unsigned int j = 0; j < static_cast<unsigned int>(newInf.getFollowers().size()); ++j) {
        BinSNFollowers fol = {};
        ficheroBinLec.read(reinterpret_cast<char*>(&fol), sizeof(BinSNFollowers));
        SNFollowers newFol(fol);
        influencers.back().addFollowers(newFol);
        }
    }
ficheroBinLec.close();
}

BinAgency Agency::toBinAgency() const{
    BinAgency ba={};

    /*if(name.size()>KMAXNAME){
        string truncated_name= name.substr(0, KMAXNAME);
        strcpy(ba.name,truncated_name.c_str());
        ba.name[KMAXNAME - 1] = '\0';
    }
    else{
        strcpy(ba.name,name.c_str());
    }*/
    strncpy(ba.name, name.c_str(), KMAXNAME - 1);
    ba.name[KMAXNAME - 1] = '\0'; 

    ba.money=money;
    ba.numInfluencers=static_cast<int>(influencers.size());
    return ba;
}

void Agency::saveData(string filename) const{
    ofstream file;
    file.open(filename,ios::out|ios::binary);
    if(!file.is_open()){
        Util::error(ERR_FILE);
    }

    BinAgency ba=toBinAgency();
    file.write((char*)&ba,sizeof(BinAgency));
    for(unsigned int i=0;i<static_cast<unsigned int>(influencers.size());i++){
        BinInfluencer bi=influencers[i].toBinInfluencer();
        file.write((char*)&bi,sizeof(BinInfluencer));
        for(unsigned int j=0;j<static_cast<unsigned int>(influencers[i].getFollowers().size());j++){
            BinSNFollowers bsf=influencers[i].getFollowers()[j].toBinSNFollowers();
            file.write((char*)&bsf,sizeof(BinSNFollowers));
        }
    }
    
    file.close();
}

Agency::Agency(string name,double initialMoney){
    this->name=name;
    money=initialMoney;
}

Influencer* Agency::searchInfluencer(string infName){
    for (unsigned int i=0; i<influencers.size(); ++i) {
        if (influencers[i].getName()==infName) {
            return &influencers[i];
        }
    }
    throw EXCEPTION_INFL_NOT_FOUND;
}

void Agency::addInfluencer(string infName,double commission){
    bool error=false;
    
    for(unsigned int i=0;i<influencers.size();i++){
        string nombre=influencers[i].getName();
        if(nombre==infName){
            Util::error(ERR_DUPLICATED);
            error=true;
        }
    }
    if(!error){
        Influencer inf(infName);
        try{
            inf.setCommission(commission);
            influencers.push_back(inf);
        }
        catch(Exception e){
            if(e==EXCEPTION_WRONG_COMMISSION){
                Util::error(ERR_WRONG_COMMISSION);
            }
            else{
                Util::debug(e);
            }
        }
    }
}

void Agency::addFollowers(string infName, string snName, int nFollowers){
    try {
        Influencer* inf = searchInfluencer(infName);
        inf->addFollowers(snName, nFollowers);
    } catch (Exception e) {
        if(e==EXCEPTION_INFL_NOT_FOUND){
            Util::error(ERR_NOT_FOUND);
        }
        else{
            Util::debug(e);
        }
    }
}

void Agency::newEvent(vector<string> infNames,int nsns, string snNames[],double evRats[]){
    
    for(unsigned int i=0; i<infNames.size(); ++i){
         try {
             Influencer* inf = searchInfluencer(infNames[i]);
             inf->addEvent(nsns,snNames,evRats);
         }
        catch(Exception e){
            if(e==EXCEPTION_INFL_NOT_FOUND){
            }
            else{
                Util::debug(e);
            }
        }

     }
}

void Agency::deleteInfluencer (string infName){
    try {
        Influencer* inf = searchInfluencer(infName);
        double commission = inf->collectCommission();
        money += commission;
        for (unsigned int i=0; i < influencers.size(); ++i) {
            string nombre=influencers[i].getName();
            
            if (nombre == infName) {
                influencers.erase(influencers.begin() + i);
                return;
            }
        }
    }
    catch(Exception e){
        if(e==EXCEPTION_INFL_NOT_FOUND){
            Util::error(ERR_NOT_FOUND);
        }
        else{
            Util::debug(e);
        }
    }
}


double Agency::collectCommissions(){
    double totalCommission = 0;
    for (unsigned int i=0;i<influencers.size();i++){
        double inflCommission= influencers[i].collectCommission();
        totalCommission += inflCommission;
    }
    money += totalCommission;
    return totalCommission;
}

ostream& operator<<(ostream &os,const Agency &ag){

    os << "Agency: " << ag.getName() << " [" << ag.getMoney() << "]" << endl;
    for (unsigned int i = 0; i < ag.influencers.size(); ++i) {
        string nombre=ag.influencers[i].getName();
        double commission=ag.influencers[i].getCommission();
        
        os << "Influencer: " << nombre << " (" << commission << ")" << endl;
        
        vector<SNFollowers> followers = ag.influencers[i].getFollowers();
        
        for (unsigned int j = 0; j <followers.size(); ++j) {
            os << followers[j];
        }
        os<<endl;
    }
    os<<endl;
    return os;
}
