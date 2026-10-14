#include "template/template.hpp"
#include "library/graph/get_dist.cpp"
vec<ll> get_path(gvec2 &G,ll s,ll t){
  ll N=(ll)G.size();
  vec D=get_dist(G,t),res;
  auto dfs=[&](this auto dfs,ll p)->void{
    res.pb(p);
    for(auto e:G[p]){
      if(D[p]!=D[e.to]+1) continue;
      dfs(e.to);
      break;
    }
  };
  dfs(s);
  return res;
}