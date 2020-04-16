#include <iostream>
#include <set>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>


using namespace std;

int main(){
    int n;
    cin >> n;
    cout << std::fixed << std::setprecision(1);
    if (n == 0) {cout << "0.0"; return 0;};
    if (n == 1) {cin >> n; cout << static_cast<double>(n); return 0;}
    unsigned int num;
    priority_queue<unsigned int> nums;
    for(int i = n/2 + 1; i != 0; --i){
        cin >> num;
        nums.push(num);
    }
    for(int i = n - (n/2 + 1); i != 0; --i){
        cin >> num;
        nums.push(num);
        nums.pop();
    }

    if (n % 2 == 1){
        cout << static_cast<double>(nums.top());
    } else {
        unsigned int a = nums.top();
        nums.pop();
        cout << static_cast<double>(a / 2.0 + nums.top() / 2.0);
    }
    return 0;
}