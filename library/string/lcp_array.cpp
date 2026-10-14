#include "template/template.hpp"
template<class Iterator>
vec<ll> lcp_array(Iterator l,Iterator r){
  using T=typename iterator_traits<Iterator>::value_type;
  vec<int> sa_int=lcp_array<T>(vec<T>(l,r),suffix_array<T>(vec<T>(l,r)));
  return vec<ll>(all(sa_int));
}