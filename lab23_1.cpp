#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename);
    string line;

    while(getline(file, line)){
        size_t colonPos = line.find(':'); 
            
        string name = line.substr(0, colonPos);
        string scoreStr = line.substr(colonPos + 1);
            
        size_t pos1, pos2;
        int s1 = stoi(scoreStr, &pos1);
        int s2 = stoi(scoreStr.substr(pos1), &pos2);
        int s3 = stoi(scoreStr.substr(pos1 + pos2)); 
        int totalScore = s1 + s2 + s3;
            
        names.push_back(name);
        scores.push_back(totalScore);
        grades.push_back(score2grade(totalScore));
        
    }
    file.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    string line;
    getline(cin, line);
    
    int space_pos = line.find(' ');
    
    if (space_pos == -1) {
        command = line;
        key = "";
    } 
    else {
        command = line.substr(0, space_pos);
        key = line.substr(space_pos + 1);
    }
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    
    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
        }
    }
    
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    
    for(size_t i = 0; i < names.size(); i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
