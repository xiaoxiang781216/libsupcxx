// -*- C++ -*- std::terminate, std::unexpected and friends.
// Copyright (C) 1994-2018 Free Software Foundation, Inc.
//
// This file is part of GCC.
//
// GCC is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// GCC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#include <exception>
#include "unwind-cxx.h"
#include <bits/exception_defines.h>

using namespace __cxxabiv1;

void
__cxxabiv1::__terminate (std::terminate_handler handler) noexcept
{
  __try 
    {
      handler ();
      __builtin_abort ();
    } 
  __catch(...) 
    { __builtin_abort (); }
}

void
std::terminate () noexcept
{
  __terminate (get_terminate ());
}

void
__cxxabiv1::__unexpected (std::unexpected_handler handler)
{
  handler();
  std::terminate ();
}

void
std::unexpected ()
{
  __unexpected (get_unexpected ());
}

std::terminate_handler
std::set_terminate (std::terminate_handler func) noexcept
{
  std::terminate_handler old;
  __terminate_handler = func;
  return old;
}

std::terminate_handler
std::get_terminate () noexcept
{
  return __terminate_handler;
}

std::unexpected_handler
std::set_unexpected (std::unexpected_handler func) noexcept
{
  std::unexpected_handler old;
  __unexpected_handler = func;
  return old;
}

std::unexpected_handler
std::get_unexpected () noexcept
{
  return __unexpected_handler;
}