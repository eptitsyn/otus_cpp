///
#include <iostream>
#include <memory>

int main()
{
    // auto p = std::make_unique<char[]>(1000);
    // char* z =  p.get();
    char* p = new char[1000];
    char* z = p;
    for(int i = 0; i < 1000; ++i){
        std::cout << *z;
        ++z;
    }
    std::cout << std::endl;
}
