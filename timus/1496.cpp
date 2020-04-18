//1496
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main(){
    int n;
    cin >> n;
    set<string> nicks;
    set<string> spam;
    string s;
    for(int i = 0; i < n; ++i){
        cin >> s;
        if(nicks.count(s) > 0){
            spam.insert(s);
        } else {
            nicks.insert(s);
        }
    }
    for(auto &i: spam){
        cout << i << endl;
    }
    return 0;
}