#include <iostream>
#include <set>


using namespace std;

int main(){
        set<int> eigen;
        int n, t;
        cin >> n;
        for(int j = 0; j < n; ++j){
            cin >> t;
            eigen.insert(t);
        }

        set<int> eigen2;
        cin >> n;
        for(int j = 0; j < n; ++j){
            cin >> t;
            if(eigen.find(t) != eigen.end()){
                eigen2.insert(t);
            }
        }

        set<int> eigen3;
        cin >> n;
        for(int j = 0; j < n; ++j){
            cin >> t;
            if(eigen2.find(t) != eigen2.end()){
                eigen3.insert(t);
            }
        }
    
    cout << eigen3.size();
    return 0;
}