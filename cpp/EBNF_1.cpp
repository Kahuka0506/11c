#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<fstream>
#include<iomanip>
#include<queue>
#include<deque>
#include<ciso646>
#include<random>
#include<map>
#include<set>
#include<complex>
#include<bitset>
#include<stack>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<cassert>
#include <bits/stdc++.h>
using namespace std;


#define rep(i,n) for(int i=0; i<(n); i++)
#define reps(i,s,n) for(int i=(s); i<(n); i++)
#define all(v) v.begin(),v.end()
#define outve(v) for(auto i : v) cout << i << " ";cout << endl
#define outmat(v) for(auto i : v){for(auto j : i) cout << j << " ";cout << endl;}

const vector<string> node_type = {"VAL", "SYMBOL", "EOF"};

struct Node{
    string type;
    int val;
    char symbol;
};

string S;

vector<Node> code;


void tokenize(S){
    

}




int expr(int n, stirng& s){

}


int mul(int n, stirng& s){

}


int primary(int n, stirng& s){
    int res = 0;
    if(s[n] >= '0' && s[n] <= '9'){
        int t = n;
        while (t < int(s.size())) {
            if(s[t] >= '0' && s[t] <= '9') t++;
            else break;
        }
        res = stoi(s.substr(s.begin()+n, s.begin()+t));
    }else{
        if(s[n] == '('){
            n++;
            res = expr(n,s);
            n++;
        }
    }

    return res;

}



int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> S;





    return 0;
}
