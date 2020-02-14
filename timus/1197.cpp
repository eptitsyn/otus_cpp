#include <iostream>

int main(){
    int n;
    std::cin >> n;
    char aa;
    int b;
    for(int i = 0; i < n; ++i){
        std::cin >> aa >> b;
        int a = aa - 'a' + 1;
        a = (9 - a) > a ? a : 9 - a;
        b = (9 - b) > b ? b : 9 - b;
        int result = 2;
        if(a > 1) ++result;
        if(a > 2) ++result;
        if(b > 1) ++result;
        if(b > 2) ++result;
        if(a > 1 && b > 2) ++result;
        if(b > 1 && a > 2) ++result;
        std::cout << result << std::endl;
    }
    return 0;
}