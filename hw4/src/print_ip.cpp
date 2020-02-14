#include <iostream>
#include <stdexcept>
#include <vector>
#include <experimental/iterator>

using namespace std;


struct print_ip{

// //container
// template<typename T, 
//     typename Fake = 
//         typename std::enable_if<std::is_array<T>::value, void>::type>
// print_ip(T&& value) {
//     cout << "container" << endl;
// };

//integer type
template<typename T, 
    typename Fake = 
        typename std::enable_if<std::is_integral<typename std::remove_reference<T>::type>::value, void>::type>
print_ip(T&& value) {
    copy(
        std::make_reverse_iterator(static_cast<const uint8_t*>(static_cast<const void*>(&value)) + sizeof(T)),
        std::make_reverse_iterator(static_cast<const uint8_t*>(static_cast<const void*>(&value))),  
        std::ostream_iterator<int>(std::cout, "."));
    cout << '\b' << ' ' << endl;
};

print_ip(std::string&& value) {
    cout << value << endl;
};

};
// ostream& operator<<(ostream& os, const print_ip& ip){
//     bool first = true;
//     for(auto i = rbegin(ip.byte);i != rend(ip.byte); ++i)
//     {
//         if(first) {first = false;}
//          else { os << ".";};
//         os << +*i;
//     }
//     return os;
// }

int main(){
    print_ip(int(1234));
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));
    print_ip(std::string("trololo"));
    //print_ip(std::vector<int>{1, 2, 3, 4});
    // print_ip(std::string("trololo"));
    return 0;
}

// - Печать адреса как 
// - Печать адреса как 
// - Печать адреса как 
// - Печать адреса как 
// - Печать адреса как 
// - Печать адреса как 
// - Печать адреса как std::list
// - Опционально. Печать адреса как std::tuple