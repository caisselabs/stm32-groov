//
// Copyright (c) 2024 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// STM32 register descriptions for the USART device.
//
#pragma once

#include <groov/config.hpp>

#include <cstdint>


namespace caisselabs::stm32 {

  template <std::uint32_t BaseAddress>
  using usart_cr1 =
    groov::reg<
      "cr1", std::uint32_t,
      BaseAddress+0x00, groov::w::replace,

      groov::field<"M1"     , bool, 28, 28>,
      groov::field<"EOBIE"  , bool, 27, 27>,
      groov::field<"RTOIE"  , bool, 26, 26>,
      groov::field<"DEAT4"  , bool, 25, 25>,
      groov::field<"DEAT3"  , bool, 24, 24>,
      groov::field<"DEAT2"  , bool, 23, 23>,
      groov::field<"DEAT1"  , bool, 22, 22>,
      groov::field<"DEAT0"  , bool, 21, 21>,
      groov::field<"DEDT4"  , bool, 20, 20>,
      groov::field<"DEDT3"  , bool, 19, 19>,
      groov::field<"DEDT2"  , bool, 18, 18>,
      groov::field<"DEDT1"  , bool, 17, 17>,
      groov::field<"DEDT0"  , bool, 16, 16>,
      groov::field<"OVER8"  , bool, 15, 15>,
      groov::field<"CMIE"   , bool, 14, 14>,
      groov::field<"MME"    , bool, 13, 13>,
      groov::field<"M0"     , bool, 12, 12>,
      groov::field<"WAKE"   , bool, 11, 11>,
      groov::field<"PCE"    , bool, 10, 10>,
      groov::field<"PS"     , bool,  9,  9>,
      groov::field<"PEIE"   , bool,  8,  8>,
      groov::field<"TXEIE"  , bool,  7,  7>,
      groov::field<"TCIE"   , bool,  6,  6>,
      groov::field<"RXNEIE" , bool,  5,  5>,
      groov::field<"IDLEIE" , bool,  4,  4>,
      groov::field<"TE"     , bool,  3,  3>,
      groov::field<"RE"     , bool,  2,  2>,
      groov::field<"UE"     , bool,  0,  0>
    >;

  
  template <std::uint32_t BaseAddress>
  using usart_cr2 =
    groov::reg<
      "cr2", std::uint32_t,
      BaseAddress+0x04, groov::w::replace,

      groov::field<"ADD"      , std::uint8_t, 31, 24>,
      groov::field<"RTOEN"    , bool        , 23, 23>,
      groov::field<"ABRMOD1"  , bool        , 22, 22>,
      groov::field<"ABRMOD0"  , bool        , 21, 21>,
      groov::field<"ABREN"    , bool        , 20, 20>,
      groov::field<"MSBFIRST" , bool        , 19, 19>,
      groov::field<"DATAINV"  , bool        , 18, 18>,
      groov::field<"TXINV"    , bool        , 17, 17>,
      groov::field<"RXINV"    , bool        , 16, 16>,
      groov::field<"SWAP"     , bool        , 15, 15>,
      groov::field<"LINEN"    , bool        , 14, 14>,
      groov::field<"STOP"     , std::uint8_t, 13, 12>,
      groov::field<"CLKEN"    , bool        , 11, 11>,
      groov::field<"CPOL"     , bool        , 10, 10>,
      groov::field<"CPHA"     , bool        , 9, 9>,
      groov::field<"LBCL"     , bool        , 8, 8>,
      groov::field<"LBDIE"    , bool        , 6, 6>,
      groov::field<"LBDL"     , bool        , 5, 5>,
      groov::field<"ADDM7"    , bool        , 4, 4>
    >;


  template <std::uint32_t BaseAddress>
  using usart_cr3 =
    groov::reg<
      "cr3", std::uint32_t,
      BaseAddress+0x08, groov::w::replace,

      groov::field<"TCBGTIE"     , bool, 24, 24>,
      groov::field<"UCESM"     , bool, 23, 23>,
      groov::field<"WUFIE"     , bool, 22, 22>,
      groov::field<"WUS"     , std::uint8_t, 21, 20>,
      groov::field<"SCRARCNT"     , std::uint8_t, 19, 17>,
      groov::field<"DEP"     , bool, 15, 15>,
      groov::field<"DEM"     , bool, 14, 14>,
      groov::field<"DDRE"     , bool, 13, 13>,
      groov::field<"OVRDIS"     , bool, 12, 12>,
      groov::field<"ONEBIT"     , bool, 11, 11>,
      groov::field<"CTSIE"     , bool, 10, 10>,
      groov::field<"CTSE"     , bool, 9, 9>,
      groov::field<"RTSE"     , bool, 8, 8>,
      groov::field<"DMAT"     , bool, 7, 7>,
      groov::field<"DMAR"     , bool, 6, 6>,
      groov::field<"SCEN"     , bool, 5, 5>,
      groov::field<"NACK"     , bool, 4, 4>,
      groov::field<"HDSEL"     , bool, 3, 3>,
      groov::field<"IRLP"     , bool, 2, 2>,
      groov::field<"IREN"     , bool, 1, 1>,
      groov::field<"EIE"     , bool, 0, 0>
    >;

