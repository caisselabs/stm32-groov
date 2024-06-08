//
// Copyright (c) 2024 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// STM32 register descriptions for the RCC : Reset Clock Control
//
#pragma once

#include <groov/config.hpp>

#include <cstdint>


namespace caisslabs::stm32 {

  template <std::uint32_t BaseAddress>
  using rcc_cr =
    groov::reg<
      "cr", std::uint32_t,
      BaseAddress+0x00, groov::w::replace,

      groov::field<"PLLSAI1RDY", bool        , 27, 27, groov::w::read_only>,
      groov::field<"PLLSAI1ON" , bool        , 26, 26>,
      groov::field<"PLLRDY"    , bool        , 25, 25, groov::w::read_only>,
      groov::field<"PLLON"     , bool        , 24, 24>,
      groov::field<"CSSON"     , bool        , 19, 19>,
      groov::field<"HSEBYP"    , bool        , 18, 18>,
      groov::field<"HSERDY"    , bool        , 17, 17, groov::w::read_only>,
      groov::field<"HSEON"     , bool        , 16, 16>,
      groov::field<"HSIASFS"   , bool        , 11, 11>,
      groov::field<"HSIASFS"   , bool        , 11, 11>,
      groov::field<"HSIRDY"    , bool        , 10, 10, groov::w::read_only>,
      groov::field<"HSIKERON"  , bool        ,  9,  9>,
      groov::field<"HSION"     , bool        ,  8,  8>,
      groov::field<"MSIRANGE"  , std::uint8_t,  7,  4>,
      groov::field<"MSIRGSEL"  , bool        ,  3,  3>,
      groov::field<"MSIPLLEN"  , bool        ,  2,  2>,
      groov::field<"MSIRDY"    , bool        ,  1,  1, groov::w::read_only>,
      groov::field<"MSION"     , bool        ,  0,  0>
    >;


  namespace rccx {
    enum class sw_t : std::uint8_t {
      msi   = 0b00,
      hsi16 = 0b01,
      hse   = 0b10,
      pll   = 0b11
    };
  }

  template <std::uint32_t BaseAddress>
  using rcc_cfgr =
    groov::reg<
      "cfgr", std::uint32_t,
      BaseAddress+0x08, groov::w::replace,

      groov::field<"MCOPRE"  , std::uint8_t, 30, 28>,
      groov::field<"MCOSEL"  , std::uint8_t, 27, 24>,
      groov::field<"STOPWUCK"  , bool, 15, 15>,
      groov::field<"PPRE2"  , std::uint8_t, 13, 11>,
      groov::field<"PPRE1"  , std::uint8_t, 10,  8>,
      groov::field<"HPRE"  , std::uint8_t, 7,  4>,
      groov::field<"SWS"  , std::uint8_t, 3,  2>,
      groov::field<"SW"  , rccx::sw_t, 1,  0>
    >;
  
  template <std::uint32_t BaseAddress>
  using rcc_apb2rstr =
    groov::reg<
      "apb2rstr", std::uint32_t,
      BaseAddress+0x40, groov::w::replace,

      groov::field<"DFSDM1RST"  , bool, 24, 24>,
      groov::field<"SAI1RST"    , bool, 21, 21>,
      groov::field<"TIM16RST"   , bool, 17, 17>,
      groov::field<"TIM15RST"   , bool, 16, 16>,
      groov::field<"USART1RST"  , bool, 14, 14>,
      groov::field<"SPI1RST"    , bool, 12, 12>,
      groov::field<"TIM1RST"    , bool, 11, 11>,
      groov::field<"SDMMC1RST"  , bool, 10, 10>,
      groov::field<"SYSCFGRST"  , bool,  0,  0>
    >;
  
  template <std::uint32_t BaseAddress>
  using rcc_ahb2enr =
    groov::reg<
      "ahb2enr", std::uint32_t,
      BaseAddress+0x4c, groov::w::replace,

      groov::field<"RNGEN"  , bool, 18, 18>,
      groov::field<"AESEN"  , bool, 16, 16>,
      groov::field<"ADCEN"  , bool, 13, 13>,
      groov::field<"GPIOHEN"  , bool, 7, 7>,
      groov::field<"GPIOEEN"  , bool, 4, 4>,
      groov::field<"GPIODEN"  , bool, 3, 3>,
      groov::field<"GPIOCEN"  , bool, 2, 2>,
      groov::field<"GPIOBEN"  , bool, 1, 1>,
      groov::field<"GPIOAEN"  , bool, 0, 0>
    >;


  template <std::uint32_t BaseAddress>
  using rcc_apb1enr1 =
    groov::reg<
      "apb1enr1", std::uint32_t,
      BaseAddress+0x58, groov::w::replace,

