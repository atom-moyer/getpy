// A group of fast and memory efficient data structures for recalling motif pair
// interactions.
#include <spp.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <msgpack.hpp>

#include <iostream>
using namespace std;

template <class T>
T GetMax (T a, T b) {
      T result;
        result = (a>b)? a : b;
          return (result);
}

int main () {
      int i=5, j=6, k;
        long l=10, m=5, n;
          k=GetMax<int>(i,j);
            n=GetMax<long>(l,m);
              cout << k << endl;
                cout << n << endl;
                  return 0;
}

