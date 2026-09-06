//
// Copyright (c) 2024, 2026 Michael Caisse
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
  // The plain timx_* templates describe the general-purpose timers. The
  // _adv variants describe the same register on the advanced-control timer
  // TIM1, which adds the complementary outputs, the break inputs and the
  // repetition counter. TIM15 and TIM16 sit between the two: they have
  // BDTR and RCR like TIM1 but only one or two channels.
  // 
  template <std::uintptr_t BaseAddress>
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

  template <std::uintptr_t BaseAddress>
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

  // TIM1 reuses every bit of the general-purpose DIER and fills in two of
  // the gaps: COM interrupt and COM DMA request.
  template <std::uintptr_t BaseAddress>
  using timx_dier_adv =
    groov::reg<
      "dier", std::uint32_t,
      BaseAddress+0x0c, groov::w::replace,

      groov::field<"TDE"  , bool, 14, 14>,
      groov::field<"COMDE", bool, 13, 13>,
      groov::field<"CC4DE", bool, 12, 12>,
      groov::field<"CC3DE", bool, 11, 11>,
      groov::field<"CC2DE", bool, 10, 10>,
      groov::field<"CC1DE", bool,  9,  9>,
      groov::field<"UDE"  , bool,  8,  8>,
      groov::field<"BIE"  , bool,  7,  7>,
      groov::field<"TIE"  , bool,  6,  6>,
      groov::field<"COMIE", bool,  5,  5>,
      groov::field<"CC4IE", bool,  4,  4>,
      groov::field<"CC3IE", bool,  3,  3>,
      groov::field<"CC2IE", bool,  2,  2>,
      groov::field<"CC1IE", bool,  1,  1>,
      groov::field<"UIE"  , bool,  0,  0>
    >;

  template <std::uintptr_t BaseAddress>
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


  template <std::uintptr_t BaseAddress>
  using timx_sr_adv =
    groov::reg<
      "sr", std::uint32_t,
      BaseAddress+0x10, groov::w::replace,

      groov::field<"CC6IF", bool, 17, 17>,
      groov::field<"CC5IF", bool, 16, 16>,
      groov::field<"SBIF" , bool, 13, 13>,
      groov::field<"CC4OF", bool, 12, 12>,
      groov::field<"CC3OF", bool, 11, 11>,
      groov::field<"CC2OF", bool, 10, 10>,
      groov::field<"CC1OF", bool,  9,  9>,
      groov::field<"B2IF" , bool,  8,  8>,
      groov::field<"BIF"  , bool,  7,  7>,
      groov::field<"TIF"  , bool,  6,  6>,
      groov::field<"COMIF", bool,  5,  5>,
      groov::field<"CC4IF", bool,  4,  4>,
      groov::field<"CC3IF", bool,  3,  3>,
      groov::field<"CC2IF", bool,  2,  2>,
      groov::field<"CC1IF", bool,  1,  1>,
      groov::field<"UIF"  , bool,  0,  0>
    >;

  // Every bit is a software event trigger, self-clearing in hardware.
  // UG reloads the prescaler and auto-reload shadows, which is how PSC and
  // ARR take effect without waiting for a rollover.
  template <std::uintptr_t BaseAddress>
  using timx_egr =
    groov::reg<
      "egr", std::uint32_t,
      BaseAddress+0x14, groov::w::replace,

      groov::field<"TG"  , bool, 6, 6>,
      groov::field<"CC4G", bool, 4, 4>,
      groov::field<"CC3G", bool, 3, 3>,
      groov::field<"CC2G", bool, 2, 2>,
      groov::field<"CC1G", bool, 1, 1>,
      groov::field<"UG"  , bool, 0, 0>
    >;

  template <std::uintptr_t BaseAddress>
  using timx_egr_adv =
    groov::reg<
      "egr", std::uint32_t,
      BaseAddress+0x14, groov::w::replace,

      groov::field<"B2G" , bool, 8, 8>,
      groov::field<"BG"  , bool, 7, 7>,
      groov::field<"TG"  , bool, 6, 6>,
      groov::field<"COMG", bool, 5, 5>,
      groov::field<"CC4G", bool, 4, 4>,
      groov::field<"CC3G", bool, 3, 3>,
      groov::field<"CC2G", bool, 2, 2>,
      groov::field<"CC1G", bool, 1, 1>,
      groov::field<"UG"  , bool, 0, 0>
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

  template <std::uintptr_t BaseAddress>
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


  template <std::uintptr_t BaseAddress>
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

  // TIM1 adds the complementary output enables at the even bit of each
  // channel pair, plus the output-only channels 5 and 6.
  template <std::uintptr_t BaseAddress>
  using timx_ccer_adv =
    groov::reg<
      "ccer", std::uint32_t,
      BaseAddress+0x20, groov::w::replace,

      groov::field<"CC6P" , bool, 21, 21>,
      groov::field<"CC6E" , bool, 20, 20>,
      groov::field<"CC5P" , bool, 17, 17>,
      groov::field<"CC5E" , bool, 16, 16>,
      groov::field<"CC4NP", bool, 15, 15>,
      groov::field<"CC4P" , bool, 13, 13>,
      groov::field<"CC4E" , bool, 12, 12>,
      groov::field<"CC3NP", bool, 11, 11>,
      groov::field<"CC3NE", bool, 10, 10>,
      groov::field<"CC3P" , bool,  9,  9>,
      groov::field<"CC3E" , bool,  8,  8>,
      groov::field<"CC2NP", bool,  7,  7>,
      groov::field<"CC2NE", bool,  6,  6>,
      groov::field<"CC2P" , bool,  5,  5>,
      groov::field<"CC2E" , bool,  4,  4>,
      groov::field<"CC1NP", bool,  3,  3>,
      groov::field<"CC1NE", bool,  2,  2>,
      groov::field<"CC1P" , bool,  1,  1>,
      groov::field<"CC1E" , bool,  0,  0>
    >;

  template <std::uintptr_t BaseAddress>
  using timx_cnt_16 =
    groov::reg<
      "cnt", std::uint32_t,
      BaseAddress+0x24, groov::w::replace,

      groov::field<"CNT", std::uint32_t, 15, 0> // TODO: uint16_t?
    >;

  template <std::uintptr_t BaseAddress>
  using timx_cnt_32 = groov::reg<
    "cnt", std::uint32_t,
    BaseAddress+0x24, groov::w::replace,
    
    groov::field<"CNT", std::uint32_t, 31, 0>
  >;

  // CK_CNT = CK_PSC / (PSC + 1). The prescaler is buffered: a write lands
  // at the next update event, so set it before CEN or force it through
  // with EGR.UG.
  template <std::uintptr_t BaseAddress>
  using timx_psc = groov::reg<
    "psc", std::uint32_t,
    BaseAddress+0x28, groov::w::replace,

    groov::field<"PSC", std::uint32_t, 15, 0>
  >;

  // ARR is 16-bit on TIM1/TIM15/TIM16 and 32-bit on TIM2. A counter never
  // runs with ARR = 0.
  template <std::uintptr_t BaseAddress>
  using timx_arr_16 = groov::reg<
    "arr", std::uint32_t,
    BaseAddress+0x2c, groov::w::replace,

    groov::field<"ARR", std::uint32_t, 15, 0>
  >;

  template <std::uintptr_t BaseAddress>
  using timx_arr_32 = groov::reg<
    "arr", std::uint32_t,
    BaseAddress+0x2c, groov::w::replace,

    groov::field<"ARR", std::uint32_t, 31, 0>
  >;

  // Advanced timers only: an update event is raised once every REP + 1
  // counter overflows.
  template <std::uintptr_t BaseAddress>
  using timx_rcr = groov::reg<
    "rcr", std::uint32_t,
    BaseAddress+0x30, groov::w::replace,

    groov::field<"REP", std::uint32_t, 15, 0>
  >;

  template <std::uintptr_t BaseAddress>
  using timx_ccr1_16 = groov::reg<
    "ccr1", std::uint32_t,
    BaseAddress+0x34, groov::w::replace,
    
    groov::field<"CCR1", std::uint32_t, 15, 0>
  >;

  template <std::uintptr_t BaseAddress>
  using timx_ccr1_32 = groov::reg<
    "ccr1", std::uint32_t,
    BaseAddress+0x34, groov::w::replace,
    
    groov::field<"CCR1", std::uint32_t, 31, 0>
  >;


  // Once a LOCK level is written it cannot be changed until the next
  // reset, and it write-protects some of BDTR along with it.
  enum class lock_t : std::uint8_t {
    off     = 0b00,
    level_1 = 0b01,
    level_2 = 0b10,
    level_3 = 0b11
  };

  // Advanced timers only.
  //
  // MOE is the one that catches people out: with it clear the outputs stay
  // disconnected no matter what CCER says, so a TIM1 channel configured
  // exactly like a working TIM2 channel drives nothing at all. It is also
  // cleared asynchronously by a break event.
  template <std::uintptr_t BaseAddress>
  using timx_bdtr =
    groov::reg<
      "bdtr", std::uint32_t,
      BaseAddress+0x44, groov::w::replace,

      groov::field<"BK2P", bool        , 25, 25>,
      groov::field<"BK2E", bool        , 24, 24>,
      groov::field<"BK2F", std::uint8_t, 23, 20>,
      groov::field<"BKF" , std::uint8_t, 19, 16>,
      groov::field<"MOE" , bool        , 15, 15>,
      groov::field<"AOE" , bool        , 14, 14>,
      groov::field<"BKP" , bool        , 13, 13>,
      groov::field<"BKE" , bool        , 12, 12>,
      groov::field<"OSSR", bool        , 11, 11>,
      groov::field<"OSSI", bool        , 10, 10>,
      groov::field<"LOCK", lock_t      ,  9,  8>,
      groov::field<"DTG" , std::uint8_t,  7,  0>
    >;
}
