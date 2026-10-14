#pragma once

#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;


// ============================================================
// debug_to_string
// ============================================================

string debug_to_string(long long x) {
  if (x >= (long long)1e18) return "INF";
  if (x <= -(long long)1e18) return "-INF";
  return to_string(x);
}

string debug_to_string(int x) {
  return to_string(x);
}

string debug_to_string(char x) {
  return string(1, x);
}

string debug_to_string(string x) {
  return x;
}

string debug_to_string(long double x) {
  ostringstream oss;
  oss << fixed << setprecision(6) << x;
  return oss.str();
}

template<class T>
string debug_to_string(T x) {
  if constexpr (requires { x.val(); }) {
    return to_string(x.val());
  }
  return "?";
}

string debug_to_string(__int128 x) {
  if (x >= (__int128)1e18) return "INF";
  if (x <= -(__int128)1e18) return "-INF";

  if (x == 0) return "0";

  bool neg = x < 0;
  if (neg) x = -x;

  string s;
  while (x > 0) {
    s += char('0' + x % 10);
    x /= 10;
  }

  if (neg) s += '-';

  reverse(s.begin(), s.end());
  return s;
}


// ============================================================
// 基本型
// ============================================================

template<class T>
requires is_arithmetic_v<T>
void debug_print(T x) {
  cerr << x;
}

template<class T>
requires requires(const T& x) {
  x.val();
}
void debug_print(const T& x) {
  cerr << x.val();
}

void debug_print(long double x) {
  auto flags = cerr.flags();
  auto precision = cerr.precision();

  cerr << fixed << setprecision(6) << x;

  cerr.flags(flags);
  cerr.precision(precision);
}

void debug_print(const string& x) {
  cerr << x;
}

void debug_print(const char* x) {
  cerr << x;
}

void debug_print(__int128 x) {
  cerr << debug_to_string(x);
}


// ============================================================
// tuple
// ============================================================

template<class Tuple, size_t... I>
void debug_tuple(const Tuple& t, index_sequence<I...>) {
  ((cerr << (I ? ", " : ""), debug_print(get<I>(t))), ...);
}

template<class... Ts>
void debug_print(const tuple<Ts...>& t) {
  cerr << "(";
  debug_tuple(t, index_sequence_for<Ts...>{});
  cerr << ")";
}


template<size_t N>
void debug_print(const bitset<N>& b) {
  cerr << b;
}


// ============================================================
// Edge
// ============================================================

template<class T>
concept EdgeLike = requires(T x) {
  x.to;
  x.w;
  x.num;
};

template<EdgeLike T>
void debug_print(const T& e) {
  cerr << "{to:";
  debug_print(e.to);
  cerr << ", w:";
  debug_print(e.w);
  cerr << ", num:";
  debug_print(e.num);
  cerr << "}";
}


// ============================================================
// vector 補助
// ============================================================

template<class T>
constexpr bool is_simple_number() {
  return is_integral_v<T> || requires(T x) {
    x.val();
  };
}

template<class T>
void collect_width(const vector<T>& v, int& width) {
  if constexpr (requires(T x) {
    x.begin();
  }) {
    for (auto& x : v) {
      collect_width(x, width);
    }
  }
  else if constexpr (is_simple_number<T>()) {
    for (auto x : v) {
      width = max(width, (int)debug_to_string(x).size());
    }

    width = min(width, 10);
  }
}

template<class T>
void debug_print_vec(const vector<T>& v, int depth, int width = -1) {
  if (width == -1) {
    collect_width(v, width);
  }

  if constexpr (requires(T x) {
    x.begin();
  }) {
    cerr << "[\n";

    for (auto& x : v) {
      cerr << string(depth + 1, ' ');
      debug_print_vec(x, depth + 1, width);
      cerr << "\n";
    }

    cerr << string(depth, ' ') << "]";
  }
  else {
    cerr << "[";

    for (int i = 0; i < (int)v.size(); i++) {
      if (i) cerr << ", ";

      if constexpr (is_simple_number<T>()) {
        cerr << setw(width) << debug_to_string(v[i]);
      }
      else {
        debug_print(v[i]);
      }
    }

    cerr << "]";
  }
}

template<class T>
void debug_print(const vector<T>& v) {
  debug_print_vec(v, 0);
}


// ============================================================
// set / map
// ============================================================

template<class T>
void debug_print(const set<T>& s) {
  cerr << "{";

  int i = 0;
  for (auto x : s) {
    if (i++) cerr << ", ";
    debug_print(x);
  }

  cerr << "}";
}

template<class K, class V>
void debug_print(const map<K, V>& m) {
  cerr << "{\n";

  for (auto [k, v] : m) {
    cerr << "  ";
    debug_print(k);
    cerr << " : ";
    debug_print(v);
    cerr << "\n";
  }

  cerr << "}";
}

template<class T>
void debug_print(const multiset<T>& s) {
  cerr << "{";

  int i = 0;
  for (auto x : s) {
    if (i++) cerr << ", ";
    debug_print(x);
  }

  cerr << "}";
}


template<class K, class V>
void debug_print(const unordered_map<K, V>& m) {
  cerr << "{\n";

  for (auto [k, v] : m) {
    cerr << "  ";
    debug_print(k);
    cerr << " : ";
    debug_print(v);
    cerr << "\n";
  }

  cerr << "}";
}


template<class T>
void debug_print(const unordered_set<T>& s) {
  cerr << "{";

  int i = 0;
  for (auto x : s) {
    if (i++) cerr << ", ";
    debug_print(x);
  }

  cerr << "}";
}


// ============================================================
// queue / priority_queue
// ============================================================

template<class T>
void debug_print(const queue<T>& q) {
  auto x = q;

  cerr << "<";

  int i = 0;
  while (!x.empty()) {
    if (i++) cerr << ", ";
    debug_print(x.front());
    x.pop();
  }

  cerr << ">";
}

template<class T>
void debug_print(const priority_queue<T>& q) {
  auto x = q;

  cerr << "<";

  int i = 0;
  while (!x.empty()) {
    if (i++) cerr << ", ";
    debug_print(x.top());
    x.pop();
  }

  cerr << ">";
}

template<class T>
void debug_print(const deque<T>& q) {
  cerr << "<";

  int i = 0;
  for (auto x : q) {
    if (i++) cerr << ", ";
    debug_print(x);
  }

  cerr << ">";
}


template<class T>
void debug_print(const stack<T>& s) {
  auto x = s;

  cerr << "<";

  int i = 0;
  while (!x.empty()) {
    if (i++) cerr << ", ";
    debug_print(x.top());
    x.pop();
  }

  cerr << ">";
}


// ============================================================
// debug
// ============================================================

#ifdef LOCAL

#define debug(x) \
  cerr << #x << " = "; \
  debug_print(x); \
  cerr << "\n";

#else

#define debug(x)

#endif

#include "data_structure/segment_tree/seg.hpp"
#include "data_structure/segment_tree/lazyseg.hpp"
#include "data_structure/compress.hpp"
#include "data_structure/ordered_set.hpp"
#include "data_structure/ordered_multiset.hpp"
#include "data_structure/uf.hpp"