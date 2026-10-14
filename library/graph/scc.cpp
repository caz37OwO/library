#include "template/template.hpp"
vec2<ll> SCC(gvec2 &G){
  ll N=(ll)G.size();
  vec P;
  auto dfs1=[&]()->void{
    vec seen(N);
    auto dfs=[&](this auto dfs,ll p)->void{
      seen[p]=1;
      for(auto e:G[p]) if(!seen[e.to]) dfs(e.to);
      P.pb(p);
    };
    for(ll i=0;i<N;i++) if(!seen[i]) dfs(i);
  };
  dfs1();
  reverse(all(P));
  vec2 res;
  auto dfs2=[&]()->void{
    gvec2 Grev(N);
    for(ll i=0;i<N;i++){
      for(auto e:G[i]) Grev[e.to].pb({e.to,e.from,e.w,e.num});
    }
    vec seen(N);
    auto dfs=[&](this auto dfs,ll p)->void{
      seen[p]=1;
      for(auto e:Grev[p]) if(!seen[e.to]) dfs(e.to);
      res.back().pb(p);
    };
    for(ll i=0;i<N;i++) if(!seen[P[i]]) res.pb(vec(0)),dfs(P[i]);
  };
  dfs2();
  return res;
}