#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  
using namespace std;
using std::left;
using std::right;

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
    std::cout <<  std::setw(25) << left << a << std::setfill(' ') << ": is her namelollll"<< endl;
    std::cout <<  std::setw(25) << left << b << std::setfill(' ') << ": is her number" <<endl;
    // printf("    %-12s\t\t %8d\t\n", a, 123);
    // printf("    %-12s\t\t %8d\t\n", b, 45678);
    return 0;
}