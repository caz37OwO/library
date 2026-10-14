#include "template/template.hpp"
vec<ll> get_cent(gvec2 &G){
  ll N=(ll)G.size();
  vec<ll> centroids,sz(N,0);
  auto dfs=[&](this auto dfs,ll p,ll pre)->void{
    sz[p]=1;
    bool is_cen=true;
    for(auto e:G[p]){
      if(e.to==pre) continue;
      dfs(e.to,p);
      sz[p]+=sz[e.to];
      if(2*sz[e.to]>N) is_cen=false;
    }
    if(2*(N-sz[p])>N) is_cen=false;
    if(is_cen) centroids.pb(p);
  };
  dfs(0,-1);
  return centroids;
}
vec2<ll> decomp(gvec2 &G,ll u){
  vec2<ll> res;
  auto dfs=[&](this auto dfs,ll p,ll pre)->void{
    res.back().pb(p);
    for(auto e:G[p]) if(e.to!=pre) dfs(e.to,p);
  };
  for(auto e:G[u]){
    res.pb({});
    dfs(e.to,u);
  }
  return res;
}