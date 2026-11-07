#include "template/template.hpp"
template<class T=ll>
struct Monoid{
  T max_v,min_v,sum_v;
  ll len;
  static Monoid unit(){return (Monoid){numeric_limits<T>::lowest(),numeric_limits<T>::max(),0,0};}
  static Monoid leaf(T x){return (Monoid){x,x,x,1};}
};
template<class T=ll>
struct Operator{
  T m,x;
  static Operator id(){return (Operator){1,0};}
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
Monoid<T> mapping(Operator<T> f,Monoid<T> a){
  Monoid<T> r;
  if(f.m>=0){
    r.max_v=a.max_v*f.m+f.x;
    r.min_v=a.min_v*f.m+f.x;
  }else{
    r.max_v=a.min_v*f.m+f.x;
    r.min_v=a.max_v*f.m+f.x;
  }
  r.sum_v=a.sum_v*f.m+f.x*a.len;
  r.len=a.len;
  return r;
}
template<class T=ll>
Operator<T> composition(Operator<T> f,Operator<T> g){
  Operator<T> r;
  r.m=f.m*g.m;
  r.x=f.m*g.x+f.x;
  return r;
}
template<class T=ll>
struct LST{
  ll n,sz;
  vec<Monoid<T>> node;
  vec<Operator<T>> lazy;
  vec<bool> lazy_flag;
  Monoid<T> e_m;
  Operator<T> e_om;
  LST(){}
  LST(ll nn,T x=0):LST(vec<T>(nn,x)){}
  LST(vec<T> v){
    e_m=Monoid<T>::unit();
    e_om=Operator<T>::id();
    sz=(ll)v.size(),n=1;
    while(n<sz) n*=2;
    node.resize(2*n-1,e_m);
    lazy.resize(2*n-1,e_om);
    lazy_flag.resize(2*n-1,false);
    for(ll i=0;i<sz;i++) node[i+n-1]=Monoid<T>::leaf(v[i]);
    for(ll i=n-2;i>=0;i--) node[i]=op(node[i*2+1],node[i*2+2]);
  }
  void pull(ll k){
    node[k]=op(node[2*k+1],node[2*k+2]);
  }
  void apply_op(ll k,Operator<T> f){
    if(node[k].len==0) return;
    node[k]=mapping(f,node[k]);
    if(k<n-1){
      lazy[k]=composition(f,lazy[k]);
      lazy_flag[k]=true;
    }
  }
  void push(ll k){
    if(!lazy_flag[k]) return;
    if(k<n-1){
      apply_op(k*2+1,lazy[k]);
      apply_op(k*2+2,lazy[k]);
    }
    lazy[k]=e_om;
    lazy_flag[k]=false;
  }
  void apply(ll a,ll b,Operator<T> f,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(b<=l||r<=a) return;
    if(a<=l&&r<=b){
      apply_op(k,f);
      return;
    }
    push(k);
    apply(a,b,f,2*k+1,l,(l+r)/2);
    apply(a,b,f,2*k+2,(l+r)/2,r);
    pull(k);
  }
  void add(ll a,ll b,T x){apply(a,b,(Operator<T>){1,x});}
  void update(ll a,ll b,T x){apply(a,b,(Operator<T>){0,x});}
  void multiply(ll a,ll b,T x){apply(a,b,(Operator<T>){x,0});}
  Monoid<T> find(ll a,ll b,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    push(k);
    if(b<=l||r<=a) return e_m;
    if(a<=l&&r<=b) return node[k];
    Monoid<T> vl=find(a,b,2*k+1,l,(l+r)/2);
    Monoid<T> vr=find(a,b,2*k+2,(l+r)/2,r);
    return op(vl,vr);
  }
  T max(ll a,ll b){return find(a,b).max_v;}
  T min(ll a,ll b){return find(a,b).min_v;}
  T sum(ll a,ll b){return find(a,b).sum_v;}
  T val(ll a){return find(a,a+1).sum_v;}
  ll lower_bound(T x,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    push(k);
    if(node[k].max_v<x) return sz;
    if(k>=n-1) return l;
    ll m=(l+r)/2;
    if(node[2*k+1].max_v>=x) return lower_bound(x,2*k+1,l,m);
    else return lower_bound(x,2*k+2,m,r);
  }
  template<typename F>
  ll max_right(ll a,F check,Monoid<T> &acc,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    push(k);
    if(r<=a) return r;
    if(a<=l){
      Monoid<T> nxt=op(acc,node[k]);
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
    push(k);
    if(b<=l) return l;
    if(r<=b){
      Monoid<T> nxt=op(node[k],acc);
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