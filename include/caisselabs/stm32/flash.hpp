//
// Copyright (c) 2026 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// STM32 register descriptions for the embedded Flash interface.
//
// Only the access control register is modelled. The programming and erase
// side of the interface (KEYR, OPTKEYR, SR, CR, ECCR, OPTR ...) is a
// different job with its own unlock sequences and is deliberately left out.
//
// clang-format off
#pragma once

#include <caisselabs/stm32/access.hpp>
#include <caisselabs/stm32/enable.hpp>

#include <groov/config.hpp>

#include <cstdint>


namespace caisselabs::stm32 {

  using std::uint8_t;
  using std::uint32_t;

  namespace flashx {
    // FLASH_ACR.LATENCY. Wait states required for a given HCLK, from
    // RM0394 Table 9:
    //
    //                VCORE Range 1     VCORE Range 2
    //   ws0            <= 16 MHz          <= 6 MHz
    //   ws1            <= 32 MHz          <= 12 MHz
    //   ws2            <= 48 MHz          <= 18 MHz
    //   ws3            <= 64 MHz          <= 26 MHz
    //   ws4            <= 80 MHz          <= 26 MHz
    //
    // When raising the CPU frequency the latency must be programmed and
    // read back *before* SW is changed in RCC_CFGR; when lowering it, the
    // order is reversed (RM0394 3.3.3).
    enum class latency : std::uint8_t {
      ws0 = 0b000,
      ws1 = 0b001,
      ws2 = 0b010,
      ws3 = 0b011,
      ws4 = 0b100
    };
  }

  // Reset value is 0x0000'0600: the instruction and data caches are
  // already enabled out of reset, prefetch is not.
  template <std::uintptr_t BaseAddress>
  using flash_acr =
    groov::reg<
      "acr", std::uint32_t,
      BaseAddress+0x00, access::rw,

      groov::field<"reserved0", uint32_t        , 31, 15, access::ro>,
      groov::field<"SLEEP_PD" , bit_enable      , 14, 14>,
      groov::field<"RUN_PD"   , bit_enable      , 13, 13>,
      groov::field<"DCRST"    , bit_reset       , 12, 12>,
      groov::field<"ICRST"    , bit_reset       , 11, 11>,
      groov::field<"DCEN"     , bit_enable      , 10, 10>,
      groov::field<"ICEN"     , bit_enable      ,  9,  9>,
      groov::field<"PRFTEN"   , bit_enable      ,  8,  8>,
      groov::field<"reserved1", uint8_t         ,  7,  3, access::ro>,
      groov::field<"LATENCY"  , flashx::latency ,  2,  0>
    >;
}
