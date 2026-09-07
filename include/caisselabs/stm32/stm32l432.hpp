//
// Copyright (c) 2024, 2026 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// STM32 registers for the STM32L432 part family mapped to the part's addresses.
//

#pragma once

// the debug bus can help add break points for store/read operations
//
// Simply pass the object type to the mmio_bus of interest and then set break
// points on free functions `debug_store` and `debug_read` which should not get
// inlined. For example:
//
//  template <stdx::ct_string Name, std::uintptr_t BaseAddress>
//  using usartx_t =
//    groov::group<
//      Name, groov::mmio_bus<debug_mem_iface>,
//
// and now reads and writes to usartx_t types will use the `debug_store` and
// `debug_read` free functions.
//
// #include "debug/debug_mmio_bus.hpp"

#include <caisselabs/stm32/dma.hpp>
#include <caisselabs/stm32/flash.hpp>
#include <caisselabs/stm32/gpio.hpp>
#include <caisselabs/stm32/i2c.hpp>
#include <caisselabs/stm32/rcc.hpp>
#include <caisselabs/stm32/spi.hpp>
#include <caisselabs/stm32/timer.hpp>
#include <caisselabs/stm32/usart.hpp>
#include <caisselabs/stm32/whole_register_bus.hpp>

#include <groov/mmio_bus.hpp>
#include <stdx/ct_string.hpp>

#include <cstdint>

