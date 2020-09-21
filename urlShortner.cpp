#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

#define WEBSITE "http://www.urlShortneer.com/"

string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int mod = 62;
vector<string> id;

string IdToUrl(int ID) {
    if(ID == 0) return "";
    return IdToUrl(ID / mod) + characters[ID % mod];
}

int getPos(char ch) {
    for(int i = 0; i < mod; i++) {
        if(ch == characters[i]) {
            return i;
        }
    }
    return 0;
}

int UrltoId(string url) {
    int len = url.length();
    int index = 0;
    for(int i = 0; i < len; i++) {
        index += getPos(url[len - i - 1]) * pow(mod, i);
    }
    return index;
}

string encode(string longUrl) {    
    id.push_back(longUrl);
    return WEBSITE + IdToUrl(id.size() - 1);
}

string decode(string shortUrl) {
    int index = UrltoId(shortUrl);
    if(index < id.size())
        return id[index];
    return "Not Found error 404";
}


int main() {
    char iChoice;
    string url;
    
    ifstream inFile;
    
    inFile.open("urls.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    while (inFile >> url) {
        cout << "URL: " << url << endl;
        cout << "Short URL: " << encode(url) << endl;
        cout << "--------------------------" << endl;
    }
    
    inFile.close();

    while(1) {
        cout << "1. Create tinyURL" << endl;
        cout << "2. Redirect" << endl;
        cout << "3. Exit" << endl; 
        cout << "Enter your choice:\t";
        cin >> iChoice;
        switch(iChoice) {
            case '1':
                cin >> url;
                cout << "TinyURL: " << encode(url) << endl;
                break;
            case '2':
                cout << WEBSITE;
                cin >> url;
                cout << "rediect: " << decode(url)  << endl;
                break;
            case '3':
                return 0;
            default:
                cout << "Invalid choice. Please Try again." << endl;
        }
    }
    return 0;
}
