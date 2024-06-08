//
// Copyright (c) 2024 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <groov/config.hpp>

#include <cstdint>


namespace caisselabs::stm32 {

  // ----------------------------------------------------------------
  // register descriptions for TIM2/TIM3 on STM32L41,42,43,44,45,46
  // 
  template <std::uint32_t BaseAddress>
  using timx_cr1 =
    groov::reg<
      "cr1", std::uint32_t,
      BaseAddress+0x00, groov::w::replace,

      groov::field<"UIFREMAP", bool, 11, 11>,
      groov::field<"CKD"     , std::uint8_t, 9, 8>,
      groov::field<"ARPE"    , bool, 7, 7>,
      groov::field<"CMS"     , std::uint8_t, 6, 5>,
      groov::field<"DIR"     , bool, 4, 4>,
      groov::field<"OPM"     , bool, 3, 3>,
      groov::field<"URS"     , bool, 2, 2>,
      groov::field<"UDIS"    , bool, 1, 1>,
      groov::field<"CEN"     , bool, 0, 0>
    >;

  template <std::uint32_t BaseAddress>
  using timx_dier =
    groov::reg<
      "dier", std::uint32_t,
      BaseAddress+0x0c, groov::w::replace,

      groov::field<"TDE"  , bool, 14, 14>,
      groov::field<"CC4DE", bool, 12, 12>,
      groov::field<"CC3DE", bool, 11, 11>,
      groov::field<"CC2DE", bool, 10, 10>,
      groov::field<"CC1DE", bool,  9,  9>,
      groov::field<"UDE"  , bool,  8,  8>,
      groov::field<"TIE"  , bool,  6,  6>,
      groov::field<"CC4IE", bool,  4,  4>,
      groov::field<"CC3IE", bool,  3,  3>,
      groov::field<"CC2IE", bool,  2,  2>,
      groov::field<"CC1IE", bool,  1,  1>,
      groov::field<"UIE"  , bool,  0,  0>
    >;

  template <std::uint32_t BaseAddress>
  using timx_sr =
    groov::reg<
      "sr", std::uint32_t,
      BaseAddress+0x10, groov::w::replace,

      groov::field<"CC4OF", bool, 12, 12>,
      groov::field<"CC3OF", bool, 11, 11>,
      groov::field<"CC2OF", bool, 10, 10>,
      groov::field<"CC1OF", bool,  9,  9>,
      groov::field<"TIF"  , bool,  6,  6>,
      groov::field<"CC4IF", bool,  4,  4>,
      groov::field<"CC3IF", bool,  3,  3>,
      groov::field<"CC2IF", bool,  2,  2>,
      groov::field<"CC1IF", bool,  1,  1>,
      groov::field<"UIF"  , bool,  0,  0>
    >;


  enum class ocm_t : std::uint8_t {
    frozen = 0b0000,
    active_on_match = 0b0001,
    inactive_on_match = 0b0010,
    oc_toggle = 0b0011,
    force_inactive = 0b0100,
    force_active = 0b0101,
    pwm_mode_1 = 0b0110,
    pwm_mode_2 = 0b0111
  };

  enum class ccsel_t : std::uint8_t {
    output = 0b00,
    input_ic_ti1 = 0b01,
    input_ic_ti2 = 0b10,
    input_ic_trc = 0b11
  };

  template <std::uint32_t BaseAddress>
  using timx_ccmr1_out =
    groov::reg<
      "ccmr1_out", std::uint32_t,
      BaseAddress+0x18, groov::w::replace,

      groov::field<"OC2M_3", std::uint8_t, 24, 24>,
      groov::field<"OC1M_3", std::uint8_t, 16, 16>,
      groov::field<"OC2CE" , bool, 15, 15>,
      groov::field<"OC2M"  , ocm_t, 14, 12>,
      groov::field<"OC2PE" , bool, 11, 11>,
      groov::field<"OC2FE" , bool, 10, 10>,
      groov::field<"OC2S"  , ccsel_t, 9, 8>,
      groov::field<"OC1CE" , bool, 7, 7>,
      groov::field<"OC1M"  , ocm_t, 6, 4>,
      groov::field<"OC1PE" , bool, 3, 3>,
      groov::field<"OC1FE" , bool, 2, 2>,
      groov::field<"OC1S"  , ccsel_t, 1, 0>
    >;


  template <std::uint32_t BaseAddress>
  using timx_ccer =
    groov::reg<
      "ccer", std::uint32_t,
      BaseAddress+0x20, groov::w::replace,
    
      groov::field<"CC4NP", bool, 15, 15>,
      groov::field<"CC4P" , bool, 13, 13>,
      groov::field<"CC4E" , bool, 12, 12>,
      groov::field<"CC3NP", bool, 11, 11>,
      groov::field<"CC3P" , bool,  9,  9>,
      groov::field<"CC3E" , bool,  8,  8>,
      groov::field<"CC2NP", bool,  7,  7>,
      groov::field<"CC2P" , bool,  5,  5>,
      groov::field<"CC2E" , bool,  4,  4>,
      groov::field<"CC1NP", bool,  3,  3>,
      groov::field<"CC1P" , bool,  1,  1>,
      groov::field<"CC1E" , bool,  0,  0>
    >;

  template <std::uint32_t BaseAddress>
  using timx_cnt_16 =
    groov::reg<
      "cnt", std::uint32_t,
      BaseAddress+0x24, groov::w::replace,

      groov::field<"CNT", std::uint32_t, 15, 0> // TODO: uint16_t?
    >;

  template <std::uint32_t BaseAddress>
  using timx_cnt_32 = groov::reg<
    "cnt", std::uint32_t,
    BaseAddress+0x24, groov::w::replace,
    
    groov::field<"CNT", std::uint32_t, 31, 0>
  >;

  template <std::uint32_t BaseAddress>
  using timx_ccr1_16 = groov::reg<
    "ccr1", std::uint32_t,
    BaseAddress+0x34, groov::w::replace,
    
    groov::field<"CCR1", std::uint32_t, 15, 0>
  >;

  template <std::uint32_t BaseAddress>
  using timx_ccr1_32 = groov::reg<
    "ccr1", std::uint32_t,
    BaseAddress+0x34, groov::w::replace,
    
    groov::field<"CCR1", std::uint32_t, 31, 0>
  >;
}
