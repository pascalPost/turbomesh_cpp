// Copyright (c) Pascal Post. All Rights Reserved.
// Licensed under AGPLv3 license (see LICENSE.txt for details)

#pragma once

#include <stdexcept>
#include <string>

namespace turbomesh
{

/// convenient error throwing function
inline void
error(const std::string& msg)
{
  throw std::runtime_error(msg);
}

} // namespace turbomesh