      groov::field<"LPTIM1EN"  , bool, 31, 31>,
      groov::field<"OPAMPEN"  , bool, 30, 30>,
      groov::field<"DAC1EN"  , bool, 29, 29>,
      groov::field<"PWREN"  , bool, 28, 28>,
      groov::field<"USBFSEN"  , bool, 26, 26>,
      groov::field<"CAN1EN"  , bool, 25, 25>,
      groov::field<"CRSEN"  , bool, 24, 24>,
      groov::field<"I2C3EN"  , bool, 23, 23>,
      groov::field<"I2C2EN"  , bool, 22, 22>,
      groov::field<"I2C1EN"  , bool, 21, 21>,
      groov::field<"UART4EN"  , bool, 19, 19>,
      groov::field<"USART3EN"  , bool, 18, 18>,
      groov::field<"USART2EN"  , bool, 17, 17>,
      groov::field<"SP3EN"  , bool, 15, 15>,
      groov::field<"SPI2EN"  , bool, 14, 14>,
      groov::field<"WWDGEN"  , bool, 11, 11>,
      groov::field<"RTCAPBEN"  , bool, 10, 10>,
      groov::field<"LCDEN"  , bool, 9, 9>,
      groov::field<"TIM7EN"  , bool, 5, 5>,
      groov::field<"TIM6EN"  , bool, 4, 4>,
      groov::field<"TIM3EN"  , bool, 1, 1>,
      groov::field<"TIM2EN"  , bool, 0, 0>
    >;

  template <std::uint32_t BaseAddress>
  using rcc_apb2enr =
    groov::reg<
      "apb2enr", std::uint32_t,
      BaseAddress+0x60, groov::w::replace,

      groov::field<"DFSDM1EN"  , bool, 24, 24>,
      groov::field<"SAI1EN"    , bool, 21, 21>,
      groov::field<"TIM16EN"   , bool, 17, 17>,
      groov::field<"TIM15EN"   , bool, 16, 16>,
      groov::field<"USART1EN"  , bool, 14, 14>,
      groov::field<"SPI1EN"    , bool, 12, 12>,
      groov::field<"TIM1EN"    , bool, 11, 11>,
      groov::field<"SDMMC1EN"  , bool, 10, 10>,
      groov::field<"FWEN"      , bool,  7,  7>,
      groov::field<"SYSCFGEN"  , bool,  0,  0>
    >;

  template <std::uint32_t BaseAddress>
  using rcc_apb2smenr =
    groov::reg<
      "apb2smenr", std::uint32_t,
      BaseAddress+0x80, groov::w::replace,

      groov::field<"SAI1SMEN"    , bool, 21, 21>,
      groov::field<"TIM16SMEN"   , bool, 17, 17>,
      groov::field<"TIM15SMEN"   , bool, 16, 16>,
      groov::field<"USART1SMEN"  , bool, 14, 14>,
      groov::field<"SPI1SMEN"    , bool, 12, 12>,
      groov::field<"TIM1SMEN"    , bool, 11, 11>,
      groov::field<"SDMMC1SMEN"  , bool, 10, 10>,
      groov::field<"SYSCFGSMEN"  , bool,  0,  0>
    >;

  namespace rccx {
    enum class usartclk_t : std::uint8_t {
      pclk   = 0b00,
      sysclk = 0b01,
      hsi16  = 0b10,
      lse    = 0b11
    };
  }
  
  template <std::uint32_t BaseAddress>
  using rcc_ccipr =
    groov::reg<
      "ccipr", std::uint32_t,
      BaseAddress+0x88, groov::w::replace,

      groov::field<"SWPMI1SEL"    , bool, 30, 30>,
      groov::field<"ADCSEL"      , bool, 29, 28>,
      groov::field<"CLK48SEL"      , bool, 27, 26>,
      groov::field<"SAI1SEL"      , bool, 23, 22>,
      groov::field<"LPTIM2SEL"      , bool, 21, 20>,
      groov::field<"LPTIM1SEL"      , bool, 19, 18>,
      groov::field<"I2C3SEL"      , bool, 17, 16>,
      groov::field<"I2C2SEL"      , bool, 15, 14>,
      groov::field<"I2C1SEL"      , bool, 13, 12>,
      groov::field<"LPUART1SEL"      , bool, 11, 10>,
      groov::field<"UART4SEL"      , rccx::usartclk_t, 7, 6>,
      groov::field<"UART3SEL"      , rccx::usartclk_t, 5, 4>,
      groov::field<"UART2SEL"      , rccx::usartclk_t, 3, 2>,
      groov::field<"UART1SEL"      , rccx::usartclk_t, 1, 0>
    >;
}
