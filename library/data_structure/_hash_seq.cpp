#include "template/template.hpp"
struct SeqHash{
  inline static ll MOD1=999990373,MOD2=1000003777;
  inline static ll BASE1=3737,BASE2=373737;
  inline static ll INV_BASE1=384529346,INV_BASE2=662535246;
  inline static vec<ll> pow1={1},pow2={1};
  static void expand(ll n){
    while((ll)pow1.size()<=n) pow1.pb(pow1.back()*BASE1%MOD1),pow2.pb(pow2.back()*BASE2%MOD2);
  }
  deque<tup2<ll>> v;
  ll v1,v2,p1,p2;
  tup2<ll> norm(ll a,ll b){return tup((a%MOD1+MOD1)%MOD1,(b%MOD2+MOD2)%MOD2);}
  template<class T>
  tup2<ll> hash_value(const T &x){
    auto [h1,h2]=norm(x,x);
    return tup(h1+1,h2+1);
  }
  SeqHash():v1(0),v2(0),p1(1),p2(1){}
  SeqHash(ll x):SeqHash(){push_back(x);}
  SeqHash(const str &s):SeqHash(){for(auto c:s) push_back(c);}
  template<class T>
  SeqHash(const vec<T> &a):SeqHash(){for(auto x:a) push_back(x);}
  template<class T>
  void push_back(const T &x){
    auto [x1,x2]=hash_value(x);
    v1=(v1*BASE1+x1)%MOD1,v2=(v2*BASE2+x2)%MOD2;
    p1=p1*BASE1%MOD1,p2=p2*BASE2%MOD2;
    v.pb(tup(x1,x2));
  }
  template<class T>
  void push_front(const T &x){
    auto [x1,x2]=hash_value(x);
    v1=(x1*p1+v1)%MOD1,v2=(x2*p2+v2)%MOD2;
    p1=p1*BASE1%MOD1,p2=p2*BASE2%MOD2;
    v.pf(tup(x1,x2));
  }
  void pop_back(){
    auto [x1,x2]=v.back();
    auto [nv1,nv2]=norm(v1-x1,v2-x2);
    v1=nv1*INV_BASE1%MOD1,v2=nv2*INV_BASE2%MOD2;
    p1=p1*INV_BASE1%MOD1,p2=p2*INV_BASE2%MOD2;
    v.pob();
  }
  void pop_front(){
    auto [x1,x2]=v.front();
    p1=p1*INV_BASE1%MOD1,p2=p2*INV_BASE2%MOD2;
    auto [nv1,nv2]=norm(v1-x1*p1,v2-x2*p2);
    v1=nv1,v2=nv2;
    v.pof();
  }
  SeqHash operator+(const SeqHash &a)const{
    SeqHash r=*this;
    r.v1=(r.v1*a.p1+a.v1)%MOD1,r.v2=(r.v2*a.p2+a.v2)%MOD2;
    r.p1=r.p1*a.p1%MOD1,r.p2=r.p2*a.p2%MOD2;
    r.v.insert(r.v.end(),all(a.v));
    return r;
  }
  bool operator==(const SeqHash &a)const{return p1==a.p1&&p2==a.p2&&v1==a.v1&&v2==a.v2;}
  bool operator!=(const SeqHash &a)const{return !(*this==a);}
  bool operator<(const SeqHash &a)const{return tie(p1,p2,v1,v2)<tie(a.p1,a.p2,a.v1,a.v2);}
  bool operator>(const SeqHash &a)const{return a<*this;}
  template<class T>
  void update(ll i,const T &x){
    if(i<0||(ll)v.size()<=i) return;
    expand(v.size());
    auto [x1,x2]=hash_value(x);
    auto [o1,o2]=v[i];
    tie (v1,v2)=norm(v1+(x1-o1)*pow1[v.size()-1-i],v2+(x2-o2)*pow2[v.size()-1-i]);
    v[i]=tup(x1,x2);
  }
};