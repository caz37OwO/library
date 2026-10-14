#include "template/template.hpp"
vec<ll> get_dist(gvec2 &G,ll s=0){
  ll N=(ll)G.size();
  vec D(N,INF);
  D[s]=0;
  que<ll> BFS;
  BFS.push(s);
  while(!BFS.empty()){
    ll p=BFS.front();
    BFS.pop();
    for(auto e:G[p]){
      if(!chmin(D[e.to],D[p]+1)) continue;
      BFS.push(e.to);
    }
  }
  return D;
}