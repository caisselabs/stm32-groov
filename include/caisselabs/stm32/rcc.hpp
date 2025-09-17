//
// Copyright (c) 2024, 2025 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// STM32 register descriptions for the RCC : Reset Clock Control
//
// clang-format off
#pragma once

#include <caisselabs/stm32/enable.hpp>
#include <caisselabs/stm32/access.hpp>

#include <groov/config.hpp>

#include <cstdint>


namespace caisselabs::stm32 {

  using std::uint8_t;
  using std::uint32_t;

  namespace rccx {
    enum class msirange : std::uint8_t {
        _100kHz = 0b0000,
        _200kHz = 0b0001,
        _400kHz = 0b0010,
        _800kHz = 0b0011,
          _1MHz = 0b0100,
          _2MHz = 0b0101,
          _4MHz = 0b0110,
          _8MHz = 0b0111,
         _16MHz = 0b1000,
         _24MHz = 0b1001,
         _32MHz = 0b1010,
         _48MHz = 0b1011
    };

    enum class msirgsel : bool {
      rcc_csr = false,
      rcc_cr  = true
    };
  }

  template <std::uint32_t BaseAddress>
  using rcc_cr =
    groov::reg<
      "cr", std::uint32_t,
      BaseAddress+0x00, access::rw,

      groov::field<"reserved0" , uint8_t      , 31, 28, access::ro>,
      groov::field<"PLLSAI1RDY", bit_locked   , 27, 27, access::ro>,
      groov::field<"PLLSAI1ON" , bit_enable   , 26, 26>,
      groov::field<"PLLRDY"    , bit_locked   , 25, 25, access::ro>,
      groov::field<"PLLON"     , bit_enable   , 24, 24>,
      groov::field<"reserved1" , uint8_t      , 23, 20, access::ro>,
      groov::field<"CSSON"     , bit_enable   , 19, 19>,
      groov::field<"HSEBYP"    , bit_enable   , 18, 18>,
      groov::field<"HSERDY"    , bit_ready    , 17, 17, access::ro>,
      groov::field<"HSEON"     , bit_enable   , 16, 16>,
      groov::field<"reserved2" , uint8_t      , 15, 12, access::ro>,
      groov::field<"HSIASFS"   , bit_enable   , 11, 11>,
      groov::field<"HSIRDY"    , bit_ready    , 10, 10, access::ro>,
      groov::field<"HSIKERON"  , bit_enable   ,  9,  9>,
      groov::field<"HSION"     , bit_enable   ,  8,  8>,
      groov::field<"MSIRANGE"  , rccx::msirange, 7,  4>,
      groov::field<"MSIRGSEL"  , rccx::msirgsel, 3,  3>,
      groov::field<"MSIPLLEN"  , bit_enable   ,  2,  2>,
      groov::field<"MSIRDY"    , bit_ready    ,  1,  1, access::ro>,
      groov::field<"MSION"     , bit_enable   ,  0,  0>
    >;


  namespace rccx {
    enum class mcopre : std::uint8_t {
      div1   = 0b000,
      div2   = 0b001,
      div4   = 0b010,
      div8   = 0b011,
      div16  = 0b100
    };

    enum class mcosel : std::uint8_t {
      DISABLE   = 0b0000,
      no_clock  = 0b0000,
      SYSCLK    = 0b0001,
      MSI       = 0b0010,
      HSI16     = 0b0011,
      HSE       = 0b0100,
      PLL       = 0b0101,
      LSI       = 0b0110,
      LSE       = 0b0111,
      HSI48     = 0b1000
    };

    enum class stopwuck : bool {
      MSI   = false,
      HSI16 = true
    };

    enum class ppre : std::uint8_t {
      DISABLE = 0b000,
      div1    = 0b000,
      div2    = 0b100,
      div4    = 0b101,
      div8    = 0b110,
      div16   = 0b111
    };

    enum class hpre : std::uint8_t {
      DISABLE = 0b0000,
      div1    = 0b0000,
      div2    = 0b1000,
      div4    = 0b1001,
      div8    = 0b1010,
      div16   = 0b1011,
      div64   = 0b1100,
      div128  = 0b1101,
      div256  = 0b1110,
      div512  = 0b1111
    };

    enum class sw : std::uint8_t {
      MSI   = 0b00,
      HSI16 = 0b01,
      HSE   = 0b10,
      PLL   = 0b11
    };
  }

  template <std::uint32_t BaseAddress>
  using rcc_cfgr =
    groov::reg<
      "cfgr", std::uint32_t,
      BaseAddress+0x08, access::rw,

