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

    if (*text1=='\0' && *text2=='\0') {
        return true;
    }
    return false;
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

int sizeOfWord(const char* word) {
    if (word==nullptr) {
        return 0;
    }
    int size=0;
    while (*word) {
        size++;
        word++;
    }
    return size;
}

void registerNewUser(const char* username, const char* password) {

    ofstream file("users.txt",ios::app);
    if (!file) {
        cout<<"File could not be opened"<<endl;
        return;
    }
    file<<username<<" "<<password<<endl;
    file.close();

    cout<<"\033[92m"<<"Registered new user"<<"\033[0m"<<endl;
}

void loginUser(const char* username, const char* password, bool& found) {
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
        cout<<"\033[92m"<<"Successfully logged in"<<"\033[0m"<<endl;
        cout<<"Welcome back, "<<username<<endl;
    }
    else {
        cout<<"\033[91m"<<"Wrong username or password. Try again!"<<"\033[0m"<<endl;
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

// trueGame
bool isInFile(const char* Word) {
    ifstream file("words.txt");
    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return false;
    }

    char* line=new char[MAX_SIZE_WORD+1];
    while (file.getline(line,MAX_SIZE_WORD+1)) {
        if (isStringEqual(line,Word)) {
            file.close();
            delete[] line;
            return true;
        }
    }
    file.close();
    delete[] line;
    return false;
}

void trueGame(bool& winGame) {
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
        if (sizeOfWord(word)!=MAX_SIZE_WORD) {
            cout<<"The size is different. Enter new word: ";
            cout<<endl;
            cin.clear();
            continue;
        }

        if (!isInFile(word)) {
            cout<<"The word isn't in file yet. Enter new: ";
            cout<<endl;
            cin.clear();
            continue;
        }

        // cin.getline(word,MAX_SIZE_WORD+1);
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

// isInLeaderboard
char* getUsername(const char* string) {
    if (string==nullptr) {
        return nullptr;
    }

    char* username=new char[MAX_SIZE+1];
    int usernameIndex=0;
    while (*string!=' ' && *string) {
        username[usernameIndex]=*string;
        string++;
        usernameIndex++;
    }
    username[usernameIndex]='\0';

    return username;
}

bool isInLeaderboard(const char* username) {
    ifstream file("leaderboard.txt");

    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return false;
    }

    char fullData[2*MAX_SIZE+1];

    while (file.getline(fullData,2*MAX_SIZE+1)) {
        char* usernameInFile=getUsername(fullData);
        if (isStringEqual(usernameInFile, username)) {
            // cout<<usernameInFile<<endl;
            file.close();
            delete[] usernameInFile;
            return true;
        }
        delete[] usernameInFile;
    }
    file.close();
    return false;
}

void addNewUserInLeaderboard(const char* username, const int wins, const int playedGames) {
    ofstream file("leaderboard.txt",ios::app);

    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return;
    }

    file<<username<<" "<<wins<<"/"<<playedGames<<endl;
    file.close();
}

void updateInformation(const char* username, const int wins, const int games) {
    ifstream file("leaderboard.txt");

    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return;
    }

    ofstream temp("temp.txt");
    char line[2*MAX_SIZE+1];

    while (file.getline(line,2*MAX_SIZE+1)) {
        char* name=getUsername(line);

        if (isStringEqual(name,username)) {
            temp<<username<<" "<<wins<<"/"<<games<<endl;
        }
        else {
            temp<<line<<endl;
        }

        delete[] name;
    }
    file.close();
    temp.close();

    remove("leaderboard.txt");
    rename("temp.txt","leaderboard.txt");
}

// update every time leaderboard
void leaderboardUpdate(const char* username, const int playedGame, const int wins) {
    ofstream file("leaderboard.txt", ios::app);

    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return;
    }

    if (!isInLeaderboard(username)) {
        addNewUserInLeaderboard(username, wins, playedGame);
    }
    else {
        updateInformation(username, wins, playedGame);
    }

    file.close();
}

