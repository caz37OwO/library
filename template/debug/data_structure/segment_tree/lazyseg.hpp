template<class T>
concept DebugLazySegmentTree = requires(T& x, ll i) {
  x.sz;
  x.val(i);
  x.lazyMul;
  x.lazyAdd;
};

template<DebugLazySegmentTree T>
void debug_print(T& seg) {
  cerr << "[";

  for (ll i = 0; i < seg.sz; i++) {
    if (i) cerr << ", ";
    debug_print(seg.val(i));
  }

  cerr << "]";
}
