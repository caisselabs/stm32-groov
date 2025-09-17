//
// Copyright (c) 2025 Michael Caisse
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 //
//
#pragma once

#include <groov/identity.hpp>

namespace caisselabs::stm32::access {
  using rw = groov::w::replace;
  using ro = groov::read_only<groov::w::ignore>;
}

