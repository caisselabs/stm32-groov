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

  template <std::uint32_t BaseAddress>
  using i2c_cr1 =
    groov::reg<
      "cr1", std::uint32_t,
      BaseAddress+0x00, groov::w::replace,

      groov::field<"PECEN", bool, 23, 23>,
      groov::field<"ALERTEN", bool, 22, 22>,
      groov::field<"SMBDEN", bool, 21, 21>,
      groov::field<"SMBHEN", bool, 20, 20>,
      groov::field<"GCEN", bool, 19, 19>,
      groov::field<"WUPEN", bool, 18, 18>,
      groov::field<"NOSTRETCH", bool, 17, 17>,
      groov::field<"SBC", bool, 16, 16>,
      groov::field<"RXDMAEN", bool, 15, 15>,
      groov::field<"TXDMAEN", bool, 14, 14>,
      groov::field<"ANFOFF", bool, 12, 12>,
      groov::field<"DNF", std::uint8_t, 11, 8>,
      groov::field<"ERRIE", bool, 7, 7>,
      groov::field<"TCIE", bool, 6, 6>,
      groov::field<"STOPIE", bool, 5, 5>,
      groov::field<"MACKIE", bool, 4, 4>,
      groov::field<"ADDRIE", bool, 3, 3>,
      groov::field<"RXIE", bool, 2, 2>,
      groov::field<"TXIE", bool, 1, 1>,
      groov::field<"PE", bool, 0, 0>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_cr2 =
    groov::reg<
      "cr2", std::uint32_t,
      BaseAddress+0x04, groov::w::replace,

      groov::field<"PECBYTE", bool, 26, 26>,
      groov::field<"AUTOEND", bool, 25, 25>,
      groov::field<"RELOAD", bool, 24, 24>,
      groov::field<"NBYTES", std::uint8_t, 23, 16>,
      groov::field<"NACK", bool, 15, 15>,
      groov::field<"STOP", bool, 14, 14>,
      groov::field<"START", bool, 13, 13>,
      groov::field<"HEAD10R", bool, 12, 12>,
      groov::field<"ADD10", bool, 11, 11>,
      groov::field<"RD_WRN", bool, 10, 10>,
      groov::field<"SADD", std::uint32_t, 9, 0>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_oar1 =
    groov::reg<
      "oar1", std::uint32_t,
      BaseAddress+0x08, groov::w::replace,

      groov::field<"OA1EN", bool, 15, 15>,
      groov::field<"OA1MODE", bool, 10, 10>,
      groov::field<"OA1", std::uint32_t, 9, 0>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_oar2 =
    groov::reg<
      "oar2", std::uint32_t,
      BaseAddress+0x0c, groov::w::replace,

      groov::field<"OA2EN", bool, 15, 15>,
      groov::field<"OA2MSK", std::uint8_t, 10, 8>,
      groov::field<"OA2", std::uint8_t, 7, 1>
    >;

  template <std::uint32_t BaseAddress>
  using i2c_timingr =
    groov::reg<
      "timingr", std::uint32_t,
      BaseAddress+0x10, groov::w::replace,

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
      BaseAddress+0x14, groov::w::replace,

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
      BaseAddress+0x18, groov::w::replace,

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
      BaseAddress+0x1c, groov::w::replace,

      groov::field<"ALERTCF", bool, 13, 13>,
      groov::field<"TIMOUTCF", bool, 12, 12>,
      groov::field<"PECCF", bool, 11, 11>,
      groov::field<"OVRCF", bool, 10, 10>,
      groov::field<"ARLOCF", bool, 9, 9>,
      groov::field<"BERRCF", bool, 8, 8>,
      groov::field<"STOPFCF", bool, 5, 5>,
      groov::field<"NACKFCF", bool, 4, 4>,
      groov::field<"ADDRCF", bool, 3, 3>
    >;
  
  template <std::uint32_t BaseAddress>
  using i2c_pecr =
    groov::reg<
      "pecr", std::uint32_t,
      BaseAddress+0x20, groov::w::replace,

      groov::field<"PEC", std::uint8_t, 7, 0>
    >;  

  template <std::uint32_t BaseAddress>
  using i2c_rxdr =
    groov::reg<
      "rxdr", std::uint32_t,
      BaseAddress+0x24, groov::w::replace,

      groov::field<"RXDATA", std::uint8_t, 7, 0>
    >;  

  template <std::uint32_t BaseAddress>
  using i2c_txdr =
    groov::reg<
      "txdr", std::uint32_t,
      BaseAddress+0x28, groov::w::replace,

      groov::field<"TXDATA", std::uint8_t, 7, 0>
    >;  
}

