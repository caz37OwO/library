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
  T a,b,lo,hi;
  bool has_lo,has_hi;
  static Operator id(){return (Operator){1,0,T{},T{},false,false};}
  static Operator affine(T a,T b){return (Operator){a,b,T{},T{},false,false};}
  static Operator update(T x){return (Operator){0,x,T{},T{},false,false};}
  static Operator add(T x){return affine(1,x);}
  static Operator chmin(T x){return (Operator){1,0,T{},x,false,true};}
  static Operator chmax(T x){return (Operator){1,0,x,T{},true,false};}
};
template<class T=ll>
T clamp_value(T x,Operator<T> f){
  if(f.has_lo&&x<f.lo) x=f.lo;
  if(f.has_hi&&x>f.hi) x=f.hi;
  return x;
}
template<class T=ll>
T constant_value(Operator<T> f){
  if(f.has_lo&&f.has_hi&&f.lo==f.hi) return f.lo;
  return clamp_value(f.b,f);
}
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
  if(x.max_v==x.min_v){assign_node(x,v);return true;}
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
  if(x.max_v==x.min_v){assign_node(x,v);return true;}
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
  r.max_v=max(a.max_v,b.max_v);
  r.max_count=(a.max_v==r.max_v?a.max_count:0)+(b.max_v==r.max_v?b.max_count:0);
  r.max2_v=max(a.max_v==r.max_v?a.max2_v:a.max_v,b.max_v==r.max_v?b.max2_v:b.max_v);
  r.min_v=min(a.min_v,b.min_v);
  r.min_count=(a.min_v==r.min_v?a.min_count:0)+(b.min_v==r.min_v?b.min_count:0);
  r.min2_v=min(a.min_v==r.min_v?a.min2_v:a.min_v,b.min_v==r.min_v?b.min2_v:b.min_v);
  r.sum_v=a.sum_v+b.sum_v;
  r.len=a.len+b.len;
  r.fail=false;
  return r;
}
template<class T=ll>
Monoid<T> mapping(Operator<T> f,Monoid<T> x){
  if(x.len==0){x.fail=false;return x;}
  if(f.a==0||(f.has_lo&&f.has_hi&&f.lo==f.hi)){
    assign_node(x,constant_value(f));
    return x;
  }
  Monoid<T> r=x;
  T old_max=x.max_v,old_max2=x.max2_v,old_min=x.min_v,old_min2=x.min2_v;
  ll old_max_count=x.max_count,old_min_count=x.min_count;
  r.sum_v=f.a*x.sum_v+f.b*x.len;
  if(f.a>0){
    r.max_v=f.a*old_max+f.b;
    r.max2_v=(old_max2==numeric_limits<T>::lowest()?numeric_limits<T>::lowest():f.a*old_max2+f.b);
    r.max_count=old_max_count;
    r.min_v=f.a*old_min+f.b;
    r.min2_v=(old_min2==numeric_limits<T>::max()?numeric_limits<T>::max():f.a*old_min2+f.b);
    r.min_count=old_min_count;
  }else{
    r.max_v=f.a*old_min+f.b;
    r.max2_v=(old_min2==numeric_limits<T>::max()?numeric_limits<T>::lowest():f.a*old_min2+f.b);
    r.max_count=old_min_count;
    r.min_v=f.a*old_max+f.b;
    r.min2_v=(old_max2==numeric_limits<T>::lowest()?numeric_limits<T>::max():f.a*old_max2+f.b);
    r.min_count=old_max_count;
  }
  if(f.has_hi&&!apply_chmin(r,f.hi)){x.fail=true;return x;}
  if(f.has_lo&&!apply_chmax(r,f.lo)){x.fail=true;return x;}
  r.fail=false;
  return r;
}
template<class T=ll>
struct Bound{
  bool finite;
  T val;
  int inf;
};
template<class T=ll>
Bound<T> eval_limit(Operator<T> f,bool finite,T x,int inf){
  if(finite) return (Bound<T>){true,clamp_value(f.a*x+f.b,f),0};
  int d=(f.a>0?inf:-inf);
  if(d<0){
    if(f.has_lo) return (Bound<T>){true,f.lo,0};
    return (Bound<T>){false,T{},-1};
  }
  if(f.has_hi) return (Bound<T>){true,f.hi,0};
  return (Bound<T>){false,T{},1};
}
template<class T=ll>
Operator<T> composition(Operator<T> f,Operator<T> g){
  auto is_constant=[](Operator<T> z){return z.a==0||(z.has_lo&&z.has_hi&&z.lo==z.hi);};
  if(is_constant(f)) return Operator<T>::update(constant_value(f));
  if(is_constant(g)) return Operator<T>::update(clamp_value(f.a*constant_value(g)+f.b,f));
  Operator<T> r=Operator<T>::affine(f.a*g.a,f.a*g.b+f.b);
  Bound<T> gl=g.has_lo?(Bound<T>){true,g.lo,0}:(Bound<T>){false,T{},-1};
  Bound<T> gh=g.has_hi?(Bound<T>){true,g.hi,0}:(Bound<T>){false,T{},1};
  Bound<T> low,high;
  if(f.a>0){
    low=eval_limit(f,gl.finite,gl.val,gl.inf);
    high=eval_limit(f,gh.finite,gh.val,gh.inf);
  }else{
    low=eval_limit(f,gh.finite,gh.val,gh.inf);
    high=eval_limit(f,gl.finite,gl.val,gl.inf);
  }
  r.has_lo=low.finite;
  r.has_hi=high.finite;
  if(low.finite) r.lo=low.val;
  if(high.finite) r.hi=high.val;
  if(r.has_lo&&r.has_hi&&r.lo==r.hi) return Operator<T>::update(r.lo);
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
    }else assert(!node[k].fail);
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
  Monoid<T> val(ll a){return find(a,a+1);}
  void update(ll a,ll b,T x){apply(a,b,Operator<T>::update(x));}
  void affine(ll a,ll b,T m,T x){apply(a,b,Operator<T>::affine(m,x));}
  void add(ll a,ll b,T x){apply(a,b,Operator<T>::add(x));}
  void chmin(ll a,ll b,T x){apply(a,b,Operator<T>::chmin(x));}
  void chmax(ll a,ll b,T x){apply(a,b,Operator<T>::chmax(x));}
  void set_val(ll a,T x,ll k=0,ll l=0,ll r=-1){
    if(r<0) r=n;
    if(r-l==1){node[k]=Monoid<T>::leaf(x);return;}
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
      if(check(nxt)){acc=nxt;return r;}
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
      if(check(nxt)){acc=nxt;return l;}
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