      groov::field<"reserved0" , bool          , 31, 31, access::ro>,
      groov::field<"MCOPRE"    , rccx::mcopre  , 30, 28>,
      groov::field<"MCOSEL"    , rccx::mcosel  , 27, 24>,
      groov::field<"reserved1" , uint8_t       , 23, 16, access::ro>,
      groov::field<"STOPWUCK"  , rccx::stopwuck, 15, 15>,
      groov::field<"reserved2" , bool          , 14, 14, access::ro>,
      groov::field<"PPRE2"     , rccx::ppre    , 13, 11>,
      groov::field<"PPRE1"     , rccx::ppre    , 10,  8>,
      groov::field<"HPRE"      , rccx::hpre    ,  7,  4>,
      groov::field<"SWS"       , rccx::sw      ,  3,  2>,
      groov::field<"SW"        , rccx::sw      ,  1,  0>
    >;


  // TODO: mjc - These are really set-only bits. Write only. RMW is not meaningful
  template <std::uint32_t BaseAddress>
  using rcc_apb1rstr1 =
    groov::reg<
      "apb1rstr1", std::uint32_t,
      BaseAddress+0x38, access::rw,

      groov::field<"LPTIM1RST" , bit_reset, 31, 31>,
      groov::field<"OPAMPRST " , bit_reset, 30, 30>,
      groov::field<"DAC1RST"   , bit_reset, 29, 29>,
      groov::field<"PWRRST"    , bit_reset, 28, 28>,
      groov::field<"reserved0" , bool     , 27, 27, access::ro>,
      groov::field<"USBFSRST"  , bit_reset, 26, 26>,
      groov::field<"CAN1RST"   , bit_reset, 25, 25>,
      groov::field<"CRSRST"    , bit_reset, 24, 24>,
      groov::field<"I2C3RST"   , bit_reset, 23, 23>,
      groov::field<"I2C2RST"   , bit_reset, 22, 22>,
      groov::field<"I2C1RST"   , bit_reset, 21, 21>,
      groov::field<"reserved1" , bool     , 20, 20, access::ro>,
      groov::field<"USART4RST" , bit_reset, 19, 19>,
      groov::field<"USART3RST" , bit_reset, 18, 18>,
      groov::field<"USART2RST" , bit_reset, 17, 17>,
      groov::field<"reserved2" , bool     , 16, 16, access::ro>,
      groov::field<"SPI3RST"   , bit_reset, 15, 15>,
      groov::field<"SPI2RST"   , bit_reset, 14, 14>,
      groov::field<"reserved3" , uint8_t  , 13, 10, access::ro>,
      groov::field<"LCDRST"    , bit_reset,  9,  9>,
      groov::field<"reserved4" , uint8_t  ,  8,  6, access::ro>,
      groov::field<"TIM7RST"   , bit_reset,  5,  5>,
      groov::field<"TIM6RST"   , bit_reset,  4,  4>,
      groov::field<"reserved5" , uint8_t  ,  3,  2, access::ro>,
      groov::field<"TIM3RST"   , bit_reset,  1,  1>,
      groov::field<"TIM2RST"   , bit_reset,  0,  0>
    >;

  // TODO: mjc - These are really set-only bits. Write only. RMW is not meaningful
  template <std::uint32_t BaseAddress>
  using rcc_apb2rstr =
    groov::reg<
      "apb2rstr", std::uint32_t,
      BaseAddress+0x40, access::rw,

      groov::field<"reserved0" , uint8_t  , 31, 25, access::ro>,
      groov::field<"DFSDM1RST" , bit_reset, 24, 24>,
      groov::field<"reserved1" , uint8_t  , 23, 22, access::ro>,
      groov::field<"SAI1RST"   , bit_reset, 21, 21>,
      groov::field<"reserved2" , uint8_t  , 20, 18, access::ro>,
      groov::field<"TIM16RST"  , bit_reset, 17, 17>,
      groov::field<"TIM15RST"  , bit_reset, 16, 16>,
      groov::field<"reserved3" , bool     , 15, 15, access::ro>,
      groov::field<"USART1RST" , bit_reset, 14, 14>,
      groov::field<"reserved4" , bool     , 13, 13, access::ro>,
      groov::field<"SPI1RST"   , bit_reset, 12, 12>,
      groov::field<"TIM1RST"   , bit_reset, 11, 11>,
      groov::field<"SDMMC1RST" , bit_reset, 10, 10>,
      groov::field<"reserved5" , uint32_t ,  9,  1, access::ro>,
      groov::field<"SYSCFGRST" , bit_reset,  0,  0>
    >;

