#pragma once
#include <string>
#include <iostream>
#include<iomanip>
#define MAX_NAME 30
#define MAX_NUM 15
using namespace std;

struct contact{
    string name;
    string number;
};

void printTableLine(){
     cout << "+------------------------------+---------------+" << endl;
}

void printContact(contact &person){
    cout << '|' << setw(MAX_NAME) << left << person.name << setfill(' ') << "|"<< setw(MAX_NUM) << left << person.number << '|' <<endl;
    printTableLine();
}

bool isValidNumber(string number){
    bool rtnval = true;
    if(number.size() > MAX_NUM){
        return false;
    }
    //special case for first number
    if(!((number[0] >= '0' && number[0] <= '9') || number[0] == '+')){
        return false;
    }
    for(string::iterator it = number.begin()+1; it != number.end(); ++it){
        if(*it < '0' && *it > '9'){
            rtnval = false;
            break;
        }
    }
    return rtnval;
}

//TODO Finish is valid name
bool isValidName(string name){
    return true;
}