#include<iostream>
#include <fstream>

using namespace std;

constexpr int MAX_SIZE=40;

void registerNewUser() {
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    cout<<"Enter username: ";
    cin.getline(username,MAX_SIZE);
    cout<<"Enter password: ";
    cin.getline(password,MAX_SIZE);

    ofstream file("users.txt",ios::app);
    if (!file) {
        cout<<"File could not be opened"<<endl;
        return;
    }
    file<<username<<" "<<password<<endl;
    file.close();

    cout<<"Registered new user"<<endl;
}