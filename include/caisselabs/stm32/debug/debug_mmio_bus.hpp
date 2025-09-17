//
// Copyright (c) 2024 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// mmio_bus suitable for groov that makes debugging easier
//
// Using this bus allows adding break points for store/read operations.
//
// Simply pass the object type to the mmio_bus of interest and then set break points
// on free functions `debug_store` and `debug_read` which should not get inlined.
// For example:
//
//  template <stdx::ct_string Name, std::uint32_t BaseAddress>
//  using usartx_t =
//    groov::group<
//      Name, groov::mmio_bus<debug_mem_iface>,
//
// and now reads and writes to usartx_t types will use the `debug_store` and
// `debug_read` free functions.
//

#pragma once

#include <groov/mmio_bus.hpp>

#include <cstdint>

inline void __attribute__ ((noinline)) debug_store(std::uintptr_t addr, std::uint32_t value) {
  *reinterpret_cast<std::uint32_t volatile *>(addr) = value;
}

inline std::uint32_t __attribute__ ((noinline)) debug_read(std::uintptr_t addr) {
  return *reinterpret_cast<std::uint32_t volatile *>(addr);
}

namespace caisselabs::stm32 {
  struct debug_mem_iface {
    template <std::unsigned_integral T>
    static auto store(std::uintptr_t addr) -> void {
        return async::then([=](T value) -> void {
            debug_store(addr, value);
        });
    }

    template <std::unsigned_integral T>
    static auto load(std::uintptr_t addr) -> async::sender auto {
        return async::just_result_of([=]() -> T {
            return debug_read(addr);
        });
    }

    template <typename T> constexpr static std::size_t alignment = alignof(T);
  };    
}
