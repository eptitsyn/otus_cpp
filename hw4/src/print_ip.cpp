#include "print_ip.h"
#include <array>

/**
 * Main print_ip function
 */
int main(){
    print_ip(int(1234));
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));
    print_ip(std::string("trololo"));
    print_ip(std::vector<int>{1, 2, 3, 4});
    print_ip(std::list<int>{12, 34, 12, 23});
    print_ip(std::tuple<int, int, int, int>{0, 1, 2, 3});
    print_ip(std::tuple<int>{42});
    //print_ip(std::tuple<int, char, int, int>{34, 'A', 43, 23});
    // std::tuple<>{};
    // print_ip(std::tuple<>{});
    return 0;
}
