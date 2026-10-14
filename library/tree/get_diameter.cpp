#include "template/template.hpp"
tup3<ll> get_diameter(gvec2 &G){
  ll N=(ll)G.size();
  auto get_dist=[&](ll s=0)->vec<ll>{
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
  };
  vec D=get_dist();
  ll p=max_element(all(D))-D.begin();
  D=get_dist(p);
  ll q=max_element(all(D))-D.begin();
  return tup(p,q,D[q]);
}