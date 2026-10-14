#include "template/template.hpp"
struct UnionFind{
  vector<ll> par,sz;
  UnionFind(ll N):par(N),sz(N,1){
    for(ll i=0;i<N;i++) par[i]=i;
  }
  ll root(ll x){
    if(par[x]==x) return x;
    return par[x]=root(par[x]);
  }
  void add(ll x){
    par.pb(x);
    sz.pb(1);
    return;
  }
  bool unite(ll x,ll y){
    x=root(x),y=root(y);
    if(x==y) return false;
    par[y]=x;
    sz[x]+=sz[y];
    return true;
  }
  bool same(ll x,ll y){return root(x)==root(y);}
  ll size(ll x){return sz[root(x)];}
};