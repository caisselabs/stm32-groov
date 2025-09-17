//
// Copyright (c) 2024, 2025 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <caisselabs/stm32/enable.hpp>
#include <caisselabs/stm32/access.hpp>

#include <groov/config.hpp>

#include <cstdint>


namespace caisselabs::stm32 {

  using std::uint8_t;
  using std::uint32_t;

  // ----------------------------------------------------------------
  // Port bit configuration
  //
  namespace gpio {
    enum class mode : std::uint8_t {
      input      = 0b00,
      output     = 0b01,
      alternate  = 0b10,
      analog     = 0b11
    };

    enum class outtype : std::uint8_t {
      push_pull   = 0b0,
      open_drain  = 0b1
    };

    enum class pupd : std::uint8_t {
      none       = 0b00,
      pull_up    = 0b01,
      pull_down  = 0b10
    };

    enum class speed : std::uint8_t {
      low_speed       = 0b00,
      medium_speed    = 0b01,
      high_speed      = 0b10,
      very_high_speed = 0b11
    };

    enum class afsel : std::uint8_t {
      AF0 = 0x0,
      AF1 = 0x1,
      AF2 = 0x2,
      AF3 = 0x3,
      AF4 = 0x4,
      AF5 = 0x5,
      AF6 = 0x6,
      AF7 = 0x7,
      AF8 = 0x8,
      AF9 = 0x9,
      AF10 = 0xa,
      AF11 = 0xb,
      AF12 = 0xc,
      AF13 = 0xd,
      AF14 = 0xe,
      AF15 = 0xf
    };
  }

  template <stdx::ct_string Name, typename FieldType, std::uint32_t Offset, std::uint32_t BaseAddress>
  using gpiox_two_bit =
    groov::reg<
      Name, std::uint32_t,
      BaseAddress+Offset, access::rw,

      groov::field<"15", FieldType, 31, 30>,
      groov::field<"14", FieldType, 29, 28>,
      groov::field<"13", FieldType, 27, 26>,
      groov::field<"12", FieldType, 25, 24>,
      groov::field<"11", FieldType, 23, 22>,
      groov::field<"10", FieldType, 21, 20>,
      groov::field<"9" , FieldType, 19, 18>,
      groov::field<"8" , FieldType, 17, 16>,
      groov::field<"7" , FieldType, 15, 14>,
      groov::field<"6" , FieldType, 13, 12>,
      groov::field<"5" , FieldType, 11, 10>,
      groov::field<"4" , FieldType,  9,  8>,
      groov::field<"3" , FieldType,  7,  6>,
      groov::field<"2" , FieldType,  5,  4>,
      groov::field<"1" , FieldType,  3,  2>,
      groov::field<"0" , FieldType,  1,  0>
    >;


  template <stdx::ct_string Name, typename FieldType, std::uint32_t Offset, std::uint32_t BaseAddress>
  using gpiox_one_bit =
    groov::reg<
      Name, std::uint32_t,
      BaseAddress+Offset, access::rw,

      groov::field<"reserved", uint32_t, 31, 16, access::ro>,
      groov::field<"15", FieldType, 15, 15>,
      groov::field<"14", FieldType, 14, 14>,
      groov::field<"13", FieldType, 13, 13>,
      groov::field<"12", FieldType, 12, 12>,
      groov::field<"11", FieldType, 11, 11>,
      groov::field<"10", FieldType, 10, 10>,
      groov::field<"9" , FieldType,  9,  9>,
      groov::field<"8" , FieldType,  8,  8>,
      groov::field<"7" , FieldType,  7,  7>,
      groov::field<"6" , FieldType,  6,  6>,
      groov::field<"5" , FieldType,  5,  5>,
      groov::field<"4" , FieldType,  4,  4>,
      groov::field<"3" , FieldType,  3,  3>,
      groov::field<"2" , FieldType,  2,  2>,
      groov::field<"1" , FieldType,  1,  1>,
      groov::field<"0" , FieldType,  0,  0>
    >;


  template <std::uint32_t BaseAddress>
  using gpiox_moder = gpiox_two_bit<"moder", gpio::mode, 0x00, BaseAddress>;

  template <std::uint32_t BaseAddress>
  using gpiox_otyper = gpiox_one_bit<"otyper", gpio::outtype, 0x04, BaseAddress>;

  template <std::uint32_t BaseAddress>
  using gpiox_ospeedr = gpiox_two_bit<"ospeedr", gpio::speed, 0x08, BaseAddress>;

  template <std::uint32_t BaseAddress>
  using gpiox_pupdr = gpiox_two_bit<"pupdr", gpio::pupd, 0x0c, BaseAddress>;

  // TODO: FIX read only
  template <std::uint32_t BaseAddress>
  using gpiox_idr = gpiox_one_bit<"idr", bool, 0x10, BaseAddress>;

  template <std::uint32_t BaseAddress>
  using gpiox_odr = gpiox_one_bit<"odr", bool, 0x14, BaseAddress>;

  template <std::uint32_t BaseAddress>
  using gpiox_afrl =
    groov::reg<
      "afrl", std::uint32_t,
      BaseAddress+0x20, access::rw,

      groov::field<"7" , gpio::afsel,  31,  28>,
      groov::field<"6" , gpio::afsel,  27,  24>,
      groov::field<"5" , gpio::afsel,  23,  20>,
      groov::field<"4" , gpio::afsel,  19,  16>,
      groov::field<"3" , gpio::afsel,  15,  12>,
      groov::field<"2" , gpio::afsel,  11,   8>,
      groov::field<"1" , gpio::afsel,   7,   4>,
      groov::field<"0" , gpio::afsel,   3,   0>
    >;

  template <std::uint32_t BaseAddress>
  using gpiox_afrh =
    groov::reg<
      "afrh", std::uint32_t,
      BaseAddress+0x24, access::rw,

      groov::field<"15" , gpio::afsel,  31,  28>,
      groov::field<"14" , gpio::afsel,  27,  24>,
      groov::field<"13" , gpio::afsel,  23,  20>,
      groov::field<"12" , gpio::afsel,  19,  16>,
      groov::field<"11" , gpio::afsel,  15,  12>,
      groov::field<"10" , gpio::afsel,  11,   8>,
      groov::field<"9"  , gpio::afsel,   7,   4>,
      groov::field<"8"  , gpio::afsel,   3,   0>
    >;

  // TODO: write one, write only register
  template <std::uint32_t BaseAddress>
  using gpiox_brr = gpiox_one_bit<"brr", bit_reset, 0x28, BaseAddress>;
}
