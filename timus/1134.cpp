//1134
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

struct Cards{
    vector<int> cards;
    int n = -1;
    int m = -1;
    Cards(){
        cards = vector<int>(1001, 0);
    };
};

Cards cards;

bool checkcards(Cards& cards){
    for(int i = 0; i < cards.n; ++i){
        if(cards.cards[i] > 2) return false;
    }
    return true;
}

void setcard(Cards& cards, int i){
    if(i == 0){ cards.cards[0]+=2; return;}
    if(i == cards.n){ 
        if(cards.cards[i-1] == 0)
            cards.cards[i-1]+=2;
        else 
            cards.cards[i-1]+=1;
        return;}
    if(cards.cards[i-1] >= 2) { 
        if(cards.cards[i] == 0)
            cards.cards[i]+=2;
        else 
            cards.cards[i]+=1;
        return;
    }
    cards.cards[i]+=1;
    cards.cards[i-1]+=1;
}

bool inputcard(Cards& cards, vector<int>& vzyat){
    sort(vzyat.begin(), vzyat.end());
    
    for(int i = 0; i < cards.m; ++i){
        setcard(cards, vzyat[i]);
        if(!checkcards(cards)){
            return false;
        }
    }
    return true;
}

int getbit(int n, int k){
    return (n & ( 1 << k )) >> k;
}

vector<int> gencards(uint8_t seed, int n){
    vector<int> result;
    for(int i = 0; i < n; ++i){
        result.push_back(i+getbit(seed, i));
    };
    return result;
}

void testcards(){
    for(int i = 0; i < 1025; ++i){
        cout << i << ' ';
        vector<int> input = gencards(i,10);
        Cards cards;
        cards.n = 10;
        cards.m = 10;
        if(!inputcard(cards, input)){
            cout<< "Errror seed = " << i << "; ";
            throw;
        }
    }
}

int main(){
    //testcards();
    cin >> cards.n >> cards.m;
    int a;
    vector<int> vzyat;
    vzyat.reserve(cards.m);
    for(int i = 0; i < cards.m; ++i){
        cin >> a;
        vzyat.push_back(a);
    }

    cout << (inputcard(cards, vzyat)?"YES":"NO");
    return 0;
}