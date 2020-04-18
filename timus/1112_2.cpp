//1112
//bruteforce
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct segment{
    int id = -1;
    int metric = -1;
    int left, right;
    segment(int id_, int left_, int right_){
        id = id_;
        left = min(left_, right_);
        right = max(left_, right_);
    }
    void addintersect(int a){
        auto p = find(begin(intersect_id), end(intersect_id), a);
        intersect_id.erase(p);
    };
    void removeintersect(int a){
        auto p = find(begin(intersect_id), end(intersect_id), a);
        intersect_id.erase(p);
    };

    vector<int> intersect_id;
};

bool isIntersect(const segment& x1, const segment& x2){
    return x1.left < x2.right && x1.right > x2.left;
}

bool haveintersect(vector<segment> &data){
    for(auto &i: data){
        if (i.intersect_id.size() > 0) return true;
    }
    return false;
}



int main(){
    int n;
    int a, b;
    vector<segment> segments;
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> a >> b;
        segments.emplace_back(segment(i, a, b));
    }

    return 0;
}