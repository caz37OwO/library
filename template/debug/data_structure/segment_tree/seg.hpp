template<class T>
concept DebugSegmentTree = requires(T& x, ll i) {
  x.sz;
  x.val(i);
} && !requires(T& x) {
  x.lazyMul;
};

template<DebugSegmentTree T>
void debug_print(T& seg) {
  cerr << "[";

  for (ll i = 0; i < seg.sz; i++) {
    if (i) cerr << ", ";
    debug_print(seg.val(i));
  }

  cerr << "]";
}
