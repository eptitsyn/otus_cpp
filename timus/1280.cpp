#include <map>
#include <set>
#include <iostream>

using namespace std;

int main(){
    unsigned int n, m;
    cin >> n >> m;
    multimap<unsigned int, unsigned int> map;
    unsigned int a, b;
    for(int i = 0; i < m; ++i){
        cin >> a >> b;
        map.insert({b, a});
    }
    set<unsigned int> learned;
    bool ok = true;
    unsigned int c;
    auto range = map.equal_range(1);
    for(int i = 0; i < n; ++i){
        cin >> c;
        range = map.equal_range(c);
        for(auto it = range.first; it != range.second; ++it){
            if(learned.count(it->second) == 0){
                //cout << c << ": lc = " << it->second;
                ok = false;
                break;
            }
        }
        learned.insert(c);
        if(!ok){ break;}
    }
    cout << (ok?"YES":"NO");
    return 0;
}