// DNI 78008606N BIBILEISHVILI MAMALADZE, NIKOLOZ

#ifndef _SNDATA_H_
#define _SNDATA_H_

#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct SocialNetworkData {
   string name;
   double averageRating;
   double averageMonetizing;
};

class SNData{
    
private:
    static vector<SocialNetworkData> sns;

public:
    static void newSocialNetwork(string name,double avgR,double avgM);
    static bool checkSN(string name);
    static double getAvgRating(string name);
    static double getAvgMonetizing(string name);
    static unsigned int getSocialNetworkNumber(){ return (unsigned int)sns.size(); };
    static void readFromCSV(string filename);
    static void writeToCSV(string filename);
    
};

#endif
