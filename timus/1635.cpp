#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

struct Str{
    const char * str;
    size_t length;
};

void print(Str str){
    const char * p = str.str;
    for(int i = 0; i < str.length; ++i){
        cout << *p;
    }
}

bool ispalindrom(const char * p, size_t length){
    auto start = p;
    auto finish = p+length;
    --finish; 
    while(start < finish){
        if((*start) != (*finish)) return false;
        ++start;
        --finish;
    }
    return true;
}

//pair<size_t, vector<string> > palindrom2_length(string_view str);

// pair<size_t, vector<string> > palindrom_length(string str){
//     if(str.length() == 0) return {0, vector<string>()};
//     if(str.length() == 1) return {1, vector<string>{str}};
//     size_t length = str.size();
//     string::iterator start;
//     string::iterator finish;
//     //assert(begin(str)+length == end(str));

//     bool found = false;
//     while(!found){
//         start = begin(str);
//         finish = start + length;
//         while( !(found = ispalindrom(string(start, finish))) && finish != end(str)){
//             ++start;
//             ++finish;
//         }
//         --length;
//     }
//     //
//     int right = 0;
//     vector<string> right_s;
//     int left = 0;
//     vector<string> left_s;
    
//     tie(left, left_s) =  palindrom_length(string(begin(str), start) );
//     tie(right, right_s) = palindrom_length(string(finish, end(str)));
//     vector<string> result;
//     for(int i = 0; i < left_s.size(); ++i){
//         result.push_back(left_s[i]);
//     }
//     result.emplace_back(string(start,finish));
//     for(int i = 0; i < right_s.size(); ++i){
//         result.push_back(right_s[i]);
//     }
//     return make_pair((left+right+1), move(result));
// }

//aabba
//aaaba

vector<Str> palindrom_length(const char * str, size_t length);

vector<Str> palindrom_search(const char * str, size_t length, const char * start, size_t lng){
    vector<Str> result;
    vector<Str> left = palindrom_length(str, start - str);
    for(int i = 0; i < left.size(); ++i){
        result.emplace_back(left[i]);
    }
    result.emplace_back(Str{start, lng});
    vector<Str> right = palindrom_length(start+lng, start - str + lng);
    for(int i = 0; i < right.size(); ++i){
        result.emplace_back(right[i]);
    }
    return result;
};

vector<Str> palindrom_length(const char * str, size_t length){
    const char * start = str;
    const char * end = str + length;
    if (length == 0) return {};
    if (length == 1) return {Str{str ,1}};
    vector<vector<Str>> result;
    for(size_t lng = length; lng > 0; --lng){
        for(start = str; start+lng<str+length; ++start){
            if(ispalindrom(start, lng)){
                result.emplace_back(palindrom_search(str, length, start, lng));
            }
        }
    }
    auto result_i = min_element(result.begin(), result.end(), 
        [](const vector<Str>&a, const vector<Str>&b){return a.size() < b.size();} );
    return *result_i;
}

int main(){
    string input;
    cin >> input;
    const char * c = input.c_str();
    //cout << ispalindrom(c, input.size());
    vector<Str> str;
    str = palindrom_length(c, input.size());
    cout << str.size() << endl;
    for(auto &i: str){
        print(i);
        cout << ' ';
    }
}