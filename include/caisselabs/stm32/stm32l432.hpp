//
// Copyright (c) 2024 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// STM32 registers for the STM32L432 part family mapped to the part's addresses.
//

#pragma once

// the debug bus can help add break points for store/read operations
//
// Simply pass the object type to the mmio_bus of interest and then set break points
// on free functions `debug_store` and `debug_read` which should not get inlined.
// For example:
//
//  template <stdx::ct_string Name, std::uint32_t BaseAddress>
//  using usartx_t =
//    groov::group<
//      Name, groov::mmio_bus<debug_mem_iface>,
//
// and now reads and writes to usartx_t types will use the `debug_store` and
// `debug_read` free functions.
//
// #include "debug/debug_mmio_bus.hpp"

#include <caisselabs/stm32/usart.hpp>
#include <caisselabs/stm32/timer.hpp>
#include <caisselabs/stm32/i2c.hpp>
#include <caisselabs/stm32/gpio.hpp>
#include <caisselabs/stm32/rcc.hpp>

#include <stdx/ct_string.hpp>
#include <groov/mmio_bus.hpp>

#include <cstdint>

namespace caisslabs::stm32 {
inline namespace l432 {

  constexpr std::uint32_t USART1_BASE = 0x4001'3800;
  constexpr std::uint32_t USART2_BASE = 0x4000'4400;

  // -------------------------------------------
  // USARTs
  template <stdx::ct_string Name, std::uint32_t BaseAddress>
  using usartx_t =
    groov::group<
      Name, groov::mmio_bus<>,
      usart_cr1<BaseAddress>,
      usart_cr2<BaseAddress>,
      usart_cr3<BaseAddress>,
      usart_brr<BaseAddress>,
      usart_gtpr<BaseAddress>,
      usart_rtor<BaseAddress>,
      usart_rqr<BaseAddress>,
      usart_isr<BaseAddress>,
      usart_icr<BaseAddress>,
      usart_rdr<BaseAddress>,
      usart_tdr<BaseAddress>
    >;

  using usart1_t = usartx_t<"usart1", USART1_BASE>;
  constexpr auto usart1 = usart1_t{};

  using usart2_t = usartx_t<"usart2", USART2_BASE>;
  constexpr auto usart2 = usart2_t{};

  // -------------------------------------------
  // Timers
  constexpr std::uint32_t TIM2_BASE = 0x4000'0000;

  // TIM2
  template <stdx::ct_string Name, std::uint32_t BaseAddress>
  using timx_t =
    groov::group<
      Name, groov::mmio_bus<>,
      timx_cr1<BaseAddress>,
      timx_dier<BaseAddress>,
      timx_sr<BaseAddress>,
      timx_ccmr1_out<BaseAddress>,
      timx_ccer<BaseAddress>,
      timx_cnt_32<BaseAddress>,
      timx_ccr1_32<BaseAddress>
    >;

  using tim2_t = timx_t<"tim2", TIM2_BASE>;
  constexpr auto tim2 = tim2_t{};

  // -------------------------------------------
  // GPIO Port Things
  constexpr std::uint32_t GPIOA_BASE = 0x4800'0000;
  constexpr std::uint32_t GPIOB_BASE = 0x4800'0400;

  template <stdx::ct_string Name, std::uint32_t BaseAddress>
  using gpiox_t =
    groov::group<
      Name, groov::mmio_bus<>,
      gpiox_moder<BaseAddress>,
      gpiox_otyper<BaseAddress>,
      gpiox_ospeedr<BaseAddress>,
      gpiox_pupdr<BaseAddress>,
      gpiox_odr<BaseAddress>,
      gpiox_afrl<BaseAddress>,
      gpiox_afrh<BaseAddress>
    >;

  using gpioa_t = gpiox_t<"gpioa", GPIOA_BASE>;
  constexpr auto gpioa = gpioa_t{};

  using gpiob_t = gpiox_t<"gpiob", GPIOB_BASE>;
  constexpr auto gpiob = gpiob_t{};

  // -------------------------------------------
  // RCC
  constexpr std::uint32_t RCC_BASE = 0x4002'1000;

  using rcc_t =
    groov::group<
      "rcc", groov::mmio_bus<>,
      rcc_cr<RCC_BASE>,
      rcc_cfgr<RCC_BASE>,
      rcc_apb2rstr<RCC_BASE>,
      rcc_ahb2enr<RCC_BASE>,
      rcc_apb1enr1<RCC_BASE>,
      rcc_apb2enr<RCC_BASE>,
      rcc_apb2smenr<RCC_BASE>,
      rcc_ccipr<RCC_BASE>
    >;
  constexpr auto rcc = rcc_t{};

  // -------------------------------------------
  // I2C
  constexpr std::uint32_t I2C1_BASE = 0x4000'5400;
  constexpr std::uint32_t I2C3_BASE = 0x4000'5c00;

  template <std::uint32_t BaseAddress>
  using i2cx_t =
    groov::group<
      "i2c1", groov::mmio_bus<>,
      i2c_cr1<BaseAddress>,
      i2c_cr2<BaseAddress>,
      i2c_oar1<BaseAddress>,
      i2c_oar2<BaseAddress>,
      i2c_timingr<BaseAddress>,
      i2c_timeoutr<BaseAddress>,
      i2c_isr<BaseAddress>,
      i2c_icr<BaseAddress>,
      i2c_pecr<BaseAddress>,
      i2c_rxdr<BaseAddress>,
      i2c_txdr<BaseAddress>
    >;

  using i2c1_t = i2cx_t<I2C1_BASE>;
  constexpr auto i2c1 = i2c1_t{};

  using i2c3_t = i2cx_t<I2C3_BASE>;
  constexpr auto i2c3 = i2c3_t{};
}}

