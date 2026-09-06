//
// Copyright (c) 2026 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// STM32 register descriptions for the SPI device.
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

  namespace spi {
    // SPIx_CR1.BR -- the serial clock is f(PCLK) divided by one of these.
    enum class baud : std::uint8_t {
      div2   = 0b000,
      div4   = 0b001,
      div8   = 0b010,
      div16  = 0b011,
      div32  = 0b100,
      div64  = 0b101,
      div128 = 0b110,
      div256 = 0b111
    };

    // SPIx_CR2.DS. Codes below 0b0011 are forced to 8-bit by hardware.
    enum class datasize : std::uint8_t {
      bits4  = 0b0011,
      bits5  = 0b0100,
      bits6  = 0b0101,
      bits7  = 0b0110,
      bits8  = 0b0111,
      bits9  = 0b1000,
      bits10 = 0b1001,
      bits11 = 0b1010,
      bits12 = 0b1011,
      bits13 = 0b1100,
      bits14 = 0b1101,
      bits15 = 0b1110,
      bits16 = 0b1111
    };

    // SPIx_CR2.FRXTH -- the RXNE threshold. Frames of 8 bits or fewer need
    // the quarter-full setting or RXNE never rises for a single byte.
    enum class rx_threshold : bool {
      half    = false,
      quarter = true
    };

    // SPIx_CR2.FRF
    enum class frame_format : bool {
      motorola = false,
      ti       = true
    };

    // SPIx_SR.FTLVL and .FRLVL
    enum class fifo_level : std::uint8_t {
      empty   = 0b00,
      quarter = 0b01,
      half    = 0b10,
      full    = 0b11
    };
  }

  // BIDIMODE with BIDIOE gives half-duplex transmit on a single line; in
  // master mode that line is MOSI, which leaves MISO and SCK free and
  // removes the receive path entirely.
  template <std::uintptr_t BaseAddress>
  using spi_cr1 =
    groov::reg<
      "cr1", std::uint32_t,
      BaseAddress+0x00, access::rw,

      groov::field<"reserved0", uint32_t  , 31, 16, access::ro>,
      groov::field<"BIDIMODE" , bit_enable, 15, 15>,
      groov::field<"BIDIOE"   , bit_enable, 14, 14>,
      groov::field<"CRCEN"    , bit_enable, 13, 13>,
      groov::field<"CRCNEXT"  , bool      , 12, 12>,
      groov::field<"CRCL"     , bool      , 11, 11>,
      groov::field<"RXONLY"   , bit_enable, 10, 10>,
      groov::field<"SSM"      , bit_enable,  9,  9>,
      groov::field<"SSI"      , bool      ,  8,  8>,
      groov::field<"LSBFIRST" , bool      ,  7,  7>,
      groov::field<"SPE"      , bit_enable,  6,  6>,
      groov::field<"BR"       , spi::baud ,  5,  3>,
      groov::field<"MSTR"     , bool      ,  2,  2>,
      groov::field<"CPOL"     , bool      ,  1,  1>,
      groov::field<"CPHA"     , bool      ,  0,  0>
    >;

  template <std::uintptr_t BaseAddress>
  using spi_cr2 =
    groov::reg<
      "cr2", std::uint32_t,
      BaseAddress+0x04, access::rw,

      groov::field<"reserved0", uint32_t          , 31, 15, access::ro>,
      groov::field<"LDMA_TX"  , bool              , 14, 14>,
      groov::field<"LDMA_RX"  , bool              , 13, 13>,
      groov::field<"FRXTH"    , spi::rx_threshold , 12, 12>,
      groov::field<"DS"       , spi::datasize     , 11,  8>,
      groov::field<"TXEIE"    , bit_enable        ,  7,  7>,
      groov::field<"RXNEIE"   , bit_enable        ,  6,  6>,
      groov::field<"ERRIE"    , bit_enable        ,  5,  5>,
      groov::field<"FRF"      , spi::frame_format ,  4,  4>,
      groov::field<"NSSP"     , bit_enable        ,  3,  3>,
      groov::field<"SSOE"     , bit_enable        ,  2,  2>,
      groov::field<"TXDMAEN"  , bit_enable        ,  1,  1>,
      groov::field<"RXDMAEN"  , bit_enable        ,  0,  0>
    >;

  template <std::uintptr_t BaseAddress>
  using spi_sr =
    groov::reg<
      "sr", std::uint32_t,
      BaseAddress+0x08, access::rw,

      groov::field<"reserved0", uint32_t        , 31, 13, access::ro>,
      groov::field<"FTLVL"    , spi::fifo_level , 12, 11, access::ro>,
      groov::field<"FRLVL"    , spi::fifo_level , 10,  9, access::ro>,
      groov::field<"FRE"      , bool            ,  8,  8, access::ro>,
      groov::field<"BSY"      , bool            ,  7,  7, access::ro>,
      groov::field<"OVR"      , bool            ,  6,  6, access::ro>,
      groov::field<"MODF"     , bool            ,  5,  5, access::ro>,
      groov::field<"CRCERR"   , bool            ,  4,  4>,
      groov::field<"reserved1", uint8_t         ,  3,  2, access::ro>,
      groov::field<"TXE"      , bool            ,  1,  1, access::ro>,
      groov::field<"RXNE"     , bool            ,  0,  0, access::ro>
    >;

  // The data register is the boundary between the Tx and Rx FIFOs, and the
  // access width decides how many frames a write pushes: with DS <= 8 a
  // 16-bit write enqueues *two* frames. Two flavours are provided for the
  // same reason timx_ccr1_16 and timx_ccr1_32 both exist -- pick the one
  // matching the configured frame size.
  //
  // DMA is unaffected either way; PSIZE controls the access width there.
  template <std::uintptr_t BaseAddress>
  using spi_dr_8 =
    groov::reg<
      "dr", std::uint8_t,
      BaseAddress+0x0c, access::rw,

      groov::field<"DR", std::uint8_t, 7, 0>
    >;

  template <std::uintptr_t BaseAddress>
  using spi_dr_16 =
    groov::reg<
      "dr", std::uint32_t,
      BaseAddress+0x0c, access::rw,

      groov::field<"reserved0", uint32_t, 31, 16, access::ro>,
      groov::field<"DR", std::uint32_t, 15, 0>
    >;

  template <std::uintptr_t BaseAddress>
  using spi_crcpr =
    groov::reg<
      "crcpr", std::uint32_t,
      BaseAddress+0x10, access::rw,

      groov::field<"reserved0", uint32_t, 31, 16, access::ro>,
      groov::field<"CRCPOLY", std::uint32_t, 15, 0>
    >;

  template <std::uintptr_t BaseAddress>
  using spi_rxcrcr =
    groov::reg<
      "rxcrcr", std::uint32_t,
      BaseAddress+0x14, access::rw,

      groov::field<"reserved0", uint32_t, 31, 16, access::ro>,
      groov::field<"RXCRC", std::uint32_t, 15, 0, access::ro>
    >;

  template <std::uintptr_t BaseAddress>
  using spi_txcrcr =
    groov::reg<
      "txcrcr", std::uint32_t,
      BaseAddress+0x18, access::rw,

      groov::field<"reserved0", uint32_t, 31, 16, access::ro>,
      groov::field<"TXCRC", std::uint32_t, 15, 0, access::ro>
    >;
}
