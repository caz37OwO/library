#include "template/template.hpp"
struct Dinic{
  struct Edge_Dinic{
    ll to,rev,cap,original_cap;
  };
  ll N;
  vec2<Edge_Dinic> G;
  vec<ll> dist,it;
  Dinic(ll n):N(n),G(n),it(n){}
  void add(ll from,ll to,ll cap){
    G[from].pb({to,(ll)G[to].size(),cap,cap});
    G[to].pb({from,(ll)G[from].size()-1LL,0,0});
  }
  void bfs(ll s){
    ll p;
    que<ll> BFS;
    dist.assign(N,INF);
    dist[s]=0;
    BFS.push(s);
    while(!BFS.empty()){
      p=BFS.front();
      BFS.pop();
      for(auto e:G[p]){
        if(e.cap==0) continue;
        if(chmin(dist[e.to],dist[p]+1)) BFS.push(e.to);
      }
    }
  }
  ll dfs(ll p,ll t,ll f){
    if(p==t) return f;
    ll res=0;
    for(;it[p]<(ll)G[p].size();it[p]++){
      auto &e=G[p][it[p]];
      if(e.cap==0||dist[e.to]-dist[p]!=1) continue;
      ll d=dfs(e.to,t,min(f-res,e.cap));
      if(!d) continue;
      e.cap-=d,G[e.to][e.rev].cap+=d;
      res+=d;
      if(res==f) break;
    }
    return res;
  }
  ll maxflow(ll s,ll t){
    ll flow=0;
    while(true){
      bfs(s);
      if(dist[t]==INF) break;
      it.assign(N,0);
      flow+=dfs(s,t,INF);
    }
    return flow;
  }
};