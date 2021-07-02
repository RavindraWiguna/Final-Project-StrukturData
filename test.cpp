#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    string a;
    string b;
    cin >> a;
    cin >> b;
    if(a > b){
        cout << "a is bigger" << endl;
    }else if(a == b){
        cout << "they are the same" << endl;
    }else{
        cout << "b is bigger" << endl;
    }
    return 0;
}