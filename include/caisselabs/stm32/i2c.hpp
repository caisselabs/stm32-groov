//
// Copyright (c) 2024 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// clang-format off
#pragma once

#include <caisselabs/stm32/access.hpp>
#include <caisselabs/stm32/enable.hpp>

#include <groov/config.hpp>

#include <cstdint>


namespace caisselabs::stm32 {

  using std::uint8_t;

  template <std::uint32_t BaseAddress>
  using i2c_cr1 =
    groov::reg<
      "cr1", std::uint32_t,
      BaseAddress+0x00, access::rw,

      groov::field<"reserved0", uint8_t, 31, 24, access::ro>,
      groov::field<"PECEN", bit_enable, 23, 23>,
      groov::field<"ALERTEN", bit_enable, 22, 22>,
      groov::field<"SMBDEN", bit_enable, 21, 21>,
      groov::field<"SMBHEN", bit_enable, 20, 20>,
      groov::field<"GCEN", bit_enable, 19, 19>,
      groov::field<"WUPEN", bit_enable, 18, 18>,
      groov::field<"NOSTRETCH", bit_enable, 17, 17>,
      groov::field<"SBC", bit_enable, 16, 16>,
      groov::field<"RXDMAEN", bit_enable, 15, 15>,
      groov::field<"TXDMAEN", bit_enable, 14, 14>,
      groov::field<"ANFOFF", bit_enable, 12, 12>,
      groov::field<"DNF", std::uint8_t, 11, 8>,
      groov::field<"ERRIE", bit_enable, 7, 7>,
      groov::field<"TCIE", bit_enable, 6, 6>,
      groov::field<"STOPIE", bit_enable, 5, 5>,
      groov::field<"NACKIE", bit_enable, 4, 4>,
      groov::field<"ADDRIE", bit_enable, 3, 3>,
      groov::field<"RXIE", bit_enable, 2, 2>,
      groov::field<"TXIE", bit_enable, 1, 1>,
      groov::field<"PE", bit_enable, 0, 0>
    >;

  namespace i2c {
    enum class rd_wrn : bool {
      WRITE_XFER = false,
      READ_XFER = true,
      zero = false,
      one = true
    };
  }

  template <std::uint32_t BaseAddress>
  using i2c_cr2 =
    groov::reg<
      "cr2", std::uint32_t,
      BaseAddress+0x04, access::rw,

      groov::field<"reserved0", uint8_t, 31, 27, access::ro>,
      groov::field<"PECBYTE", bit_enable, 26, 26>,
      groov::field<"AUTOEND", bit_enable, 25, 25>,
      groov::field<"RELOAD", bit_enable, 24, 24>,
      groov::field<"NBYTES", std::uint8_t, 23, 16>,
      groov::field<"NACK", bool, 15, 15>,  // rs
      groov::field<"STOP", bit_enable, 14, 14>,
      groov::field<"START", bool, 13, 13>, // rs
      groov::field<"HEAD10R", bit_enable_bar, 12, 12>,
      groov::field<"ADD10", bit_enable, 11, 11>,
      groov::field<"RD_WRN", i2c::rd_wrn, 10, 10>,
      groov::field<"SADD", std::uint32_t, 9, 0>,
      groov::field<"SADD7", std::uint8_t, 7, 1>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_oar1 =
    groov::reg<
      "oar1", std::uint32_t,
      BaseAddress+0x08, access::rw,

      groov::field<"OA1EN", bool, 15, 15>,
      groov::field<"OA1MODE", bool, 10, 10>,
      groov::field<"OA1", std::uint32_t, 9, 0>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_oar2 =
    groov::reg<
      "oar2", std::uint32_t,
      BaseAddress+0x0c, access::rw,

      groov::field<"OA2EN", bool, 15, 15>,
      groov::field<"OA2MSK", std::uint8_t, 10, 8>,
      groov::field<"OA2", std::uint8_t, 7, 1>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_timingr =
    groov::reg<
      "timingr", std::uint32_t,
      BaseAddress+0x10, access::rw,

      groov::field<"PRESC", std::uint8_t, 31, 28>,
      groov::field<"SCLDEL", std::uint8_t, 23, 20>,
      groov::field<"SDADEL", std::uint8_t, 19, 16>,
      groov::field<"SCLH", std::uint8_t, 15, 8>,
      groov::field<"SCLL", std::uint8_t, 7, 0>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_timeoutr =
    groov::reg<
      "timeoutr", std::uint32_t,
      BaseAddress+0x14, access::rw,

      groov::field<"TEXTEN", bool, 31, 31>,
      groov::field<"TIMEOUTB", std::uint32_t, 27, 16>,
      groov::field<"TIMOUTEN", bool, 15, 15>,
      groov::field<"TIDLE", bool, 12, 12>,
      groov::field<"TIMEOUTA", std::uint32_t, 11, 0>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_isr =
    groov::reg<
      "isr", std::uint32_t,
      BaseAddress+0x18, access::rw,

      groov::field<"ADDCODE", std::uint8_t, 23, 17>,
      groov::field<"DIR", bool, 16, 16>,
      groov::field<"BUSY", bool, 15, 15>,
      groov::field<"ALERT", bool, 13, 13>,
      groov::field<"TIMEOUT", bool, 12, 12>,
      groov::field<"PECERR", bool, 11, 11>,
      groov::field<"OCR", bool, 10, 10>,
      groov::field<"ARLO", bool, 9, 9>,
      groov::field<"BERR", bool, 8, 8>,
      groov::field<"TCR", bool, 7, 7>,
      groov::field<"TC", bool, 6, 6>,
      groov::field<"STOPF", bool, 5, 5>,
      groov::field<"NACKF", bool, 4, 4>,
      groov::field<"ADDR", bool, 3, 3>,
      groov::field<"RXNE", bool, 2, 2>,
      groov::field<"TXIS", bool, 1, 1>,
      groov::field<"TXE", bool, 0, 0>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_icr =
    groov::reg<
      "icr", std::uint32_t,
      BaseAddress+0x1c, access::rw,  // TODO: FIX THIS FOR WRITE ONLY

      groov::field<"ALERTCF", bool, 13, 13>,
      groov::field<"TIMOUTCF", bool, 12, 12>,
      groov::field<"PECCF", bool, 11, 11>,
      groov::field<"OVRCF", bool, 10, 10>,
      groov::field<"ARLOCF", bool, 9, 9>,
      groov::field<"BERRCF", bool, 8, 8>,
      groov::field<"STOPCF", bool, 5, 5>,
      groov::field<"NACKFCF", bool, 4, 4>,
      groov::field<"ADDRCF", bool, 3, 3>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_pecr =
    groov::reg<
      "pecr", std::uint32_t,
      BaseAddress+0x20, access::rw,

      groov::field<"PEC", std::uint8_t, 7, 0>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_rxdr =
    groov::reg<
      "rxdr", std::uint32_t,
      BaseAddress+0x24, access::rw,

      groov::field<"RXDATA", std::uint8_t, 7, 0>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_txdr =
    groov::reg<
      "txdr", std::uint32_t,
      BaseAddress+0x28, access::rw,

      groov::field<"TXDATA", std::uint8_t, 7, 0>
    >;
}

