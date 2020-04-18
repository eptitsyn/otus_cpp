//не решил. через поток графа надо решать

#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <set>

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
    void addintersect(segment* a){
        intersect_data.insert(a);
    };
    void removeintersect(segment *a){
        intersect_data.erase(a);
    };
    set<segment*> intersect_data;
};

struct segments{
    bool isIntersect(const segment& x1, const segment& x2){
    return x1.left < x2.right && x1.right > x2.left;
    }

    void add(segment&& a){
        data.emplace_back(a);
        segment* p = &*--end(data);
        for(segment &i: data){
            if(i.id != p->id && isIntersect((*p), i)) {
                p->addintersect(&i);
                i.addintersect(p);
            }
        }
    };

    void remove(int id){remove(get(id));};

    void remove(segment* a){
        for(auto &i: a->intersect_data){
            i->removeintersect(a);
        }
        int id = a->id;
        auto p = find_if(begin(data), end(data), [id](const segment &a){ return a.id == id; });
        data.erase(p);
        recount_metric();
    };

    segment* get(int id){
        auto p = find_if(begin(data), end(data), [id](const segment &a){ return a.id == id; });
        if ( p!= end(data)){
            return &(*p);
        }
        return nullptr;
    }

    vector<segment*> get_bymetric(int metric){
        sort_metricasc();
        auto starti = find_if(begin(data), end(data), [metric](const segment &a){ return a.metric == metric; });
        vector<segment*> result;
        while(starti != end(data) && starti->metric == metric){
            result.push_back( &(*starti) );
            ++starti;
        }
        return result;
    }

    void recount_metric(){
        for(auto &i: data){
            i.metric = i.intersect_data.size();
        }
    };

    void sort_metricasc(){
        data.sort([](segment a, segment b){ return a.metric < b.metric; });
        //sort(begin(data), end(data), [](segment a, segment b){ return a.metric < b.metric; });
    }

    void sort_metricdesc(){
        data.sort([](segment a, segment b){ return a.metric > b.metric; });
        //sort(begin(data), end(data), [](segment a, segment b){ return a.metric > b.metric; });
        printdatadebug();
    }
    void sort_leftcoord(){
        data.sort([](segment a, segment b){ return a.left < b.left; });
        //sort(begin(data), end(data), [](segment a, segment b){ return a.left < b.left; });
    }
    bool haveintersect(){
        for(auto &i: data){
            if (i.intersect_data.size() > 0) return true;
        }
        return false;
    }

    void printdata(){
        sort_leftcoord();
        cout << data.size() << endl;
        for(auto &i: data){
            cout << i.left << ' ' << i.right << endl;
        }
    }
    void printdatadebug(){
        cout << "=====" << endl;
        cout << data.size() << endl;
        for(auto &i: data){
            cout << i.id << ' ' << i.left << ' ' << i.right << ": " << i.metric << " :";
            for(auto &j: i.intersect_data){
                cout << ' ' << j->id;
            }
            cout << endl << flush;
        }
    }
    void smartdelete(){
        //delete with metric 2
        int i = 2;
        while(haveintersect()){
            vector<segment*> todel = get_bymetric(i);
            for(auto &ii: todel){
                remove(ii);
                i = 2;
            }
            if(todel.size() == 0){ ++i; };
            printdatadebug();
        }
    }
private:
    list<segment> data;
};

int main(){
    int n;
    int a, b;
    segments segments;
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> a >> b;
        segments.add(segment(i, a, b));
    }
    segments.recount_metric();
    
    segments.smartdelete();
    
    cout<< "result" << endl;
    segments.printdata();

    return 0;
}