  template <std::uint32_t BaseAddress>
  using rcc_ahb2enr =
    groov::reg<
      "ahb2enr", std::uint32_t,
      BaseAddress+0x4c, access::rw,

      groov::field<"reserved0", uint32_t  , 31, 17, access::ro>,
      groov::field<"RNGEN"    , bit_enable, 18, 18>,
      groov::field<"reserved1", bool      , 17, 17, access::ro>,
      groov::field<"AESEN"    , bit_enable, 16, 16>,
      groov::field<"reserved2", uint8_t   , 15, 14, access::ro>,
      groov::field<"ADCEN"    , bit_enable, 13, 13>,
      groov::field<"reserved3", uint8_t   , 12,  8, access::ro>,
      groov::field<"GPIOHEN"  , bit_enable,  7,  7>,
      groov::field<"reserved4", uint8_t   ,  6,  5, access::ro>,
      groov::field<"GPIOEEN"  , bit_enable,  4,  4>,
      groov::field<"GPIODEN"  , bit_enable,  3,  3>,
      groov::field<"GPIOCEN"  , bit_enable,  2,  2>,
      groov::field<"GPIOBEN"  , bit_enable,  1,  1>,
      groov::field<"GPIOAEN"  , bit_enable,  0,  0>
    >;


  template <std::uint32_t BaseAddress>
  using rcc_apb1enr1 =
    groov::reg<
      "apb1enr1", std::uint32_t,
      BaseAddress+0x58, access::rw,

      groov::field<"LPTIM1EN" , bit_enable  , 31, 31>,
      groov::field<"OPAMPEN"  , bit_enable  , 30, 30>,
      groov::field<"DAC1EN"   , bit_enable  , 29, 29>,
      groov::field<"PWREN"    , bit_enable  , 28, 28>,
      groov::field<"reserved0", bool        , 27, 27, access::ro>,
      groov::field<"USBFSEN"  , bit_enable  , 26, 26>,
      groov::field<"CAN1EN"   , bit_enable  , 25, 25>,
      groov::field<"CRSEN"    , bit_enable  , 24, 24>,
      groov::field<"I2C3EN"   , bit_enable  , 23, 23>,
      groov::field<"I2C2EN"   , bit_enable  , 22, 22>,
      groov::field<"I2C1EN"   , bit_enable  , 21, 21>,
      groov::field<"reserved1", bool        , 20, 20, access::ro>,
      groov::field<"UART4EN"  , bit_enable  , 19, 19>,
      groov::field<"USART3EN" , bit_enable  , 18, 18>,
      groov::field<"USART2EN" , bit_enable  , 17, 17>,
      groov::field<"reserved2", bool        , 16, 16, access::ro>,
      groov::field<"SP3EN"    , bit_enable  , 15, 15>,
      groov::field<"SPI2EN"   , bit_enable  , 14, 14>,
      groov::field<"reserved3", std::uint8_t, 13, 12, access::ro>,
      groov::field<"WWDGEN"   , bit_enable  , 11, 11>,
      groov::field<"RTCAPBEN" , bit_enable  , 10, 10>,
      groov::field<"LCDEN"    , bit_enable  ,  9,  9>,
      groov::field<"reserved4", std::uint8_t,  8,  6, access::ro>,
      groov::field<"TIM7EN"   , bit_enable  ,  5,  5>,
      groov::field<"TIM6EN"   , bit_enable  ,  4,  4>,
      groov::field<"reserved5", std::uint8_t,  3,  2, access::ro>,
      groov::field<"TIM3EN"   , bit_enable  ,  1,  1>,
      groov::field<"TIM2EN"   , bit_enable  ,  0,  0>
    >;

  template <std::uint32_t BaseAddress>
  using rcc_apb2enr =
    groov::reg<
      "apb2enr", std::uint32_t,
      BaseAddress+0x60, access::rw,

      groov::field<"reserved0" , uint8_t   , 31, 25, access::ro>,
      groov::field<"DFSDM1EN"  , bit_enable, 24, 24>,
      groov::field<"reserved1" , uint8_t   , 23, 22, access::ro>,
      groov::field<"SAI1EN"    , bit_enable, 21, 21>,
      groov::field<"reserved2" , uint8_t   , 20, 18, access::ro>,
      groov::field<"TIM16EN"   , bit_enable, 17, 17>,
      groov::field<"TIM15EN"   , bit_enable, 16, 16>,
      groov::field<"reserved3" , bool      , 15, 15, access::ro>,
      groov::field<"USART1EN"  , bit_enable, 14, 14>,
      groov::field<"reserved4" , bool      , 13, 13, access::ro>,
      groov::field<"SPI1EN"    , bit_enable, 12, 12>,
      groov::field<"TIM1EN"    , bit_enable, 11, 11>,
      groov::field<"SDMMC1EN"  , bit_enable, 10, 10>,
      groov::field<"reserved5" , uint8_t   ,  9,  8, access::ro>,
      groov::field<"FWEN"      , bit_enable,  7,  7>,
      groov::field<"reserved6" , uint8_t   ,  6,  1, access::ro>,
      groov::field<"SYSCFGEN"  , bit_enable,  0,  0>
    >;

