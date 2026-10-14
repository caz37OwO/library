#include "template/template.hpp"
template<class Iterator>
auto rle(Iterator l, Iterator r){
  using T=typename iterator_traits<Iterator>::value_type;
  vector<tuple<T,ll>> res;
  for(auto it=l;it!=r;it++){
    if(res.empty()||get<0>(res.back())!=*it) res.pb(tup(*it,1));
    else get<1>(res.back())++;
  }
  return res;
}