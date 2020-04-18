//1545
#include <iostream>
#include <map>
#include <list>
#include <string>

using namespace std;

int main(){
    int n;
    string str;
    map<char, list<char>> dict;
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> str;
        dict[str[0]].push_back(str[1]);
    }
    char k;
    cin >> k;
    if(dict.count(k) > 0){
        for(auto &i: dict[k]){
            cout << k << i << endl;
        }
    }

    return 0;
}