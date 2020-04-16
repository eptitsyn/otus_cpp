#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    set<pair<int, int>> coords;
    int n;
    int x,y;
    int minx, maxx, miny, maxy;
    minx = maxx = miny = maxy = 0;
    cin >> n;

    for(int i = 0; i < n; ++i){
        cin >> x >> y;
        minx = min(x, minx);
        maxx = max(x, maxx);
        miny = min(y, miny);
        maxy = max(y, maxy);
        coords.insert({x,y});
    }
    minx = min(minx, 0);
    maxx = max(maxx, 0);
    miny = min(miny, 0);
    maxy = max(maxy, 0);

    //cout << minx << ' ' << maxx << ' ' << miny << ' ' << maxy << endl; 

    // if (minx > maxx) throw;
    // if (miny > maxy) throw;
    // if (maxx > 100) throw;
    // if (minx < -100) throw;
    // if (maxy > 100) throw;
    // if (miny < -100) throw;

    for(int i = maxy; i >= miny; --i){
        for(int j = minx; j <= maxx; ++j){
            if(coords.count({j,i}) > 0){ cout << '*';}
            else if(i == 0 && j == 0){ cout << '+'; }
            else if(i == 0){ cout << '-';}
            else if(j == 0){ cout << '|';}
            else 
                {cout << '.';}
        }
        cout << endl;
    }
    return 0;
}