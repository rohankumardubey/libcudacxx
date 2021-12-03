//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// UNSUPPORTED: c++98, c++03

// template <class T>
//   constexpr T ceil2(T x) noexcept;

// Returns: The minimal value y such that ispow2(y) is true and y >= x;
//    if y is not representable as a value of type T, the result is an unspecified value.
// Remarks: This function shall not participate in overload resolution unless
//  T is an unsigned integer type

#include <cuda/std/bit>
#include <cuda/std/cstdint>
#include <cuda/std/type_traits>
#include <cuda/std/cassert>

#include "test_macros.h"

class A{};
enum       E1 : unsigned char { rEd };
enum class E2 : unsigned char { red };

template <typename T>
__host__ __device__ constexpr bool constexpr_test()
{
    return cuda::std::ceil2(T(0)) == T(1)
       &&  cuda::std::ceil2(T(1)) == T(1)
       &&  cuda::std::ceil2(T(2)) == T(2)
       &&  cuda::std::ceil2(T(3)) == T(4)
       &&  cuda::std::ceil2(T(4)) == T(4)
       &&  cuda::std::ceil2(T(5)) == T(8)
       &&  cuda::std::ceil2(T(6)) == T(8)
       &&  cuda::std::ceil2(T(7)) == T(8)
       &&  cuda::std::ceil2(T(8)) == T(8)
       &&  cuda::std::ceil2(T(9)) == T(16)
       ;
}


template <typename T>
__host__ __device__ void runtime_test()
{
    ASSERT_SAME_TYPE(T, decltype(cuda::std::ceil2(T(0))));
    LIBCPP_ASSERT_NOEXCEPT(      cuda::std::ceil2(T(0)));

    assert( cuda::std::ceil2(T(60)) == T( 64));
    assert( cuda::std::ceil2(T(61)) == T( 64));
    assert( cuda::std::ceil2(T(62)) == T( 64));
    assert( cuda::std::ceil2(T(63)) == T( 64));
    assert( cuda::std::ceil2(T(64)) == T( 64));
    assert( cuda::std::ceil2(T(65)) == T(128));
    assert( cuda::std::ceil2(T(66)) == T(128));
    assert( cuda::std::ceil2(T(67)) == T(128));
    assert( cuda::std::ceil2(T(68)) == T(128));
    assert( cuda::std::ceil2(T(69)) == T(128));
}

int main(int, char **)
{
#if !defined(__CUDA_ARCH__)
    static_assert(constexpr_test<unsigned char>(),      "");
    static_assert(constexpr_test<unsigned short>(),     "");
    static_assert(constexpr_test<unsigned>(),           "");
    static_assert(constexpr_test<unsigned long>(),      "");
    static_assert(constexpr_test<unsigned long long>(), "");

    static_assert(constexpr_test<uint8_t>(),   "");
    static_assert(constexpr_test<uint16_t>(),  "");
    static_assert(constexpr_test<uint32_t>(),  "");
    static_assert(constexpr_test<uint64_t>(),  "");
    static_assert(constexpr_test<size_t>(),    "");
    static_assert(constexpr_test<uintmax_t>(), "");
    static_assert(constexpr_test<uintptr_t>(), "");

#ifndef _LIBCUDACXX_HAS_NO_INT128
    static_assert(constexpr_test<__uint128_t>(),        "");
#endif
#endif

    runtime_test<unsigned char>();
    runtime_test<unsigned>();
    runtime_test<unsigned short>();
    runtime_test<unsigned long>();
    runtime_test<unsigned long long>();

    runtime_test<uint8_t>();
    runtime_test<uint16_t>();
    runtime_test<uint32_t>();
    runtime_test<uint64_t>();
    runtime_test<size_t>();
    runtime_test<uintmax_t>();
    runtime_test<uintptr_t>();

#ifndef _LIBCUDACXX_HAS_NO_INT128
    runtime_test<__uint128_t>();
#endif

	return 0;
}
