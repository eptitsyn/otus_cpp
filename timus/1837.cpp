//1834
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct person{
    string name;
    int metric = 65536;
    vector<person*> teammates;

    void setmetric(int m){
        if (m < metric){
            metric = m;
            for(auto &i : teammates){
                i->setmetric(m+1);
            }
        }
    }
    void addteammate(person* p){
        if(p != this){
            teammates.push_back(p);
        }
    }
    void addteammates(vector<person*>& p){
        for(auto &i : p){
            addteammate(i);
        }
    }
};

person* getperson(list<person> &p, string name){
    list<person>::iterator iter;
    if((iter = find_if(p.begin(), p.end(), [&name](person& p){ return p.name == name;} )) == p.end()){
        p.push_back(person{name});
        iter = --p.end();
    }
    return &*iter;
}


int main(){
    size_t n;
    cin >> n;
    list<person> people;
    string d;
    vector<person*> team(3);

    for(size_t i = 0; i < n; ++i){
        team.clear();
        for(uint8_t j = 0; j < 3; ++j){
            cin >> d;
            team.push_back(getperson(people, d));
        };
        for(auto &i: team){
            i->addteammates(team);
        }
    }
    auto p = find_if(people.begin(), people.end(), [](person& p){ return p.name == "Isenbaev";});
    if (p != people.end()) p->setmetric(0);
    people.sort([](person& a, person& b){ return a.name < b.name;});
    //sort(people.begin(), people.end(), [](person& a, person& b){ return a.name < b.name;});
    for(auto &i: people){
        cout << i.name << ' ';
        if (i.metric == 65536) 
            cout << "undefined";
        else 
            cout << i.metric;
        cout << endl;
    }
    return 0;
}