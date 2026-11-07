template<class T>
concept DebugSegmentTree = requires(T& x, long long i) {
  x.sz;
  x.val(i);
} && !requires(T& x) {
  x.lazyMul;
};

template<DebugSegmentTree T>
void debug_print(T& seg) {
  cerr << "[";

  for (long long i = 0; i < seg.sz; i++) {
    if (i) cerr << ", ";
    debug_print(seg.val(i));
  }

  cerr << "]";
}
