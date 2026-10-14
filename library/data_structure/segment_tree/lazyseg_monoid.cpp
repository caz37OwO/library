#include "template/template.hpp"
struct Monoid{
  ll val,len;
  static Monoid unit(){return (Monoid){0,0};}
};
struct Operator{
  ll a,b;
  static Operator id(){return (Operator){1,0};}
};
Monoid op(Monoid a,Monoid b){
  Monoid res;
  res.val=a.val+b.val;
  res.len=a.len+b.len;
  return res;
}
Monoid mapping(Operator f,Monoid x){
  Monoid res;
  res.val=f.a*x.val+f.b*x.len;
  res.len=x.len;
  return res;
}
Operator composition(Operator f,Operator g){
  Operator res;
  res.a=f.a*g.a,res.b=f.a*g.b+f.b;
  return res;
}
struct LST{
  ll n,sz;
  vec<Monoid> node;
  vec<Operator> lazy;
  vec<bool> lazy_flag;
  Monoid e_m;
  Operator e_om;
  LST(){}
  LST(ll nn,Monoid x=Monoid::unit()):LST(vec<Monoid>(nn,x)){}
  LST(vec<Monoid> v){
    e_m=Monoid::unit();
    e_om=Operator::id();
    sz=(ll)v.size(),n=1;
    while(n<sz) n*=2;
    node.resize(2*n-1,e_m);
    lazy.resize(2*n-1,e_om);
    lazy_flag.resize(2*n-1,false);
    for(ll i=0;i<sz;i++) node[i+n-1]=v[i];
    for(ll i=n-2;i>=0;i--) node[i]=op(node[i*2+1],node[i*2+2]);
  }
  void apply_op(ll k,Operator f){
    node[k]=mapping(f,node[k]);
    lazy[k]=composition(f,lazy[k]);
    lazy_flag[k]=true;
  }
  void push(ll k,ll l,ll r){
    if(!lazy_flag[k]) return;
    if(r-l>1){
      apply_op(k*2+1,lazy[k]);
      apply_op(k*2+2,lazy[k]);
    }
    lazy[k]=e_om;
    lazy_flag[k]=false;
  }
  void apply(ll a,ll b,Operator f,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    push(k,l,r);
    if(b<=l||r<=a) return;
    if(a<=l&&r<=b) apply_op(k,f);
    else{
      apply(a,b,f,2*k+1,l,(l+r)/2);
      apply(a,b,f,2*k+2,(l+r)/2,r);
      node[k]=op(node[2*k+1],node[2*k+2]);
    }
  }
  Monoid find(ll a,ll b,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    push(k,l,r);
    if(b<=l||r<=a) return e_m;
    if(a<=l&&r<=b) return node[k];
    Monoid vl=find(a,b,2*k+1,l,(l+r)/2);
    Monoid vr=find(a,b,2*k+2,(l+r)/2,r);
    return op(vl,vr);
  }
  Monoid val(ll a){return find(a,a+1);}
  template<typename F>
  ll max_right(ll a,F check,Monoid &acc,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    push(k,l,r);
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
    push(k,l,r);
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