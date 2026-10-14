#include "template/template.hpp"
template<class T=ll>
struct Monoid{
  T max_v,min_v;
  static Monoid unit(){return (Monoid){numeric_limits<T>::lowest(),numeric_limits<T>::max()};}
};
template<class T=ll>
Monoid<T> op(Monoid<T> a,Monoid<T> b){
  Monoid<T> r;
  r.max_v=max(a.max_v,b.max_v);
  r.min_v=min(a.min_v,b.min_v);
  return r;
}
template<class T=ll>
struct sparse_table{
  ll n,b;
  vec2<Monoid<T>> node;
  Monoid<T> e;
  sparse_table(){}
  sparse_table(ll nn,T x=0):sparse_table(vec<T>(nn,x)){}
  sparse_table(vec<T> v){
    e=Monoid<T>::unit();
    n=(ll)v.size(),b=0;
    while((1<<b)<=n) b++;
    node.assign(b,vec<Monoid<T>>(n,e));
    for(ll i=0;i<n;i++) node[0][i]={v[i],v[i]};
    for(ll i=1;i<b;i++) for(ll j=0;j+(1<<i)<=n;j++) node[i][j]=op(node[i-1][j],node[i-1][j+(1<<(i-1))]);
  }
  Monoid<T> find(ll l,ll r){
    if(l>=r) return e;
    ll i=63-__builtin_clzll(r-l);
    return op(node[i][l],node[i][r-(1<<i)]);
  }
  T max(ll a,ll b){return find(a,b).max_v;}
  T min(ll a,ll b){return find(a,b).min_v;}
};