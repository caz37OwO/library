#pragma once

inline mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l,r) uniform_int_distribution<ll>(l,r)(rng)


inline ll randint(ll l,ll r){
  return uniform_int_distribution<ll>(l,r)(rng);
}

inline ldub randdouble(ldub l,ldub r){
  return uniform_real_distribution<ldub>(l,r)(rng);
}

template<class T>
void shuf(vec<T>& v){
  shuffle(all(v),rng);
}

inline vec<ll> generate_array(ll N,ll L,ll R){
  vec<ll>A(N);
  for(auto& x:A) x=randint(L,R);
  return A;
}

inline vec<ll> generate_permutation(ll N){
  vec<ll>P(N);
  iota(all(P),1);
  shuf(P);
  return P;
}

inline vec<tup2<>> generate_tree(ll N){
  vec<tup2<>>E;
  for(ll i=2;i<=N;i++)
    E.pb(tup(randint(1,i-1),i));
  shuf(E);
  return E;
}

inline vec<tup2<>> generate_graph(ll N,ll M){
  vec<tup2<>>E;
  set<tup2<>>S;

  while((ll)E.size()<M){
    ll u=randint(1,N),v=randint(1,N);
    if(u==v) continue;
    if(u>v) swap(u,v);
    if(S.count(tup(u,v))) continue;
    S.ins(tup(u,v));
    E.pb(tup(u,v));
  }
  return E;
}

inline vec<tup2<>> generate_connected_graph(ll N,ll M){
  assert(M>=N-1);

  vec<tup2<>>E=generate_tree(N);
  set<tup2<>>S;

  for(auto [u,v]:E)
    S.ins(tup(min(u,v),max(u,v)));

  while((ll)E.size()<M){
    ll u=randint(1,N),v=randint(1,N);
    if(u==v) continue;
    if(u>v) swap(u,v);
    if(S.count(tup(u,v))) continue;
    S.ins(tup(u,v));
    E.pb(tup(u,v));
  }

  shuf(E);
  return E;
}

inline vec<tup3<>> generate_weighted_tree(ll N,ll L,ll R){
  vec<tup3<>>E;

  for(ll i=2;i<=N;i++)
    E.pb(tup(randint(1,i-1),i,randint(L,R)));

  shuf(E);
  return E;
}

inline vec<tup3<>> generate_weighted_graph(ll N,ll M,ll L,ll R){
  vec<tup3<>>E;
  set<tup2<>>S;

  while((ll)E.size()<M){
    ll u=randint(1,N),v=randint(1,N);
    if(u==v) continue;
    if(u>v) swap(u,v);
    if(S.count(tup(u,v))) continue;

    S.ins(tup(u,v));
    E.pb(tup(u,v,randint(L,R)));
  }

  return E;
}

inline vec<tup3<>> generate_weighted_connected_graph(ll N,ll M,ll L,ll R){
  assert(M>=N-1);

  vec<tup3<>>E;
  set<tup2<>>S;

  for(ll i=2;i<=N;i++){
    ll p=randint(1,i-1);
    E.pb(tup(p,i,randint(L,R)));
    S.ins(tup(min(p,i),max(p,i)));
  }

  while((ll)E.size()<M){
    ll u=randint(1,N),v=randint(1,N);
    if(u==v) continue;
    if(u>v) swap(u,v);
    if(S.count(tup(u,v))) continue;

    S.ins(tup(u,v));
    E.pb(tup(u,v,randint(L,R)));
  }

  shuf(E);
  return E;
}

inline str generate_string(ll N,char L='a',char R='z'){
  str s;
  for(ll i=0;i<N;i++)
    s+=char(randint(L,R));
  return s;
}

inline str generate_binary_string(ll N){
  str s;
  for(ll i=0;i<N;i++)
    s+=char('0'+randint(0,1));
  return s;
}