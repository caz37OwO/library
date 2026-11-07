struct LCA{
  ll N,lg;
  gvec2 G;
  vec2<ll> par;
  vec<ll> dep,dis;
  LCA(gvec2 g,ll root=0):N((ll)g.size()),G(g),lg(0){
    while((1LL<<lg)<=N) lg++;
    build(root);
  }
  void build(ll root){
    dep.assign(N,INF);
    dis.assign(N,0);
    par.assign(lg,vec<ll>(N,-1));
    que<ll> BFS;
    dep[root]=0;
    BFS.push(root);
    while(!BFS.empty()){
      ll p=BFS.front();
      BFS.pop();
      for(auto e:G[p]){
        if(!chmin(dep[e.to],dep[p]+1)) continue;
        dis[e.to]=dis[p]+e.w;
        par[0][e.to]=p;
        BFS.push(e.to);
      }
    }
    for(ll k=1;k<lg;k++){
      for(ll p=0;p<N;p++){
        if(par[k-1][p]==-1) continue;
        par[k][p]=par[k-1][par[k-1][p]];
      }
    }
  }
  ll jump(ll p,ll k){
    if(k<0||dep[p]<k) return -1;
    for(ll i=0;i<lg;i++) if((k>>i)&1) p=par[i][p];
    return p;
  }
  ll lca(ll u,ll v){
    if(dep[u]<dep[v]) swap(u,v);
    u=jump(u,dep[u]-dep[v]);
    if(u==v) return u;
    for(ll k=lg-1;k>=0;k--){
      if(par[k][u]==par[k][v]) continue;
      u=par[k][u],v=par[k][v];
    }
    return par[0][u];
  }
  ll dist(ll u,ll v){
    ll p=lca(u,v);
    return dep[u]+dep[v]-2*dep[p];
  }
  ll wdist(ll u,ll v){
    ll p=lca(u,v);
    return dis[u]+dis[v]-2*dis[p];
  }
  ll kth_on_path(ll u,ll v,ll k){
    ll p=lca(u,v);
    ll a=dep[u]-dep[p],b=dep[v]-dep[p];
    if(k<0||a+b<k) return -1;
    if(k<=a) return jump(u,k);
    return jump(v,a+b-k);
  }
  ll parent(ll v){return par[0][v];}
};