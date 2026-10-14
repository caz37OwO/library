#include "template/template.hpp"
struct MCF{
  struct Edge_MCF{
    ll to,rev,cap,cost;
  };
  ll N;
  vec2<Edge_MCF> G;
  vec<ll> h,dist,prevv,preve;
  bool initial_calc;
  MCF(ll n):N(n),G(n),h(n,0),prevv(n),preve(n),initial_calc(false){}
  void add(ll from,ll to,ll cap,ll cost){
    G[from].pb({to,(ll)G[to].size(),cap,cost});
    G[to].pb({from,(ll)G[from].size()-1,0,-cost});
  }
  tup2<ll> min_flow(ll s,ll t,ll f){
    if(!initial_calc){
      initial_calc=true;
      h.assign(N,0);
      bool update=true;
      for(ll step=0;step<N&&update;step++){
        update=false;
        for(ll v=0;v<N;v++){
          for(auto &e:G[v]){
            if(e.cap>0&&h[e.to]>h[v]+e.cost){
              h[e.to]=h[v]+e.cost;
              update=true;
            }
          }
        }
      }
    }
    ll res=0,flowed=0;
    while(f>0){
      pque<tup2<>> pq;
      dist.assign(N,INF);
      dist[s]=0;
      pq.push(tup(0,s));
      while(!pq.empty()){
        auto [d,v]=pq.top();
        pq.pop();
        if(dist[v]<d) continue;
        for(ll i=0;i<(ll)G[v].size();i++){
          Edge_MCF &e=G[v][i];
          if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
            dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
            prevv[e.to]=v;
            preve[e.to]=i;
            pq.push(tup(dist[e.to],e.to));
          }
        }
      }
      if(dist[t]==INF) return tup(flowed,res);
      for(ll v=0;v<N;v++){
        if(dist[v]<INF) h[v]+=dist[v];
      }
      ll d=f;
      for(ll v=t;v!=s;v=prevv[v]) d=min(d,G[prevv[v]][preve[v]].cap);
      f-=d,flowed+=d,res+=d*(h[t]-h[s]);
      for(ll v=t;v!=s;v=prevv[v]){
        Edge_MCF &e=G[prevv[v]][preve[v]];
        e.cap-=d;
        G[v][e.rev].cap+=d;
      }
    }
    return tup(flowed,res);
  }
};