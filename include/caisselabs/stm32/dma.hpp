//
// Copyright (c) 2026 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// STM32 register descriptions for the DMA controller.
//
// The seven channels are identical blocks of four registers starting at
// 0x08, spaced 0x14 apart. The channel templates below take the register
// name explicitly -- following the gpiox_* pattern -- so a group can spell
// out "ccr6", "cndtr6" and so on as ordinary groov field paths.
//
// clang-format off
#pragma once

#include <caisselabs/stm32/access.hpp>
#include <caisselabs/stm32/enable.hpp>

#include <groov/config.hpp>

#include <stdx/ct_string.hpp>

#include <cstdint>


namespace caisselabs::stm32 {

  using std::uint8_t;
  using std::uint32_t;

  namespace dma {
    // DMA_CCRx.DIR. "Read from memory" is the memory-to-peripheral
    // direction: the source is CMAR/MSIZE/MINC and the destination is
    // CPAR/PSIZE/PINC.
    enum class direction : bool {
      read_from_peripheral = false,
      read_from_memory     = true,
      peripheral_to_memory = false,
      memory_to_peripheral = true
    };

    // DMA_CCRx.MSIZE and .PSIZE. A narrow source feeding a wide
    // destination is zero-extended (RM0394 Table 48), which is what lets a
    // byte array drive a 32-bit compare or data register.
    enum class xfer_size : std::uint8_t {
      bits8  = 0b00,
      bits16 = 0b01,
      bits32 = 0b10
    };

    // DMA_CCRx.PL
    enum class priority : std::uint8_t {
      low       = 0b00,
      medium    = 0b01,
      high      = 0b10,
      very_high = 0b11
    };

    // Channel register blocks are at 0x08 + 0x14 * (x - 1), x = 1 to 7.
    constexpr auto channel_base(std::uint32_t channel) -> std::uintptr_t {
      static_assert(x >= 1 && x <= 7, "invalid dma channel base");
      return 0x08 + 0x14 * (channel - 1);
    }
  }

  // ----------------------------------------------------------------
  // Interrupt status and flag clear
  //
  // Four flags per channel, packed low to high as GIF, TCIF, HTIF, TEIF,
  // starting at bit 4 * (x - 1).
  //
  template <std::uintptr_t BaseAddress>
  using dma_isr =
    groov::reg<
      "isr", std::uint32_t,
      BaseAddress+0x00, access::rw,

      groov::field<"reserved0", uint8_t, 31, 28, access::ro>,
      groov::field<"TEIF7", bool, 27, 27, access::ro>,
      groov::field<"HTIF7", bool, 26, 26, access::ro>,
      groov::field<"TCIF7", bool, 25, 25, access::ro>,
      groov::field<"GIF7" , bool, 24, 24, access::ro>,
      groov::field<"TEIF6", bool, 23, 23, access::ro>,
      groov::field<"HTIF6", bool, 22, 22, access::ro>,
      groov::field<"TCIF6", bool, 21, 21, access::ro>,
      groov::field<"GIF6" , bool, 20, 20, access::ro>,
      groov::field<"TEIF5", bool, 19, 19, access::ro>,
      groov::field<"HTIF5", bool, 18, 18, access::ro>,
      groov::field<"TCIF5", bool, 17, 17, access::ro>,
      groov::field<"GIF5" , bool, 16, 16, access::ro>,
      groov::field<"TEIF4", bool, 15, 15, access::ro>,
      groov::field<"HTIF4", bool, 14, 14, access::ro>,
      groov::field<"TCIF4", bool, 13, 13, access::ro>,
      groov::field<"GIF4" , bool, 12, 12, access::ro>,
      groov::field<"TEIF3", bool, 11, 11, access::ro>,
      groov::field<"HTIF3", bool, 10, 10, access::ro>,
      groov::field<"TCIF3", bool,  9,  9, access::ro>,
      groov::field<"GIF3" , bool,  8,  8, access::ro>,
      groov::field<"TEIF2", bool,  7,  7, access::ro>,
      groov::field<"HTIF2", bool,  6,  6, access::ro>,
      groov::field<"TCIF2", bool,  5,  5, access::ro>,
      groov::field<"GIF2" , bool,  4,  4, access::ro>,
      groov::field<"TEIF1", bool,  3,  3, access::ro>,
      groov::field<"HTIF1", bool,  2,  2, access::ro>,
      groov::field<"TCIF1", bool,  1,  1, access::ro>,
      groov::field<"GIF1" , bool,  0,  0, access::ro>
    >;

  // Write 1 to clear the matching DMA_ISR flag; writing 0 has no effect,
  // so the read-modify-write groov performs is harmless here (the register
  // reads back as zero).
  template <std::uintptr_t BaseAddress>
  using dma_ifcr =
    groov::reg<
      "ifcr", std::uint32_t,
      BaseAddress+0x04, access::rw,

