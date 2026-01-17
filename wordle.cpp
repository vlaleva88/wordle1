#include<iostream>
#include <fstream>

using namespace std;

constexpr int MAX_SIZE=40;
constexpr int MAX_SIZE_WORD=5;

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


void loginUser() {
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    cout<<"Username: ";
    cin.getline(username,MAX_SIZE);
    cout<<"Password: ";
    cin.getline(password,MAX_SIZE);

    bool found=false;

    ifstream file("users.txt");
    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return;
    }

    char fullData[2*MAX_SIZE+1];
    myStrcpy(username, password, fullData);

    constexpr int MAX_SiZE_FILE=2*MAX_SIZE+2;
    char lineInFile[MAX_SiZE_FILE];
    while (file.getline(lineInFile,MAX_SiZE_FILE-1)) {
        if (isStringEqual(lineInFile,fullData)) {
            found=true;
            break;
        }
    }
    file.close();

    // can make check for wrong username or wrong password
    if (found) {
        cout<<"Successfully logged in"<<endl;
    }
    else {
        cout<<"Wrong username or password"<<endl;
    }
}

int wordCounterInFile() {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return -1;
    }


    char* wordInFile=new char[MAX_SIZE_WORD+1];
    int count=0;

    while (file.getline(wordInFile,MAX_SIZE_WORD+1)) {
        count++;
        // cout<<wordInFile<<endl;
    }
    file.close();
    delete[] wordInFile;

    return count;
}

char* getWordFromLine(const int line) {

    ifstream file("words.txt");
    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return nullptr;
    }

    char* wordInFile=new char[MAX_SIZE_WORD+1];

    int count=1;
    while (file.getline(wordInFile,MAX_SIZE_WORD+1)) {
        if (count==line) {
            file.close();
            return wordInFile;
        }
        count++;
    }
    file.close();

    return nullptr;
}

bool isInWord(const char* Word,const char symbol) {
    while (*Word) {
        if (*Word==symbol) {
            return true;
        }
        Word++;
    }
    return false;
}



void colorLetter(const char* trueWord, const char* Word, int& current) {
    if (trueWord==nullptr) {
        return;
    }

    for (int i=0;i<MAX_SIZE_WORD;i++) {
        if (Word[i]==trueWord[i]) {
            cout<<"\033[92m"<<Word[i]<<"\033[0m";
            current++;
        }
        else {
            if (isInWord(trueWord,Word[i])) {
                cout<<"\033[93m"<<Word[i]<<"\033[0m";
            }
            else {
                cout<<"\033[97m"<<Word[i]<<"\033[0m";
            }
        }
    }
}

void trueGame() {
    ifstream file("words.txt");

    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return;
    }
    file.close();

    srand(time(0));

    // get word
    const int randomWordIndex=rand()%wordCounterInFile()+1;
    // cout<<randomWordIndex<<" -> ";

    const char* searchWord=getWordFromLine(randomWordIndex);
    // cout<<searchWord<<endl;

    // can make different
    int availableTimes=6;

    int countCurrentLetter=0;
    char* word=new char[MAX_SIZE_WORD+1];
    while (availableTimes!=0 && countCurrentLetter!=MAX_SIZE_WORD) {
        cin.getline(word,MAX_SIZE_WORD+1);
        countCurrentLetter=0;
        colorLetter(searchWord,word,countCurrentLetter);
        availableTimes--;
        cout<<endl;
    }
    delete[] word;

    if (availableTimes==0 && countCurrentLetter!=MAX_SIZE_WORD) {
        cout<<"No more times! The word is: "<<searchWord<<endl;
    }
    else {
        cout<<"Congratulations! You win!"<<endl;
    }

    delete[] searchWord;
}