int getWins(const char* username) {
    ifstream file("leaderboard.txt");

    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return -1;
    }

    char line[2*MAX_SIZE+1];
    int wins;

    while (file.getline(line,2*MAX_SIZE+1)) {
        char* name=getUsername(line);

        if (isStringEqual(name,username)) {
            sscanf(line, "%*s %d/", &wins);
        }

        delete[] name;
    }

    file.close();
    return wins;

}

int getPlayedGames(const char* username) {
    ifstream file("leaderboard.txt");

    if (!file.is_open()) {
        cout<<"File could not be opened"<<endl;
        return -1;
    }

    char line[2*MAX_SIZE+1];
    int playedGames=0;

    while (file.getline(line,2*MAX_SIZE+1)) {
        char* name=getUsername(line);

        if (isStringEqual(name,username)) {
            sscanf(line, "%*s %*d/%d", &playedGames);
        }

        delete[] name;
    }

    file.close();
    return playedGames;
}

void selectAction(char* username, char* password) {



    bool login=false;

    while (!login) {

        cout<<"1. Login"<<endl;
        cout<<"2. Register User"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter your choice: ";
        int choice;
        cin>>choice;

        switch (choice) {
            case 1: {
                cin.ignore();

                cout<<"Username: ";
                cin.getline(username,MAX_SIZE);
                cout<<"Password: ";
                cin.getline(password,MAX_SIZE);
                loginUser(username,password,login);

                if (!login) {
                    break;
                } break;
            }
            case 2: {
                cin.ignore();

                cout<<"Username: ";
                cin.getline(username,MAX_SIZE);
                cout<<"Password: ";
                cin.getline(password,MAX_SIZE);
                registerNewUser(username, password);
                break;
            }
            case 3:
                exit(0);
            default:
                cout<<"\033[91m"<<"Wrong choice. Please enter current choice!"<<"\033[0m"<<endl;
        }
    }
}

void playerGameplay(const char* username, const char* password) {

    cout<<"\033[95m"<<"Let's the game start"<<"\033[0m"<<endl;

    bool flag=false;
    trueGame(flag);

    int games=0;
    int wins=0;

    if (isInLeaderboard(username)) {
        games=getPlayedGames(username);
        wins=getWins(username);
    }

    if (flag) {
        wins++;
        games++;
    }
    else {
        games++;
    }
    leaderboardUpdate(username, wins, games);
    cout<<"You stats: "<<wins<<"/"<<games<<endl;
}

int main() {
    cout<<"\033[95m"<<"Welcome to the Wordle! Please choice: "<<"\033[0m"<<endl;
    cout<<"-------------------------------------"<<endl;
    cout<<"1. Login"<<endl;
    cout<<"2. Register User"<<endl;
    cout<<"3. Exit"<<endl;
    int choice=0;
    cout<<"Enter your choice: ";

    char username[MAX_SIZE];
    char password[MAX_SIZE];

    while (choice!= 1 && choice!=2 && choice!=3) {
        cin>>choice;

        cin.ignore();

        switch (choice) {
            case 1: {
                bool found=false;
                while (!found) {
                    cout<<"Username: ";
                    cin.getline(username,MAX_SIZE);
                    cout<<"Password: ";
                    cin.getline(password,MAX_SIZE);
                    loginUser(username,password,found);
                } break;
            }
            case 2: {
                cout<<"Username: ";
                cin.getline(username,MAX_SIZE);
                cout<<"Password: ";
                cin.getline(password,MAX_SIZE);
                registerNewUser(username, password);
                break;
            }
            case 3:
                exit(0);
            default:
                cout<<"\033[91m"<<"Wrong choice. Please enter current choice!"<<"\033[0m"<<endl;
        }
    }

    cout<<endl;
    cout<<"\033[95m"<<"Let's the game start"<<"\033[0m"<<endl;

    bool flag=false;
    trueGame(flag);

    int games=0;
    int wins=0;

    if (isInLeaderboard(username)) {
        games=getPlayedGames(username);
        wins=getWins(username);
    }

    if (flag) {
        wins++;
        games++;
    }
    else {
        games++;
    }
    leaderboardUpdate(username, wins, games);

    return 0;
}