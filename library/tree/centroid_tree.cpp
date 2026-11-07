#include "template/template.hpp"
vec<ll> get_centroid_tree(gvec2 &G){
  ll N=(ll)G.size();
  vec<ll> par(N,-1),sz(N);
  vec<bool> used(N);
  auto get_sz=[&](this auto get_sz,ll p,ll pre)->void{
    sz[p]=1;
    for(auto e:G[p]){
      if(e.to==pre||used[e.to]) continue;
      get_sz(e.to,p);
      sz[p]+=sz[e.to];
    }
  };
  auto get_cent=[&](this auto get_cent,ll p,ll pre,ll ss)->ll{
    for(auto e:G[p]){
      if(e.to==pre||used[e.to]) continue;
      if(sz[e.to]*2>ss) return get_cent(e.to,p,ss);
    }
    return p;
  };
  auto build=[&](this auto build,ll p,ll pre)->void{
    get_sz(p,-1);
    ll cent=get_cent(p,-1,sz[p]);
    par[cent]=pre,used[cent]=true;
    for(auto e:G[cent]){
      if(!used[e.to]) build(e.to,cent);
    }
  };
  build(0,-1);
  return par;
};