  template <std::uint32_t BaseAddress>
  using usart_brr =
    groov::reg<
      "brr", std::uint32_t,
      BaseAddress+0x0c, groov::w::replace,

      groov::field<"BRR"     , std::uint32_t, 15, 0>  // uint16_t?
    >;

  template <std::uint32_t BaseAddress>
  using usart_gtpr =
    groov::reg<
      "gtpr", std::uint32_t,
      BaseAddress+0x10, groov::w::replace,

      groov::field<"GT"     , std::uint8_t, 15, 8>,
      groov::field<"PSC"     , std::uint8_t, 7, 0>
    >;

  template <std::uint32_t BaseAddress>
  using usart_rtor =
    groov::reg<
      "gtpr", std::uint32_t,
      BaseAddress+0x14, groov::w::replace,

      groov::field<"BLEN"     , std::uint8_t, 31, 24>,
      groov::field<"RTO"     , std::uint32_t, 23, 0>
    >;

  template <std::uint32_t BaseAddress>
  using usart_rqr =
    groov::reg<
      "rqr", std::uint32_t,
      BaseAddress+0x18, groov::w::replace,

      groov::field<"TXFRQ"     , bool, 4, 4>,
      groov::field<"RXFRQ"     , bool, 3, 3>,
      groov::field<"MMRQ"     , bool, 2, 2>,
      groov::field<"SBKRQ"     , bool, 1, 1>,
      groov::field<"ABRRQ"     , bool, 0, 0>
    >;

  template <std::uint32_t BaseAddress>
  using usart_isr =
    groov::reg<
      "isr", std::uint32_t,
      BaseAddress+0x1c, groov::w::replace,

      groov::field<"TCBGT"     , bool, 25, 25>,
      groov::field<"REACK"     , bool, 22, 22>,
      groov::field<"TEACK"     , bool, 21, 21>,
      groov::field<"WUF"     , bool, 20, 20>,
      groov::field<"RWU"     , bool, 19, 19>,
      groov::field<"SBKF"     , bool, 18, 18>,
      groov::field<"CMF"     , bool, 17, 17>,
      groov::field<"BUSY"     , bool, 16, 16>,
      groov::field<"ABRF"     , bool, 15, 15>,
      groov::field<"ABRE"     , bool, 14, 14>,
      groov::field<"EOBF"     , bool, 12, 12>,
      groov::field<"RTOF"     , bool, 11, 11>,
      groov::field<"CTS"     , bool, 10, 10>,
      groov::field<"CTSIF"     , bool, 9, 9>,
      groov::field<"LBDF"     , bool, 8, 8>,
      groov::field<"TXE"     , bool, 7, 7>,
      groov::field<"TC"     , bool, 6, 6>,
      groov::field<"RXNE"     , bool, 5, 5>,
      groov::field<"IDLE"     , bool, 4, 4>,
      groov::field<"ORE"     , bool, 3, 3>,
      groov::field<"NF"     , bool, 2, 2>,
      groov::field<"FE"     , bool, 1, 1>,
      groov::field<"PE"     , bool, 0, 0>
    >;

  template <std::uint32_t BaseAddress>
  using usart_icr =
    groov::reg<
      "icr", std::uint32_t,
      BaseAddress+0x20, groov::w::replace,

      groov::field<"WUCF"     , bool, 20, 20>,
      groov::field<"CMCF"     , bool, 17, 17>,
      groov::field<"EOBCF"     , bool, 12, 12>,
      groov::field<"RTOCF"     , bool, 11, 11>,
      groov::field<"CTSCF"     , bool, 9, 9>,
      groov::field<"LBDCF"     , bool, 8, 8>,
      groov::field<"TCBGTCF"     , bool, 7, 7>,
      groov::field<"TCCF"     , bool, 6, 6>,
      groov::field<"IDLECF"     , bool, 4, 4>,
      groov::field<"ORECF"     , bool, 3, 3>,
      groov::field<"NCF"     , bool, 2, 2>,
      groov::field<"FECF"     , bool, 1, 1>,
      groov::field<"PECF"     , bool, 0, 0>
    >;

  template <std::uint32_t BaseAddress>
  using usart_rdr =
    groov::reg<
      "rdr", std::uint32_t,
      BaseAddress+0x24, groov::w::replace,

      groov::field<"RDR"     , std::uint32_t, 8, 0>
    >;

  template <std::uint32_t BaseAddress>
  using usart_tdr =
    groov::reg<
      "tdr", std::uint32_t,
      BaseAddress+0x28, groov::w::replace,

      groov::field<"_reserved", std::uint32_t, 31, 9, groov::w::read_only>,
      groov::field<"TDR"      , std::uint32_t,  8, 0>
    >;
}

