//
// Copyright (c) 2026 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// An MMIO bus that always accesses a register at its declared width.
//
// groov's `mmio_bus` picks the narrowest access that covers the bits being
// written -- see `subword_permutations` in groov/mmio_bus.hpp. That is a good
// optimization but fatal for peripherals that specify an access width.
//
#pragma once

#include <groov/mmio_bus.hpp>

#include <async/concepts.hpp>
#include <async/just.hpp>
#include <async/then.hpp>

#include <stdx/bit.hpp>
#include <stdx/ct_string.hpp>

#include <concepts>
#include <cstddef>
#include <cstdint>

namespace caisselabs::stm32 {

namespace detail {
template <std::unsigned_integral T, std::unsigned_integral U>
constexpr auto to_addr(U u) -> T {
   if constexpr (sizeof(T) > sizeof(U)) {
      return static_cast<T>(u);
   } else {
      static_assert(std::same_as<T, U>);
      return u;
   }
}

template <std::unsigned_integral T, std::unsigned_integral U>
constexpr auto to_addr(U *p) -> T {
   static_assert(sizeof(T) == sizeof(U *));
   return stdx::bit_cast<T>(p);
}
} // namespace detail

template <typename HardwareInterface = groov::cpp_mem_iface>
struct whole_register_bus {
   using iface = HardwareInterface;

   template <stdx::ct_string, auto Mask, decltype(Mask) IdMask, decltype(Mask) IdValue>
      requires std::unsigned_integral<decltype(Mask)>
   static auto write(auto addr, decltype(Mask) value) -> async::sender auto {
      static_assert((Mask & IdMask) == decltype(Mask){});
      static_assert((Mask & IdValue) == decltype(Mask){});

      using base_type = decltype(Mask);
      constexpr auto all_bits = static_cast<base_type>(~base_type{});

      auto const iaddr = detail::to_addr<std::uintptr_t>(addr);

      if constexpr ((Mask | IdMask) == all_bits) {
         // Every bit is either being written or is an identity bit, so nothing
         // read back could survive into the result. Skipping the load is not
         // only faster: a read of a peripheral register is not always free of
         // side effects, and one that cannot affect the value written has no
         // business happening at all.
         return async::just(static_cast<base_type>(value | IdValue)) //
                | iface::template store<base_type>(iaddr)            //
             ;
      } else {
         return iface::template load<base_type>(iaddr)                     //
                | async::then([=](base_type old) {                         //
                     auto const bits_to_update = value & Mask;             //
                     auto const bits_to_writeback = old & ~Mask & ~IdMask; //
                     return static_cast<base_type>(bits_to_update | bits_to_writeback |
                                                   IdValue); //
                  })                                         //
                | iface::template store<base_type>(iaddr)    //
             ;
      }
   }

   template <stdx::ct_string, std::unsigned_integral auto Mask>
   static auto read(auto addr) -> async::sender auto {
      using base_type = decltype(Mask);
      auto const iaddr = detail::to_addr<std::uintptr_t>(addr);
      return iface::template load<base_type>(iaddr);
   }
};
} // namespace caisselabs::stm32
