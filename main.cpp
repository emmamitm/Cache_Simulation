#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include "sstream"
#include "Data.h"
#include "vector"
#include "map"
#include "unordered_map"
#include "struct.h"
using namespace std;
struct test {
    string set;
    string tag;
    int number;
};
int main() {
    //making a vector to hold the addys taken from the file
    vector<string> addys;
    vector<string> binaryDigits;
    string blank="";
    string fileName;
    cout<< "What file would you like to load in? ";
    cin>> fileName;
    ifstream file(fileName);
    if (file.is_open()){ //opening the file and getting the addresses
        while(getline(file, blank)){
            istringstream stream(blank);

            string gone = "";
            string addy = "";
            string gone2 = "";
            getline(stream, gone, ' ');
            getline(stream, addy, ' ');
            getline(stream, gone2, ' ');
            addys.push_back(addy);

    }}

    //turning the addresses into binary
    for(int j=0; j< addys.size(); j++){
        string temp = "";
        string compare = addys[j].substr(2, (addys[j].size()-2));
        for (int i = 0; i < compare.size(); ++i) {
            char c = compare.at(i);
            if (c <= 57) {
                switch (c) {
                    case 48:
                        temp += "0000";
                        break;
                    case 49:
                        temp += "0001";
                        break;
                    case 50:
                        temp += "0010";
                        break;
                    case 51:
                        temp += "0011";
                        break;
                    case 52:
                        temp += "0100";
                        break;
                    case 53:
                        temp += "0101";
                        break;
                    case 54:
                        temp += "0110";
                        break;
                    case 55:
                        temp += "0111";
                        break;
                    case 56:
                        temp += "1000";
                        break;
                    case 57:
                        temp += "1001";
                        break;
                }
            }
            else{
                switch (c) {
                    case 97:
                        temp+="1010";
                        break;
                    case 98:
                        temp+="1011";
                        break;
                    case 99:
                        temp+="1100";
                        break;
                    case 100:
                        temp+="1101";
                        break;
                    case 101:
                        temp+="1110";
                        break;
                    case 102:
                        temp+="1111";
                        break;
                    case 65:
                        temp+="1010";
                        break;
                    case 66:
                        temp+="1011";
                        break;
                    case 67:
                        temp+="1100";
                        break;
                    case 68:
                        temp+="1101";
                        break;
                    case 69:
                        temp+="1110";
                        break;
                    case 70:
                        temp+="1111";
                        break;
                }
            }

        }
        binaryDigits.push_back(temp);
        temp="";
    }


    //take every element from the vector and make a vector of the class
    int bytesInC;
    cout<< "How many bytes are in the cache: ";
    cin>> bytesInC;
    int c;
    cout<< "How many bytes are in each line: ";
    cin>> c;


    double hit=0;
    double miss=0;
    int option;
    unordered_map<string,string> mymap;
    unordered_map<string, int> map2;
    int option2;
    vector<Data> datavalues;//Vector of the data class that gets the address, tag, line

    cout<<endl<< "Select an Number for the simulation (1=direct mapping; 2=Fully Associatve; 3=Set Associative): ";
    cin>> option;

    if (option==1){
        //this is for the DIRECT MAPPING
        for (int i = 0; i < binaryDigits.size(); ++i) {
            Data d(bytesInC,c,binaryDigits.at(i),option);
            datavalues.push_back(d);
        }
        for (int i = 0; i < datavalues.size(); ++i) {
            auto iter = mymap.find(datavalues.at(i).LineL);
            if (iter != mymap.end()){ //line matches
                if (iter->second == datavalues.at(i).tag){//if the tags do not match
                    //hit increments
                    hit++;


                } else {
                    //replace the tag
                    //miss increments
                    iter->second =datavalues.at(i).tag;
                    miss++;
                }
            }else{
                //a miss
                //the thing is not in the list and you have to add it to the map
                mymap.emplace(datavalues.at(i).LineL, datavalues.at(i).tag);
                miss++;
            }
        }

    }
    else if (option ==2){
        //Fully Associatve
        int userReplacementChoice;
        cout<< endl << "Which replacement strategy would you like to use? (1=LRU, 2=FIFO) ";
        cin >> userReplacementChoice;
        int counterLRU =1; //will update only when a tag is used
        int counterFIFO =1; //will update everytime the loop runs to indicate how long it has been there
        int sizeOfMap =0;
        int cacheSize= bytesInC;
        int bytesInCache;

        bytesInCache = cacheSize/c;
        for (int i = 0; i < binaryDigits.size(); ++i) {
            Data d(bytesInC,c,binaryDigits.at(i),option);
            datavalues.push_back(d);
        }

        for (int i = 0; i < datavalues.size(); ++i) {
            auto iter = map2.find(datavalues.at(i).tag);
            if (iter != map2.end()){ //tag matches
                //compare tags
                if (iter->first == datavalues.at(i).tag){//if the tags match
                    //hit increments
                    hit++;
                    if (userReplacementChoice ==1){
                        counterLRU++;
                        iter->second =counterLRU;
                    }
                }
            }else{ //reached the end without finding the tag
                if (sizeOfMap==bytesInCache){ //if the map is  full --> have to use a replacement method
                    //a miss
                    //if you are using FIFO--> that means that the first one in will be removed first
                    //if you are using LRU--> use the counter with the lowest number
                    miss++;
                    if (sizeOfMap ==0){
                        map2.emplace(datavalues.at(i).tag, 1);
                    }
                    else if (userReplacementChoice ==1){
                        string tag2;
                        auto iter2 = map2.begin();
                        long lowest =10000000000000000;
                        while (iter2 != map2.end()){
                            if (iter2->second <= lowest){
                                lowest = iter2->second;
                                tag2= iter2->first;
                            }
                            iter2++;
                        }
                        map2.erase(tag2);
                        map2.emplace(datavalues.at(i).tag, 1);
                    }
                    else{
                        //counter fifo with the largers vLUE HAS BEEN IN THERE THE LONGEST
                        string tag2;
                        //increment FIFO counter before adding new value to the map
                        auto iter2 = map2.begin();
                        int highest =1;
                        while (iter2 != map2.end()){
                            if (iter2->second >= highest){
                                highest = iter2->second;
                                tag2= iter2->first;
                            }
                            iter2++;
                        }
                        map2.erase(tag2);
                        map2.emplace(datavalues.at(i).tag, 1);
                    }

                 }
                else{ //if the map is not full --> just add it to the end
                    miss++;
                    if (userReplacementChoice ==1){
                        map2.emplace(datavalues.at(i).tag, 1);
                        sizeOfMap++;
                    }
                    else{
                        //increment FIFO counter before adding new value to the map
                        auto iter2 = map2.begin();

                        if (iter2 != map2.end()){
                            for (int j = 0; j < sizeOfMap; ++j) {
                                counterFIFO = iter2->second;
                                counterFIFO++;
                                iter2->second = counterFIFO;
                            }
                        }

                        map2.emplace(datavalues.at(i).tag, 1);
                        sizeOfMap++;
                    }


                }

            }
        }

    }
    else{
        int setAssociativity;
        cout <<endl << "How many ways would you like the set associativity to be. Enter a number (2=two-way; 4=four-way) :";
        cin>> setAssociativity;
        int userReplacementChoice;
        cout<< endl << "Which replacement strategy would you like to use? (1=LRU, 2=FIFO) ";
        cin >> userReplacementChoice;
        int counterLRU =1; //will update only when a tag is used
        int counterFIFO =1; //will update everytime the loop runs to indicate how long it has been there
        int cacheSize= bytesInC;
        int bytesInCache;
        bytesInCache = cacheSize/c;
        int sets= bytesInCache/setAssociativity;
        int linesInSet = cacheSize/sets; //this is how many things can be in each set map
        int counter=0;

        for (int i = 0; i < binaryDigits.size(); ++i) {
            Data d(bytesInC,c,binaryDigits.at(i),option, sets);
            datavalues.push_back(d);
        }

        vector<test> vectest;
        vector<int> v;
        int set2=0;
        int count =0;
        int val = sets;
        for (int i = 0; i < datavalues.size(); ++i) {
            count++;
            if (vectest.size() ==0){
                vectest.push_back({datavalues.at(i).setL, datavalues.at(i).tag, 1});

            }
            else{

                    v.push_back(i);
                    for (int j = 0; j < vectest.size(); ++j) {
                        if (datavalues.at(i).tag == vectest.at(j).tag && datavalues.at(i).setL == vectest.at(j).set) {//hit
                            hit++;
                            if (userReplacementChoice == 1) {//LRU
                                counterLRU++;
                                vectest.at(j).number = counterLRU;
                                //break;
                            } //else
                            //break;
                        }
                        if (j== vectest.size()-1 && datavalues.at(i).setL == vectest.at(j).set){
                            if (linesInSet == vectest.size()){

                                if (userReplacementChoice ==1){
                                    miss++;
                                    string tag2;
                                    string set2;
                                    int lowest =10000000;
                                    int numberMove;
                                    for (int k = 0; k < vectest.size(); ++k) {
                                        if (vectest.at(k).number <= lowest){
                                            lowest= vectest.at(k).number;
                                            tag2 = vectest.at(k).tag;
                                            set2= vectest.at(k).set;
                                            numberMove =k;
                                        }

                                    }
                                    vectest.at(numberMove).number = lowest;
                                    vectest.at(numberMove).tag = tag2;
                                    vectest.at(numberMove).set = set2;
                                    break;
                                }
                                else {
                                    miss++;
                                    string tag2;
                                    string set2;
                                    int highest = 1;
                                    int numberMove;

                                    for (int k = 0; k < vectest.size(); ++k) {
                                        if (vectest.at(k).number >= highest) {
                                            highest = vectest.at(k).number;
                                            tag2 = vectest.at(k).tag;
                                            set2 = vectest.at(k).set;
                                            numberMove = k;
                                        }
                                    }
                                    vectest.at(numberMove).number = highest;
                                    vectest.at(numberMove).tag = tag2;
                                    vectest.at(numberMove).set = set2;
                                    break;
                                }
                            }
                            else{//add to end

                                if (userReplacementChoice ==1){ //LRU
                                    miss++;
                                    vectest.push_back({datavalues.at(i).setL, datavalues.at(i).tag, 1});
                                    break;
                                }
                                else{//FIFO
                                    miss ++;
                                    for (int k = 0; k < vectest.size(); ++k) {
                                        vectest.at(k).number++;
                                    }
                                    vectest.push_back({datavalues.at(i).setL, datavalues.at(i).tag, 1});
                                    break;
                                }

                            }
                        }
                }
            }
            if (count == datavalues.size()){
                set2=1;
                val--;
            }
            if (set2==1 ){
                if (val <=0){

                    count =0;
                    counterLRU =1;
                    counterFIFO =1;
                    string constSet = vectest.at(0).set;
                    for (auto it=datavalues.begin(); it != datavalues.end(); it++){
                        if (constSet == it->setL){
                            datavalues.erase(it);
                        }
                    }
                    for (auto it=vectest.begin(); it != vectest.end(); it++){
                        vectest.erase(it);
                    }
                    set2=0;
                    i=0;
                }


            }

        }
    }
    cout<<endl<< "hits: " <<hit;
    cout<< endl << "miss: " << miss;

    cout<< endl <<"hit rate:  " << (hit/(miss+hit));



    return 0;
}
