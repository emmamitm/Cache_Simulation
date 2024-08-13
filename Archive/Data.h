//
// Created by Emma Mitchell on 12/3/22.
//

#ifndef CACHE_SIMULATION_DATA_H
#define CACHE_SIMULATION_DATA_H
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include "sstream"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include "sstream"
#include "vector"
#include "map"
#include "unordered_map"
using namespace std;

class Data {


public:
    int bytesInCache;
    int bytesInLine;
    int offset;
    int line;
    int set;
    string setL;
    int lineUsing;
    int offsetUsing;
    string LineL;
    string offsetL;
    string tag;
    string address; //the address in binary

    void FullyAssociative(string b){
        //string is already in binary
        string temp;
        //split into tag/offset
        //take the binary string and take the amount of the offset off of the end and store it in an offset
        int num= offset;
        for (int i = 0; i < b.size(); ++i) {
            if (i==(b.size()-num)){
                offsetL+= b.at(i);
                num--;
            }
        }
        tag=  b.substr(0,(b.size()-offset));
    }

    void DirectMapped(string b){
        //string is already in binary
        string temp;
        //split into tag/line/offset
        //take the binary string and take the amount of the offset off of the end and store it in an offset
        int num= offset;
        for (int i = 0; i < b.size(); ++i) {
            if (i==(b.size()-num)){
                offsetL+= b.at(i);
                num--;
            }
        }
        temp = b.substr(0,(b.size()-offset));

        int num2= line;
        for (int i = 0; i < temp.size(); ++i) {
            if (i==(temp.size()-num2)){
                LineL+= temp.at(i);
                num2--;
            }
        }
        string temp2;
        temp2 = temp.substr(0,(temp.size()-line));
        tag += temp2;
    }

    void SetAccociative(string b){
        //string is already in binary
        string temp;
        //split into tag/set/offset
        //take the binary string and take the amount of the offset off of the end and store it in an offset
        int num= offset;
        for (int i = 0; i < b.size(); ++i) {
            if (i==(b.size()-num)){
                offsetL+= b.at(i);
                num--;
            }

        }

        temp = b.substr(0,(b.size()-offset));

        int num2= set;
        for (int i = 0; i < temp.size(); ++i) {
            if (i==(temp.size()-num2)){
                setL+= temp.at(i);
                num2--;
            }
        }

        string temp2;
        temp2 = temp.substr(0,(temp.size()-set));
        tag += temp2;

    }


    Data(int byte, int l, string s, int option){
        bytesInCache =byte;
        bytesInLine =l;
        offset = log2(bytesInLine);
        line = log2(bytesInCache/bytesInLine);
        lineUsing= log2(line);
        offsetUsing= log2(offset);
        offsetL = "";
        LineL= "";
        tag= "";
        address = s;
        if (option==1)
            DirectMapped(address);
        if (option==2)
            FullyAssociative(address);
        if (option ==3)
            SetAccociative(address);
    }
    Data(int byte, int l, string s, int option, int setWay){
        bytesInCache =byte;
        bytesInLine =l;
        offset = log2(bytesInLine);
        line = log2(bytesInCache/bytesInLine);
        lineUsing= log2(line);
        offsetUsing= log2(offset);
        offsetL = "";
        LineL= "";
        tag= "";
        setL ="";
        address = s;
        set = setWay;
        if (option ==3)
            SetAccociative(address);
    }
    //binary to decimal conversion
    long btoD(long double number)
    {
        //initializers
        long double num = number;
        long dec = 0;
        int base = 1;
        //making a temporary variable
        unsigned long long temp = (unsigned long long)num;
        while (temp) {
            long ld = temp % 10;
            temp = temp / 10;
            //multiplying the base times the last digit
            dec+= ld * base;
            //binary c onversion factor
            base = base * 2;
        }

        return dec;
    }

};


#endif //CACHE_SIMULATION_DATA_H
/*
 *
 *
 *
 *
 *  double LineF;
   double offsetF;
    double tagF;
    double binaryTag;
    long binaryOffset;
    long binaryLine;
 */
