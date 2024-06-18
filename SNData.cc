// DNI 78008606N BIBILEISHVILI MAMALADZE, NIKOLOZ

#include "SNData.h"
#include "Util.h"

#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<SocialNetworkData> SNData::sns;

void SNData::newSocialNetwork(string name,double avgR,double avgM){

    if(checkSN(name)){
            throw invalid_argument(name);
        }
    
    if(avgR<0 || avgR>1){
        throw invalid_argument(to_string(avgR));
    }
    else if(avgM<0 || avgM>1){
        throw invalid_argument(to_string(avgM));
    }
    
    else{
        SocialNetworkData newsns;
        newsns.name=name;
        newsns.averageRating=avgR;
        newsns.averageMonetizing=avgM;
       
        sns.push_back(newsns);
    }
}

 bool SNData::checkSN(string name){
     for(unsigned int i=0;i<sns.size();i++){
         if(sns[i].name==name){
             return true;
         }
     }
     return false;
}

 double SNData::getAvgRating(string name){
     for(unsigned int i=0;i<sns.size();i++){
         if(sns[i].name==name){
             return sns[i].averageRating;
         }
     }
         return 0.0;
}

 double SNData::getAvgMonetizing(string name){
     for(unsigned int i=0;i<sns.size();i++){
         if(sns[i].name==name){
             return sns[i].averageMonetizing;
         }
     }
         return 0.0;
}

//P4
/*Leer de un fichero de texto name:avgRating:avgMonetizing
  Vacio=Nada y Mal= Error line X
   Y guardar en sns los datos leidos
 */

void readline(string line){

    if(line.length()==0){
        return;
    }

    else if(line[0]==':'){
        throw invalid_argument(line);
    }

    else{
for(unsigned int i=0;i<line.length();i++){
    if(line[i]==':'){
        string name=line.substr(0,i);
        for(unsigned int j=i+1;j<line.length();j++){
            if(line[j]==':'){
                string avgR=line.substr(i+1,j-i);
                for(unsigned int k=j+1;k<line.length();k++){
                    if(line[k]==':'){
                        throw invalid_argument(line);
                    }
                        string avgM=line.substr(j+1,line.length());
                        float avgRating=stod(avgR);
                        float avgMonetizing=stod(avgM);

                        SNData::newSocialNetwork(name,avgRating,avgMonetizing);
                        return;
                }
            }
        }
    }
}
throw invalid_argument(line);
    }
}

void SNData::readFromCSV(string filename){
    int linenum=0;
    ifstream ficheroLec;
    ficheroLec.open(filename);
    if(ficheroLec.is_open()){
        string line;
        while(getline(ficheroLec,line)){
            try{
                linenum++;
                readline(line);
            }catch(invalid_argument& e){
                cout<<"Error line "<<linenum<<endl;
            }
        }
        ficheroLec.close();
    }
    else{
        Util::error(ERR_FILE);
    }
    }


void SNData::writeToCSV(string filename){
    ofstream ficheroEscr;
    ficheroEscr.open(filename);
    if(ficheroEscr.is_open()){
        for(unsigned int i=0;i<sns.size();i++){
            ficheroEscr<<sns[i].name<<":"<<sns[i].averageRating<<":"<<sns[i].averageMonetizing<<endl;
        }
        ficheroEscr.close();
    }
    else{
        Util::error(ERR_FILE);
}
}