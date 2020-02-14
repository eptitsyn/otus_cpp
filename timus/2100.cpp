#include <iostream>
#include <string.h>

int main(){
    int n;
    std::cin >> n;
    char str[20];
    int result = n + 2;
    for(int i = 0; i < n; ++i){
        std::cin >> str;
        if (strchr(str, '+') != 0) ++result;
    }
    if(result == 13) ++ result;
    std::cout << result * 100;
    return 0;
}