  template <std::uint32_t BaseAddress>
  using rcc_apb2smenr =
    groov::reg<
      "apb2smenr", std::uint32_t,
      BaseAddress+0x80, groov::w::replace,

      groov::field<"reserved0" , uint32_t  , 31, 22, access::ro>,
      groov::field<"SAI1SMEN"  , bit_enable, 21, 21>,
      groov::field<"reserved1" , uint8_t   , 20, 18, access::ro>,
      groov::field<"TIM16SMEN" , bit_enable, 17, 17>,
      groov::field<"TIM15SMEN" , bit_enable, 16, 16>,
      groov::field<"reserved2" , bool      , 15, 15, access::ro>,
      groov::field<"USART1SMEN", bit_enable, 14, 14>,
      groov::field<"reserved3" , bool      , 13, 13, access::ro>,
      groov::field<"SPI1SMEN"  , bit_enable, 12, 12>,
      groov::field<"TIM1SMEN"  , bit_enable, 11, 11>,
      groov::field<"SDMMC1SMEN", bit_enable, 10, 10>,
      groov::field<"reserved4" , uint32_t  ,  9,  1, access::ro>,
      groov::field<"SYSCFGSMEN", bit_enable,  0,  0>
    >;

  namespace rccx {
    enum class swpmi1 : bool {
      APB1   = 0b0,
      PCLK1  = 0b0,
      HSI16  = 0b1
    };

    enum class adcclk : std::uint8_t {
      no_clk   = 0b00,
      PLLSAI1  = 0b01,
      SYSCLK   = 0b11
    };

    enum class clk48clk : std::uint8_t {
      HSI48    = 0b00,
      PLLSAI1  = 0b01,
      PLL      = 0b10,
      MSI      = 0b11
    };

    enum class sai1clk : std::uint8_t {
      PLLSAI       = 0b00,
      PLL          = 0b10,
      SAI1_EXTCLK  = 0b11
    };

    enum class lptimclk : std::uint8_t {
      PCLK   = 0b00,
      LSI    = 0b01,
      HSI16  = 0b10,
      LSE    = 0b11
    };

    enum class i2cclk : std::uint8_t {
      PCLK   = 0b00,
      SYSCLK = 0b01,
      HSI16  = 0b10
    };

    enum class usartclk : std::uint8_t {
      PCLK   = 0b00,
      SYSCLK = 0b01,
      HSI16  = 0b10,
      LSE    = 0b11
    };
  }

  template <std::uint32_t BaseAddress>
  using rcc_ccipr =
    groov::reg<
      "ccipr", std::uint32_t,
      BaseAddress+0x88, groov::w::replace,

      groov::field<"reserved0"   , bool          , 31, 31, access::ro>,
      groov::field<"SWPMI1SEL"   , rccx::swpmi1  , 30, 30>,
      groov::field<"ADCSEL"      , rccx::adcclk  , 29, 28>,
      groov::field<"CLK48SEL"    , rccx::clk48clk, 27, 26>,
      groov::field<"reserved1"   , uint8_t       , 25, 24, access::ro>,
      groov::field<"SAI1SEL"     , rccx::sai1clk , 23, 22>,
      groov::field<"LPTIM2SEL"   , rccx::lptimclk, 21, 20>,
      groov::field<"LPTIM1SEL"   , rccx::lptimclk, 19, 18>,
      groov::field<"I2C3SEL"     , rccx::i2cclk  , 17, 16>,
      groov::field<"I2C2SEL"     , rccx::i2cclk  , 15, 14>,
      groov::field<"I2C1SEL"     , rccx::i2cclk  , 13, 12>,
      groov::field<"LPUART1SEL"  , rccx::usartclk, 11, 10>,
      groov::field<"reserved2"   , uint8_t       ,  9,  8, access::ro>,
      groov::field<"UART4SEL"    , rccx::usartclk,  7,  6>,
      groov::field<"UART3SEL"    , rccx::usartclk,  5,  4>,
      groov::field<"UART2SEL"    , rccx::usartclk,  3,  2>,
      groov::field<"UART1SEL"    , rccx::usartclk,  1,  0>
    >;
}

