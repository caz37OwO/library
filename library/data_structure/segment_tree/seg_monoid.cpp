#include "template/template.hpp"
struct Monoid{
  ll val;
  static Monoid unit(){return (Monoid){0};}
};
Monoid op(Monoid a,Monoid b){
  Monoid res;
  res.val=a.val+b.val;
  return res;
}
struct SegTree{
  ll n,sz;
  vec<Monoid> node;
  Monoid e;
  SegTree(){}
  SegTree(ll nn,Monoid x=Monoid::unit()):SegTree(vec<Monoid>(nn,x)){}
  SegTree(vec<Monoid> v){
    e=Monoid::unit();
    sz=(ll)v.size(),n=1;
    while(n<sz) n*=2;
    node.resize(2*n-1,e);
    for(ll i=0;i<sz;i++) node[i+n-1]=v[i];
    for(ll i=n-2;i>=0;i--) node[i]=op(node[i*2+1],node[i*2+2]);
  }
  void update(ll i,Monoid x){
    i+=n-1;
    node[i]=x;
    while(i>0){
      i=(i-1)/2;
      node[i]=op(node[i*2+1],node[i*2+2]);
    }
  }
  Monoid find(ll a,ll b,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(b<=l||r<=a) return e;
    if(a<=l&&r<=b) return node[k];
    Monoid vl=find(a,b,2*k+1,l,(l+r)/2);
    Monoid vr=find(a,b,2*k+2,(l+r)/2,r);
    return op(vl,vr);
  }
  Monoid val(ll a){return node[a+n-1];}
  template<typename F>
  ll max_right(ll a,F check,Monoid &acc,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(r<=a) return r;
    if(a<=l){
      Monoid nxt=op(acc,node[k]);
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
    Monoid acc=Monoid::unit();
    return std::min(max_right(a,check,acc),sz);
  }
  template<typename F>
  ll min_left(ll b,F check,Monoid &acc,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(b<=l) return l;
    if(r<=b){
      Monoid nxt=op(node[k],acc);
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
    Monoid acc=Monoid::unit();
    return min_left(b,check,acc);
  }
};