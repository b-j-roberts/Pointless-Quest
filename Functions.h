#ifndef __FUNCTIONS_H_INCLUDED__
#define __FUNCTIONS_H_INCLUDED__

template <typename T1, typename T2>
decltype(auto) max(T1 a, T2 b) {
  return (a < b ? b : a);
}

template <typename T1, typename T2>
decltype(auto) min(T1 a, T2 b) {
  return (a > b ? b : a);
}

#endif
