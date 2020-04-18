//1196
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    uint32_t n;
    cin >> n;
    set<uint32_t> dates;
    uint32_t d;
    for(size_t i = 0; i < n; ++i){
        cin >> d;
        //if(dates.back() != d)
            dates.insert(d);
    }

    size_t count = 0;
    cin >> n;
    for(size_t i = 0; i < n; ++i){
        cin >> d;
        if(dates.find(d) != dates.end()) {
            ++count;
        }
    }
    cout << count;  
    return 0;
}