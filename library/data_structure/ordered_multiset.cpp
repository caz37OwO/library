#include "template/template.hpp"
template<class T=ll>
struct MultiSet{
  struct Node{
    Node *l=0,*r=0;
    ll p,c=1;
    T v,s;
    Node(T x,ll pr):p(pr),v(x),s(x){}
  };
  Node *rt=0;
  mt19937_64 rng{
    static_cast<mt19937_64::result_type>(
      chrono::steady_clock::now().time_since_epoch().count()
    )
  };
  T e(){
    return 0;
  }
  T op(T a,T b){
    return a+b;
  }
  ll cnt(Node *t){
    if(t) return t->c;
    else return 0;
  }
  T get(Node *t){
    if(t) return t->s;
    else return e();
  }
  void up(Node *t){
    if(!t) return;
    t->c=1+cnt(t->l)+cnt(t->r);
    t->s=op(op(get(t->l),t->v),get(t->r));
  }
  void split(Node *t,T k,Node *&l,Node *&r){
    if(!t){
      l=r=0;
      return;
    }
    if(t->v<k) split(t->r,k,t->r,r),l=t;
    else split(t->l,k,l,t->l),r=t;
    up(t);
  }
  void splitk(Node *t,ll k,Node *&l,Node *&r){
    if(!t){
      l=r=0;
      return;
    }
    ll c=cnt(t->l);
    if(k<=c) splitk(t->l,k,l,t->l),r=t;
    else splitk(t->r,k-c-1,t->r,r),l=t;
    up(t);
  }
  void merge(Node *&t,Node *l,Node *r){
    if(!l||!r) t=l?l:r;
    else if(l->p>r->p) merge(l->r,l->r,r),t=l;
    else merge(r->l,l,r->l),t=r;
    up(t);
  }
  void destroy(Node *t){
    if(!t) return;
    destroy(t->l),destroy(t->r);
    delete t;
  }
  MultiSet(){}
  void clear(){
    destroy(rt);
    rt=0;
  }
  bool empty(){
    return cnt(rt)==0;
  }
  void insert(T x){
    Node *l,*r;
    split(rt,x,l,r);
    merge(rt,l,new Node(x,rng())),merge(rt,rt,r);
  }
  void erase(T x){
    Node *l,*r,*m;
    split(rt,x,l,r);
    if(cnt(r)){
      splitk(r,1,m,r);
      if(m->v!=x) merge(r,m,r);
      else delete m;
    }
    merge(rt,l,r);
  }
  ll size(){
    return cnt(rt);
  }
  ll count(T x){
    Node *l,*r,*m;
    split(rt,x,l,r),split(r,x+1,m,r);
    ll res=cnt(m);
    merge(r,m,r),merge(rt,l,r);
    return res;
  }
  T kth(ll k){
    if(k<0) return -INF;
    if(k>=cnt(rt)) return INF;
    Node *t=rt;
    while(t){
      ll c=cnt(t->l);
      if(k==c) return t->v;
      if(k<c) t=t->l;
      else k-=(c+1),t=t->r;
    }
  }
  T operator[](ll k){
    return kth(k);
  }
  ll rank(T x){
    Node *l,*r;
    split(rt,x,l,r);
    ll res=cnt(l);
    merge(rt,l,r);
    return res;
  }
  ll lower_bound(T x) {
    Node *t=rt;
    ll res=0;
    while(t){
      if(t->v>=x) t=t->l;
      else res+=cnt(t->l)+1,t=t->r;
    }
    return res;
  }
  T find(ll l,ll r){
    if(l>=r||l>=cnt(rt)) return e();
    Node *a,*b,*c;
    splitk(rt,r,b,c),splitk(b,l,a,b);
    T res=get(b);
    merge(b,a,b),merge(rt,b,c);
    return res;
  }
};