      groov::field<"reserved0", uint8_t, 31, 28, access::ro>,
      groov::field<"CTEIF7", bit_reset, 27, 27>,
      groov::field<"CHTIF7", bit_reset, 26, 26>,
      groov::field<"CTCIF7", bit_reset, 25, 25>,
      groov::field<"CGIF7" , bit_reset, 24, 24>,
      groov::field<"CTEIF6", bit_reset, 23, 23>,
      groov::field<"CHTIF6", bit_reset, 22, 22>,
      groov::field<"CTCIF6", bit_reset, 21, 21>,
      groov::field<"CGIF6" , bit_reset, 20, 20>,
      groov::field<"CTEIF5", bit_reset, 19, 19>,
      groov::field<"CHTIF5", bit_reset, 18, 18>,
      groov::field<"CTCIF5", bit_reset, 17, 17>,
      groov::field<"CGIF5" , bit_reset, 16, 16>,
      groov::field<"CTEIF4", bit_reset, 15, 15>,
      groov::field<"CHTIF4", bit_reset, 14, 14>,
      groov::field<"CTCIF4", bit_reset, 13, 13>,
      groov::field<"CGIF4" , bit_reset, 12, 12>,
      groov::field<"CTEIF3", bit_reset, 11, 11>,
      groov::field<"CHTIF3", bit_reset, 10, 10>,
      groov::field<"CTCIF3", bit_reset,  9,  9>,
      groov::field<"CGIF3" , bit_reset,  8,  8>,
      groov::field<"CTEIF2", bit_reset,  7,  7>,
      groov::field<"CHTIF2", bit_reset,  6,  6>,
      groov::field<"CTCIF2", bit_reset,  5,  5>,
      groov::field<"CGIF2" , bit_reset,  4,  4>,
      groov::field<"CTEIF1", bit_reset,  3,  3>,
      groov::field<"CHTIF1", bit_reset,  2,  2>,
      groov::field<"CTCIF1", bit_reset,  1,  1>,
      groov::field<"CGIF1" , bit_reset,  0,  0>
    >;

  // ----------------------------------------------------------------
  // Per-channel registers
  //
  // MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC and DIR are read-only while
  // EN = 1, so configure the channel before enabling it.
  //
  template <stdx::ct_string Name, std::uintptr_t BaseAddress, std::uint32_t Channel>
  using dma_ccr =
    groov::reg<
      Name, std::uint32_t,
      BaseAddress+dma::channel_base(Channel)+0x00, access::rw,

      groov::field<"reserved0", uint32_t       , 31, 15, access::ro>,
      groov::field<"MEM2MEM"  , bit_enable     , 14, 14>,
      groov::field<"PL"       , dma::priority  , 13, 12>,
      groov::field<"MSIZE"    , dma::xfer_size , 11, 10>,
      groov::field<"PSIZE"    , dma::xfer_size ,  9,  8>,
      groov::field<"MINC"     , bit_enable     ,  7,  7>,
      groov::field<"PINC"     , bit_enable     ,  6,  6>,
      groov::field<"CIRC"     , bit_enable     ,  5,  5>,
      groov::field<"DIR"      , dma::direction ,  4,  4>,
      groov::field<"TEIE"     , bit_enable     ,  3,  3>,
      groov::field<"HTIE"     , bit_enable     ,  2,  2>,
      groov::field<"TCIE"     , bit_enable     ,  1,  1>,
      groov::field<"EN"       , bit_enable     ,  0,  0>
    >;

  template <stdx::ct_string Name, std::uintptr_t BaseAddress, std::uint32_t Channel>
  using dma_cndtr =
    groov::reg<
      Name, std::uint32_t,
      BaseAddress+dma::channel_base(Channel)+0x04, access::rw,

      groov::field<"reserved0", uint32_t, 31, 16, access::ro>,
      groov::field<"NDT", std::uint32_t, 15, 0>
    >;

  template <stdx::ct_string Name, std::uintptr_t BaseAddress, std::uint32_t Channel>
  using dma_cpar =
    groov::reg<
      Name, std::uint32_t,
      BaseAddress+dma::channel_base(Channel)+0x08, access::rw,

      groov::field<"PA", std::uint32_t, 31, 0>
    >;

  template <stdx::ct_string Name, std::uintptr_t BaseAddress, std::uint32_t Channel>
  using dma_cmar =
    groov::reg<
      Name, std::uint32_t,
      BaseAddress+dma::channel_base(Channel)+0x0c, access::rw,

      groov::field<"MA", std::uint32_t, 31, 0>
    >;

  // ----------------------------------------------------------------
  // Channel selection
  //
  // The meaning of each 4-bit code is channel-specific -- 0b0111 selects
  // TIM1_UP on channel 6 but something else entirely on channel 3 -- so
  // these stay plain integers. See RM0394 Table 45 (DMA1) and Table 46
  // (DMA2) for the mapping. Values this project uses:
  //
  //   C3S = 0b0001  SPI1_TX
  //   C6S = 0b0111  TIM1_UP
  //   C7S = 0b0010  USART2_TX
  //
  template <std::uintptr_t BaseAddress>
  using dma_cselr =
    groov::reg<
      "cselr", std::uint32_t,
      BaseAddress+0xa8, access::rw,

      groov::field<"reserved0", uint8_t, 31, 28, access::ro>,
      groov::field<"C7S", std::uint8_t, 27, 24>,
      groov::field<"C6S", std::uint8_t, 23, 20>,
      groov::field<"C5S", std::uint8_t, 19, 16>,
      groov::field<"C4S", std::uint8_t, 15, 12>,
      groov::field<"C3S", std::uint8_t, 11,  8>,
      groov::field<"C2S", std::uint8_t,  7,  4>,
      groov::field<"C1S", std::uint8_t,  3,  0>
    >;
}
