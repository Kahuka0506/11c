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


int expr(int& n, string& s);
int equality(int& n, string& s);
int relational(int& n, string& s);
int add(int& n, string& s);
int mul(int& n, string& s);
int unary(int& n, string& s);
int primary(int& n, string& s);



void error_at(int& n, string& s){
    printf("\x1b[39m");printf("\x1b[1m");
    printf("Code:1:%d:  ", n);
    printf("\x1b[31m");printf("\x1b[1m");
    printf("error: ");
    printf("\x1b[39m");printf("\x1b[0m");
    printf("unexpected symbol '%c'\n", s[n]);

    printf("   ");
    rep(i,int(s.size())){
        if(i==n){
            printf("\x1b[31m");printf("\x1b[1m");
        }else{
            printf("\x1b[39m");printf("\x1b[0m");
        }
        printf("%c", s[i]);
    }
    printf("\n");
    string eee(n, ' ');
    printf("\x1b[31m");printf("\x1b[1m");
    printf("   %s^\n", eee.c_str());


    printf("\x1b[39m");printf("\x1b[0m");
    exit(1);
}






int expr(int& n, string& s){
    int res = equality(n,s);

    return res;
}





int equality(int& n, string& s){
    int res = relational(n,s);

    if(n+1 < int(s.size())){
        if(s.substr(n,2) == "=="){
            n += 2;
            int r_res = relational(n,s);

            if(res == r_res) res = 1;
            else res = 0;

        }else if(s.substr(n,2) == "!="){
            n += 2;
            int r_res = relational(n,s);

            if(res != r_res) res = 1;
            else res = 0;

        }
    }

    return res;
}


int relational(int& n, string& s){
    int res = add(n,s);

    if(n+1 < int(s.size())){
        if(s.substr(n,2) == "<="){
            n += 2;
            int r_res = add(n,s);

            if(res <= r_res) res = 1;
            else res = 0;

        }else if(s.substr(n,1) == "<"){
            n += 1;
            int r_res = add(n,s);

            if(res < r_res) res = 1;
            else res = 0;

        }else if(s.substr(n,2) == ">="){
            n += 2;
            int r_res = add(n,s);

            if(res >= r_res) res = 1;
            else res = 0;

        }else if(s.substr(n,1) == ">"){
            n += 1;
            int r_res = add(n,s);

            if(res > r_res) res = 1;
            else res = 0;

        }
    }


    return res;
}


int add(int& n, string& s){
    int res = mul(n, s);

    if(n+1 < int(s.size())){
        if(s.substr(n,1) == "+"){
            n++;
            int r_res = mul(n,s);

            res += r_res;
        }else if(s.substr(n,1) == "-"){
            n++;
            int r_res = mul(n,s);

            res -= r_res;
        }
    }
    return res;

}


int mul(int& n, string& s){
    int res = unary(n, s);

    if(n+1 < int(s.size())){
        if(s.substr(n,1) == "*"){
            n++;
            int r_res = unary(n,s);

            res *= r_res;
        }else if(s.substr(n,1) == "/"){
            n++;
            int r_res = unary(n,s);

            res /= r_res;
        }
    }
    return res;

}




int unary(int& n, string& s){
    int res = 0;
    int f = 1;

    if(s[n] == '+' || s[n] == '-'){
        if(s[n] == '-') f = -1;
        n++;
    }

    res = f*primary(n,s);

    return res;
}



int primary(int& n, string& s){
    int res = 0;
    if(s[n] >= '0' && s[n] <= '9'){
        int t = n;
        while (t < int(s.size())) {
            if(s[t] >= '0' && s[t] <= '9') t++;
            else break;
        }
        res = stoi(s.substr(n, t-n));
        n = t;
    }else{
        if(s[n] == '('){
            n++;
            res = expr(n,s);
            if(s[n] == ')'){
                n++;
            }else{
                error_at(n,s);
                return 0;
            }
        }else{
            error_at(n,s);
            return 0;
        }
    }

    return res;

}



int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;
        int n = 0;

        int ans = expr(n,s);
        cout << s << " = " << ans << endl;

    }




    return 0;
}
