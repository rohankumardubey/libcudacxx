//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <cuda/std/array>

// array();

#include <cuda/std/array>
#include <cuda/std/cassert>

// cuda::std::array is explicitly allowed to be initialized with A a = { init-list };.
// Disable the missing braces warning for this reason.
#include "test_macros.h"
#include "disable_missing_braces_warning.h"

struct NoDefault {
  __host__ __device__ NoDefault(int) {}
};

int main(int, char**)
{
    {
        typedef double T;
        typedef cuda::std::array<T, 3> C;
        C c;
        assert(c.size() == 3);
    }
    {
        typedef double T;
        typedef cuda::std::array<T, 0> C;
        C c;
        assert(c.size() == 0);
    }
    {
      typedef cuda::std::array<NoDefault, 0> C;
      C c;
      assert(c.size() == 0);
      C c1 = {};
      assert(c1.size() == 0);
      C c2 = {{}};
      assert(c2.size() == 0);
    }

  return 0;
}
