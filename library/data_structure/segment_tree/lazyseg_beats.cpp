#include "template/template.hpp"
template<class T=ll>
struct Monoid{
  T max_v,max2_v;
  ll max_count;
  T min_v,min2_v;
  ll min_count;
  T sum_v;
  ll len;
  bool fail;
  static Monoid unit(){return (Monoid){numeric_limits<T>::lowest(),numeric_limits<T>::lowest(),0,numeric_limits<T>::max(),numeric_limits<T>::max(),0,0,0,false};}
  static Monoid leaf(T x){return (Monoid){x,numeric_limits<T>::lowest(),1,x,numeric_limits<T>::max(),1,x,1,false};}
};
template<class T=ll>
struct Operator{
  T lo,hi;
  static Operator id(){return (Operator){numeric_limits<T>::lowest(),numeric_limits<T>::max()};}
  static Operator update(T x){return (Operator){x,x};}
  static Operator chmin(T x){return (Operator){numeric_limits<T>::lowest(),x};}
  static Operator chmax(T x){return (Operator){x,numeric_limits<T>::max()};}
};
template<class T=ll>
void assign_node(Monoid<T> &x,T v){
  x.max_v=x.min_v=v;
  x.max2_v=numeric_limits<T>::lowest();
  x.min2_v=numeric_limits<T>::max();
  x.max_count=x.min_count=x.len;
  x.sum_v=v*x.len;
  x.fail=false;
}
template<class T=ll>
bool apply_chmin(Monoid<T> &x,T v){
  if(x.len==0||x.max_v<=v) return true;
  if(x.max_v==x.min_v){
    assign_node(x,v);
    return true;
  }
  if(x.max2_v>=v) return false;
  T old=x.max_v;
  x.sum_v-=(old-v)*x.max_count;
  if(x.min_v==old) x.min_v=v;
  else if(x.min2_v==old) x.min2_v=v;
  x.max_v=v;
  x.fail=false;
  return true;
}
template<class T=ll>
bool apply_chmax(Monoid<T> &x,T v){
  if(x.len==0||x.min_v>=v) return true;
  if(x.max_v==x.min_v){
    assign_node(x,v);
    return true;
  }
  if(x.min2_v<=v) return false;
  T old=x.min_v;
  x.sum_v+=(v-old)*x.min_count;
  if(x.max_v==old) x.max_v=v;
  else if(x.max2_v==old) x.max2_v=v;
  x.min_v=v;
  x.fail=false;
  return true;
}
template<class T=ll>
Monoid<T> op(Monoid<T> a,Monoid<T> b){
  if(a.len==0){b.fail=false;return b;}
  if(b.len==0){a.fail=false;return a;}
  Monoid<T> r;
  r.max_v=std::max(a.max_v,b.max_v);
  r.max_count=(a.max_v==r.max_v?a.max_count:0)+(b.max_v==r.max_v?b.max_count:0);
  r.max2_v=std::max(a.max_v==r.max_v?a.max2_v:a.max_v,b.max_v==r.max_v?b.max2_v:b.max_v);
  r.min_v=std::min(a.min_v,b.min_v);
  r.min_count=(a.min_v==r.min_v?a.min_count:0)+(b.min_v==r.min_v?b.min_count:0);
  r.min2_v=std::min(a.min_v==r.min_v?a.min2_v:a.min_v,b.min_v==r.min_v?b.min2_v:b.min_v);
  r.sum_v=a.sum_v+b.sum_v;
  r.len=a.len+b.len;
  r.fail=false;
  return r;
}
template<class T=ll>
Monoid<T> mapping(Operator<T> f,Monoid<T> x){
  if(x.len==0){x.fail=false;return x;}
  if(f.lo==f.hi){
    assign_node(x,f.lo);
    return x;
  }
  Monoid<T> r=x;
  if(!apply_chmin(r,f.hi)||!apply_chmax(r,f.lo)){
    x.fail=true;
    return x;
  }
  r.fail=false;
  return r;
}
template<class T=ll>
T clamp_value(T x,T lo,T hi){
  return std::min(std::max(x,lo),hi);
}
template<class T=ll>
Operator<T> composition(Operator<T> f,Operator<T> g){
  return (Operator<T>){clamp_value(g.lo,f.lo,f.hi),clamp_value(g.hi,f.lo,f.hi)};
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
  LST(vec<T> v):LST(to_monoid(v)){}
  LST(vec<Monoid<T>> v){
    e_m=Monoid<T>::unit();
    e_om=Operator<T>::id();
    sz=(ll)v.size(),n=1;
    while(n<sz) n*=2;
    node.resize(2*n-1,e_m);
    lazy.resize(2*n-1,e_om);
    lazy_flag.resize(2*n-1,false);
    for(ll i=0;i<sz;i++) node[i+n-1]=v[i];
    for(ll i=n-2;i>=0;i--) node[i]=op(node[i*2+1],node[i*2+2]);
  }
  static vec<Monoid<T>> to_monoid(vec<T> v){
    vec<Monoid<T>> res(v.size());
    for(ll i=0;i<(ll)v.size();i++) res[i]=Monoid<T>::leaf(v[i]);
    return res;
  }
  void pull(ll k){
    node[k]=op(node[2*k+1],node[2*k+2]);
  }
  void apply_op(ll k,Operator<T> f){
    node[k]=mapping(f,node[k]);
    if(k<n-1){
      lazy[k]=composition(f,lazy[k]);
      lazy_flag[k]=true;
      if(node[k].fail){
        push(k);
        pull(k);
      }
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
    ll m=(l+r)/2;
    apply(a,b,f,2*k+1,l,m);
    apply(a,b,f,2*k+2,m,r);
    pull(k);
  }
  Monoid<T> find(ll a,ll b,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(b<=l||r<=a) return e_m;
    if(a<=l&&r<=b) return node[k];
    push(k);
    Monoid<T> vl=find(a,b,2*k+1,l,(l+r)/2);
    Monoid<T> vr=find(a,b,2*k+2,(l+r)/2,r);
    return op(vl,vr);
  }
  void update(ll a,ll b,T x){apply(a,b,Operator<T>::update(x));}
  void chmin(ll a,ll b,T x){apply(a,b,Operator<T>::chmin(x));}
  void chmax(ll a,ll b,T x){apply(a,b,Operator<T>::chmax(x));}
  void set_val(ll a,T x,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(r-l==1){
      node[k]=Monoid<T>::leaf(x);
      return;
    }
    push(k);
    ll m=(l+r)/2;
    if(a<m) set_val(a,x,2*k+1,l,m);
    else set_val(a,x,2*k+2,m,r);
    pull(k);
  }
  T max(ll a,ll b){return find(a,b).max_v;}
  T min(ll a,ll b){return find(a,b).min_v;}
  T sum(ll a,ll b){return find(a,b).sum_v;}
  T val(ll a){return find(a,a+1).sum_v;}
  template<typename F>
  ll max_right(ll a,F check,Monoid<T> &acc,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(r<=a) return r;
    if(a<=l){
      Monoid<T> nxt=op(acc,node[k]);
      if(check(nxt)){
        acc=nxt;
        return r;
      }
      if(k>=n-1) return l;
    }
    push(k);
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
      Monoid<T> nxt=op(node[k],acc);
      if(check(nxt)){
        acc=nxt;
        return l;
      }
      if(k>=n-1) return r;
    }
    push(k);
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