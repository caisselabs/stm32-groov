//
// Copyright (c) 2025 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Data types for enable/disable and the bar versions.
//
#pragma once

namespace caisselabs::stm32 {

// clang-format off
  enum class bit_enable : bool {
    ENABLE  = true,
    DISABLE = false,
    ON      = true,
    OFF     = false,
    zero    = false,
    one     = true
  };

  enum class bit_enable_bar : bool {
    ENABLE  = false,
    DISABLE = true,
    ON      = false,
    OFF     = true,
    zero    = false,
    one     = true
  };

  template <typename T>
  auto is_enabled(T v) -> bool {
    return v == T::ENABLED;
  }

  enum class bit_ready : bool {
    READY     = true,
    NOT_READY = false,
    zero      = false,
    one       = true
  };

  enum class bit_ready_bar : bool {
    READY     = false,
    NOT_READY = true,
    zero      = false,
    one       = true
  };

  // TODO: ICE on gcc. Talk to Ben.
  // template <typename T>
  // auto is_ready(T v) -> bool {
  //   return v == T::READY;
  // }

  inline auto is_ready(bit_ready v) -> bool {
    return v == bit_ready::READY;
  }

  inline auto is_ready(bit_ready_bar v) -> bool {
    return v == bit_ready_bar::READY;
  }

  enum class bit_locked : bool {
    LOCKED    = true,
    UNLOCKED  = false,
    zero      = false,
    one       = true
  };

  enum class bit_locked_bar : bool {
    LOCKED    = false,
    UNLOCKED  = true,
    zero      = false,
    one       = true
  };

  template <typename T>
  auto is_locked(T v) -> bool {
    return v == T::READY;
  }

  enum class bit_reset : bool {
    do_nothing = false,
    RESET      = true,
    SET        = true,
    zero       = false,
    one        = true
  };
}

