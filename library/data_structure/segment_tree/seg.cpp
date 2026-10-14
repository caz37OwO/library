#include "template/template.hpp"
template<class T=ll>
struct Monoid{
  T max_v,min_v,sum_v;
  ll len;
  static Monoid unit(){return (Monoid){numeric_limits<T>::lowest(),numeric_limits<T>::max(),0,0};}
  static Monoid leaf(T x){return (Monoid){x,x,x,1};}
};
template<class T=ll>
Monoid<T> op(Monoid<T> a,Monoid<T> b){
  Monoid<T> r;
  r.max_v=max(a.max_v,b.max_v);
  r.min_v=min(a.min_v,b.min_v);
  r.sum_v=a.sum_v+b.sum_v;
  r.len=a.len+b.len;
  return r;
}
template<class T=ll>
Monoid<T> affine(Monoid<T> a,T m,T x){
  Monoid<T> r;
  if(m>=0){
    r.max_v=a.max_v*m+x;
    r.min_v=a.min_v*m+x;
  }else{
    r.max_v=a.min_v*m+x;
    r.min_v=a.max_v*m+x;
  }
  r.sum_v=a.sum_v*m+x*a.len;
  r.len=a.len;
  return r;
}
template<class T=ll>
struct SegTree{
  ll n,sz;
  vec<Monoid<T>> node;
  Monoid<T> e;
  SegTree(){}
  SegTree(ll nn,T x=0):SegTree(vec<T>(nn,x)){}
  SegTree(vec<T> v){
    e=Monoid<T>::unit();
    sz=(ll)v.size(),n=1;
    while(n<sz) n*=2;
    node.resize(2*n-1,e);
    for(ll i=0;i<sz;i++) node[i+n-1]=Monoid<T>::leaf(v[i]);
    for(ll i=n-2;i>=0;i--) node[i]=op(node[i*2+1],node[i*2+2]);
  }
  void apply(ll i,T m,T x){
    i+=n-1;
    node[i]=affine(node[i],m,x);
    while(i>0){
      i=(i-1)/2;
      node[i]=op(node[i*2+1],node[i*2+2]);
    }
  }
  void add(ll i,T x){apply(i,1,x);}
  void update(ll i,T x){apply(i,0,x);}
  void multiply(ll i,T x){apply(i,x,0);}
  Monoid<T> find(ll a,ll b,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(b<=l||r<=a) return e;
    if(a<=l&&r<=b) return node[k];
    Monoid<T> vl=find(a,b,2*k+1,l,(l+r)/2);
    Monoid<T> vr=find(a,b,2*k+2,(l+r)/2,r);
    return op(vl,vr);
  }
  T max(ll a,ll b){return find(a,b).max_v;}
  T min(ll a,ll b){return find(a,b).min_v;}
  T sum(ll a,ll b){return find(a,b).sum_v;}
  T val(ll a){return node[a+n-1].sum_v;}
  ll lower_bound(T x,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(node[k].max_v<x) return sz;
    if(k>=n-1) return l;
    ll m=(l+r)/2;
    if(node[2*k+1].max_v>=x) return lower_bound(x,2*k+1,l,m);
    else return lower_bound(x,2*k+2,m,r);
  }
  template<typename F>
  ll max_right(ll a,F check,Monoid<T> &acc,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(r<=a) return r;
    if(a<=l){
      Monoid<T> nxt=(acc.len==0)?node[k]:op(acc,node[k]);
      if(check(nxt)){
        acc=nxt;
        return r;
      }
      if(k>=n-1) return l;
    }
    ll m=(l+r)/2;
    ll res=max_right(a,check,acc,2*k+1,l,m);
    if(res<m) return res;
    return max_right(a,check,acc,2*k+2,m,r);
  }
  template<typename F>
  ll max_right(ll a,F check){
    Monoid<T> acc=Monoid<T>::unit();
    return std::min(max_right(a,check,acc),sz);
  }
  template<typename F>
  ll min_left(ll b,F check,Monoid<T> &acc,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(b<=l) return l;
    if(r<=b){
      Monoid<T> nxt=(acc.len==0)?node[k]:op(node[k],acc);
      if(check(nxt)){
        acc=nxt;
        return l;
      }
      if(k>=n-1) return r;
    }
    ll m=(l+r)/2;
    ll res=min_left(b,check,acc,2*k+2,m,r);
    if(res>m) return res;
    return min_left(b,check,acc,2*k+1,l,m);
  }
  template<typename F>
  ll min_left(ll b,F check){
    Monoid<T> acc=Monoid<T>::unit();
    return min_left(b,check,acc);
  }
};