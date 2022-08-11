// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#pragma once

namespace turbomesh
{

/// @brief helper type for std::visit, see
/// https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts>
struct overloaded : Ts...
{
  using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded( Ts... ) -> overloaded<Ts...>;

} // namespace turbomesh