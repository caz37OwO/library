#pragma once
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using ll=long long;
using ldub=long double;
using lldub=__float128;
using str=string;

using mint=modint;

template<class T=ll>
using tup2=tuple<T,T>;
template<class T=ll>
using tup3=tuple<T,T,T>;
template<class T=ll>
using tup4=tuple<T,T,T,T>;
template<class T=ll>
using tup5=tuple<T,T,T,T,T>;
template<class T=ll>
using tup6=tuple<T,T,T,T,T,T>;
template<class T=ll>
using tup7=tuple<T,T,T,T,T,T,T>;

template<class T=ll>
using vec=vector<T>;
template<class T=ll>
using vec2=vector<vec<T>>;
template<class T=ll>
using vec3=vector<vec2<T>>;
template<class T=ll>
using vec4=vector<vec3<T>>;
template<class T=ll>
using vec5=vector<vec4<T>>;
template<class T=ll>
using vec6=vector<vec5<T>>;

template<class T>
using que=queue<T>;
template<class T>
using Pque=priority_queue<T>;
template<class T>
using pque=priority_queue<T, vector<T>, greater<T>>;

struct Edge{
  ll from,to,w=1,num=-1;
};
using gvec=vector<Edge>;
using gvec2=vector<gvec>;

template<class T>
bool chmax(T &a,T b){if(a<b){a=b;return 1;}return 0;}
template<class T>
bool chmin(T &a,T b){if(b<a){a=b;return 1;}return 0;}

#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define ins insert
#define tup make_tuple
#define low lower_bound
#define pops(a) __builtin_popcountll(a)
#define ctz(a) __builtin_ctzll(a)
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define nperm(v) next_permutation(all(v))
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define YN(f) cout << ((f)?"Yes":"No") << endl

const int IINF=2e9;
const ll INF=4e18;

#ifndef LOCAL
#define debug(x)
#endif

// ===

// ===
