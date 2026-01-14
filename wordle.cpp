#include<iostream>
#include <fstream>

using namespace std;

constexpr int MAX_SIZE=40;

bool isStringEqual(const char* text1, const char* text2) {
    while (*text1 || *text2) {
        if (*text1==*text2) {
            text1++;
            text2++;
        }
        else {
            return false;
        }
    }
    return true;
}

void myStrcpy(const char* text1, const char* text2, char* result) {
    while (*text1) {
        *result=*text1;
        result++;
        text1++;
    }

    *result=' ';
    result++;

    while (*text2) {
        *result=*text2;
        result++;
        text2++;
    }
    *result='\0';
}

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