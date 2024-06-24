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

        //Hay que quitarlo despues
        cout<<newsns.name<<newsns.averageRating<<newsns.averageMonetizing<<endl;
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
     if (line.length() == 0) {
        return;
    }

    if (line[0] == ':') {
        throw invalid_argument(line);
    }

    size_t primer_punto = line.find(':');
    if (primer_punto == string::npos) {
        throw invalid_argument(line);
    }
    string name = line.substr(0, primer_punto);

    size_t segundo_punto = line.find(':', primer_punto + 1);
    if (segundo_punto == string::npos || primer_punto + 1 == segundo_punto) {
        throw invalid_argument(line);
    }
    string avgR = line.substr(primer_punto + 1, segundo_punto - primer_punto - 1);

    if (avgR.find(':') != string::npos || segundo_punto == line.length()) {
        throw invalid_argument(line);
    }
    double avgRating = stod(avgR);

    string avgM = line.substr(segundo_punto + 1);
    if (avgM.find(':') != string::npos) {
        throw invalid_argument(line);
    }
    double avgMonetizing = stod(avgM);

    try {
        SNData::newSocialNetwork(name, avgRating, avgMonetizing);
    } catch (invalid_argument &e) {
        throw invalid_argument(line);
    }
}


void SNData::readFromCSV(string filename){
    int linenum=0;
    ifstream ficheroLec(filename);

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