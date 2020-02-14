#include <iostream>
int main(){
    int n,k;
    std::cin >> n >> k;
    int result;
    if (n<k) {
        result = 2;
    } else {
        result = (n*2 % k == 0) ? n*2 / k : n*2 / k + 1;
    }

    std::cout << result;
    return 0;
}