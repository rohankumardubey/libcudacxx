//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <cuda/std/array>

// template <size_t I, class T, size_t N> const T& get(const array<T, N>& a);

#include <cuda/std/array>
#include <cuda/std/cassert>

#include "test_macros.h"

// cuda::std::array is explicitly allowed to be initialized with A a = { init-list };.
// Disable the missing braces warning for this reason.
#include "disable_missing_braces_warning.h"

int main(int, char**)
{
    {
        typedef double T;
        typedef cuda::std::array<T, 3> C;
        const C c = {1, 2, 3.5};
        assert(cuda::std::get<0>(c) == 1);
        assert(cuda::std::get<1>(c) == 2);
        assert(cuda::std::get<2>(c) == 3.5);
    }
#if TEST_STD_VER > 11
    {
        typedef double T;
        typedef cuda::std::array<T, 3> C;
        constexpr const C c = {1, 2, 3.5};
        static_assert(cuda::std::get<0>(c) == 1, "");
        static_assert(cuda::std::get<1>(c) == 2, "");
        static_assert(cuda::std::get<2>(c) == 3.5, "");
    }
#endif

  return 0;
}