namespace caisselabs::stm32 {
inline namespace l432 {

constexpr std::uintptr_t USART1_BASE = 0x4001'3800;
constexpr std::uintptr_t USART2_BASE = 0x4000'4400;
// clang-format off
  // -------------------------------------------
  // USARTs
  template <stdx::ct_string Name, std::uintptr_t BaseAddress>
  // whole_register_bus: RM0394 39.8 -- "The peripheral registers have to be
  // accessed by words (32 bits)". Same requirement as the DMA, and the same
  // reason: groov's default bus narrows a write to the smallest type that
  // covers the bits being written.
  using usartx_t =
    groov::group<
      Name, whole_register_bus<>,
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
  constexpr std::uintptr_t TIM1_BASE = 0x4001'2c00;
  constexpr std::uintptr_t TIM2_BASE = 0x4000'0000;

  // TIM2 -- general purpose, 32-bit counter and auto-reload
  template <stdx::ct_string Name, std::uintptr_t BaseAddress>
  // whole_register_bus, and OVER-CONSTRAINED on purpose. RM0394 27.4 permits
  // half-word or word access to the TIM2/TIM3 registers -- what it does not
  // permit is a byte access, and groov's subword list includes uint8_t. Since
  // there is no bus here that allows 16 but forbids 8, this takes the
  // stricter of the two. The cost is a legal half-word write becoming a word
  // read-modify-write; the benefit is that a byte access cannot appear from a
  // future change to which fields a write touches.
  using timx_t =
    groov::group<
      Name, whole_register_bus<>,
      timx_cr1<BaseAddress>,
      timx_dier<BaseAddress>,
      timx_sr<BaseAddress>,
      timx_egr<BaseAddress>,
      timx_ccmr1_out<BaseAddress>,
      timx_ccer<BaseAddress>,
      timx_cnt_32<BaseAddress>,
      timx_psc<BaseAddress>,
      timx_arr_32<BaseAddress>,
      timx_ccr1_32<BaseAddress>
    >;

  using tim2_t = timx_t<"tim2", TIM2_BASE>;
  constexpr auto tim2 = tim2_t{};

  // TIM1 -- advanced control. 16-bit counter and auto-reload, plus the
  // repetition counter and the break/dead-time register. Outputs stay
  // disconnected until bdtr.MOE is set.
  template <stdx::ct_string Name, std::uintptr_t BaseAddress>
  // whole_register_bus, over-constrained for the same reason as timx_t above:
  // RM0394 26.4 allows half-word or word access to the TIM1 registers but not
  // byte, and word is the only guarantee available here.
  using timx_adv_t =
    groov::group<
      Name, whole_register_bus<>,
      timx_cr1<BaseAddress>,
      timx_dier_adv<BaseAddress>,
      timx_sr_adv<BaseAddress>,
      timx_egr_adv<BaseAddress>,
      timx_ccmr1_out<BaseAddress>,
      timx_ccer_adv<BaseAddress>,
      timx_cnt_16<BaseAddress>,
      timx_psc<BaseAddress>,
      timx_arr_16<BaseAddress>,
      timx_rcr<BaseAddress>,
      timx_ccr1_16<BaseAddress>,
      timx_bdtr<BaseAddress>
    >;

  using tim1_t = timx_adv_t<"tim1", TIM1_BASE>;
  constexpr auto tim1 = tim1_t{};

  // -------------------------------------------
  // GPIO Port Things
  constexpr std::uintptr_t GPIOA_BASE = 0x4800'0000;
  constexpr std::uintptr_t GPIOB_BASE = 0x4800'0400;

  template <stdx::ct_string Name, std::uintptr_t BaseAddress>
  using gpiox_t =
    groov::group<
      Name, groov::mmio_bus<>,
      gpiox_moder<BaseAddress>,
      gpiox_otyper<BaseAddress>,
      gpiox_ospeedr<BaseAddress>,
      gpiox_pupdr<BaseAddress>,
      gpiox_odr<BaseAddress>,
      gpiox_afrl<BaseAddress>,
      gpiox_afrh<BaseAddress>,
      gpiox_brr<BaseAddress>
    >;

  using gpioa_t = gpiox_t<"gpioa", GPIOA_BASE>;
  constexpr auto gpioa = gpioa_t{};

  using gpiob_t = gpiox_t<"gpiob", GPIOB_BASE>;
  constexpr auto gpiob = gpiob_t{};

  // -------------------------------------------
  // RCC
  constexpr std::uintptr_t RCC_BASE = 0x4002'1000;

  using rcc_t =
    groov::group<
      "rcc", groov::mmio_bus<>,
      rcc_cr<RCC_BASE>,
      rcc_cfgr<RCC_BASE>,
      rcc_pllcfgr<RCC_BASE>,
      rcc_apb1rstr1<RCC_BASE>,
      rcc_apb2rstr<RCC_BASE>,
      rcc_ahb1enr<RCC_BASE>,
      rcc_ahb2enr<RCC_BASE>,
      rcc_apb1enr1<RCC_BASE>,
      rcc_apb2enr<RCC_BASE>,
      rcc_apb2smenr<RCC_BASE>,
      rcc_ccipr<RCC_BASE>
    >;
  constexpr auto rcc = rcc_t{};

  // -------------------------------------------
  // I2C
  constexpr std::uintptr_t I2C1_BASE = 0x4000'5400;
  constexpr std::uintptr_t I2C3_BASE = 0x4000'5c00;

  template <stdx::ct_string Name, std::uintptr_t BaseAddress>
  // whole_register_bus: RM0394 38.9 -- "The registers are accessed by words
  // (32-bit)".
  using i2cx_t =
    groov::group<
      Name, whole_register_bus<>,
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

  using i2c1_t = i2cx_t<"i2c1", I2C1_BASE>;
  constexpr auto i2c1 = i2c1_t{};

  using i2c3_t = i2cx_t<"i2c2", I2C3_BASE>;
  constexpr auto i2c3 = i2c3_t{};

  // -------------------------------------------
  // SPI
  constexpr std::uintptr_t SPI1_BASE = 0x4001'3000;

  // The 8-bit data register is used here: with DS <= 8 a 16-bit write to
  // DR would enqueue two frames. Swap in spi_dr_16 for wider frames.
  template <stdx::ct_string Name, std::uintptr_t BaseAddress>
  // whole_register_bus, over-constrained. RM0394 41.6 allows half-word or word
  // access to the SPI registers and forbids byte access -- with one exception,
  // stated in the same paragraph: "SPI_DR in addition can be accessed by 8-bit
  // access". That exception still holds here, because spi_dr_8 declares itself
  // a std::uint8_t register and this bus accesses a register at its own
  // declared width; an 8-bit DR access is required for DS <= 8, not a
  // violation. Only the surrounding control registers are made stricter.
  using spix_t =
    groov::group<
      Name, whole_register_bus<>,
      spi_cr1<BaseAddress>,
      spi_cr2<BaseAddress>,
      spi_sr<BaseAddress>,
      spi_dr_8<BaseAddress>,
      spi_crcpr<BaseAddress>,
      spi_rxcrcr<BaseAddress>,
      spi_txcrcr<BaseAddress>
    >;

  using spi1_t = spix_t<"spi1", SPI1_BASE>;
  constexpr auto spi1 = spi1_t{};

  // -------------------------------------------
  // DMA
  constexpr std::uintptr_t DMA1_BASE = 0x4002'0000;
  constexpr std::uintptr_t DMA2_BASE = 0x4002'0400;

  template <stdx::ct_string Name, std::uintptr_t BaseAddress>
  using dmax_t =
    groov::group<
      Name, whole_register_bus<>,
      dma_isr<BaseAddress>,
      dma_ifcr<BaseAddress>,
      dma_ccr  <"ccr1"  , BaseAddress, 1>,
      dma_cndtr<"cndtr1", BaseAddress, 1>,
      dma_cpar <"cpar1" , BaseAddress, 1>,
      dma_cmar <"cmar1" , BaseAddress, 1>,
      dma_ccr  <"ccr2"  , BaseAddress, 2>,
      dma_cndtr<"cndtr2", BaseAddress, 2>,
      dma_cpar <"cpar2" , BaseAddress, 2>,
      dma_cmar <"cmar2" , BaseAddress, 2>,
      dma_ccr  <"ccr3"  , BaseAddress, 3>,
      dma_cndtr<"cndtr3", BaseAddress, 3>,
      dma_cpar <"cpar3" , BaseAddress, 3>,
      dma_cmar <"cmar3" , BaseAddress, 3>,
      dma_ccr  <"ccr4"  , BaseAddress, 4>,
      dma_cndtr<"cndtr4", BaseAddress, 4>,
      dma_cpar <"cpar4" , BaseAddress, 4>,
      dma_cmar <"cmar4" , BaseAddress, 4>,
      dma_ccr  <"ccr5"  , BaseAddress, 5>,
      dma_cndtr<"cndtr5", BaseAddress, 5>,
      dma_cpar <"cpar5" , BaseAddress, 5>,
      dma_cmar <"cmar5" , BaseAddress, 5>,
      dma_ccr  <"ccr6"  , BaseAddress, 6>,
      dma_cndtr<"cndtr6", BaseAddress, 6>,
      dma_cpar <"cpar6" , BaseAddress, 6>,
      dma_cmar <"cmar6" , BaseAddress, 6>,
      dma_ccr  <"ccr7"  , BaseAddress, 7>,
      dma_cndtr<"cndtr7", BaseAddress, 7>,
      dma_cpar <"cpar7" , BaseAddress, 7>,
      dma_cmar <"cmar7" , BaseAddress, 7>,
      dma_cselr<BaseAddress>
    >;

  using dma1_t = dmax_t<"dma1", DMA1_BASE>;
  constexpr auto dma1 = dma1_t{};

  using dma2_t = dmax_t<"dma2", DMA2_BASE>;
  constexpr auto dma2 = dma2_t{};

  // -------------------------------------------
  // Embedded Flash interface
  constexpr std::uintptr_t FLASH_BASE = 0x4002'2000;

  using flash_t =
    groov::group<
      "flash", groov::mmio_bus<>,
      flash_acr<FLASH_BASE>
    >;
  constexpr auto flash = flash_t{};
}}

