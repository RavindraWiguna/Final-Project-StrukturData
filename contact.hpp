#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#define NAME 1
#define NUMBER 2
#define MAX_NAME 30
#define MAX_NUM 15
#define CANCEL_NAME "/cancel"
#define CANCEL_NUM "+0"
using namespace std;
/*
Berisi segala fungsi dan struktur yang berhubungan dengan perkontakan
*/
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

bool isValidNumber(std::string number){
    bool rtnval = true;
    if(number.size() > MAX_NUM){
        return false;
    }
    //special case for first number
    if(!((number[0] >= '0' && number[0] <= '9') || number[0] == '+')){
        return false;
    }
    for(string::iterator it = number.begin()+1; it != number.end(); ++it){
        if(*it < '0' || *it > '9'){
            rtnval = false;
            break;
        }
    }
    return rtnval;
}

bool isValidName(std::string name){
    return name.size() < MAX_NAME;
}

std::string getName(){
    // string namestr;
    char namechar[MAX_NAME];
    while(true){
        cout<<"Masukkan nama kontak [Maksimal: "<<MAX_NAME<<" karakter | Masukkan '"<<CANCEL_NAME<<"' untuk batal] >";
        cin.getline (namechar, MAX_NAME);
        // namestr = namechar;
        if(isValidName(namechar)){
            break;
        }
    }
    return namechar;
}

std::string getNumber(){
    // string numstr;
    char numchar[MAX_NUM];
    while(true){
        cout << "Masukkan nomor kontak [Maksimal: "<<MAX_NUM<<" digit| Masukkan '"<<CANCEL_NUM<<"' untuk batal] >";
        cin.getline (numchar, MAX_NUM);
        if(isValidNumber(numchar)){
            break;
        }
    }
    return numchar;
}

bool SaveToText(contact &newPerson, std::string fileName){
    bool success = true;
    ofstream textfile;
    textfile.open(fileName, std::ios_base::app); 
    if(textfile.is_open()){
        textfile << newPerson.name << endl;
        textfile << newPerson.number << endl;
        textfile.close();
    }else{
        cout << "Tidak dapat menemukan " << fileName << endl;
        success = false;
    }
    return success;
}