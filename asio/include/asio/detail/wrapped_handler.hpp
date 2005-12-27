//
// wrapped_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2005 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_WRAPPED_HANDLER_HPP
#define ASIO_DETAIL_WRAPPED_HANDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/push_options.hpp"

#include "asio/handler_alloc_hook.hpp"
#include "asio/detail/bind_handler.hpp"

namespace asio {
namespace detail {

template <typename Dispatcher, typename Handler>
class wrapped_handler;

} // namespace detail
} // namespace asio

namespace asio {

template <typename Dispatcher, typename Handler>
class handler_alloc_hook<
  asio::detail::wrapped_handler<Dispatcher, Handler> >;

} // namespace asio

namespace asio {
namespace detail {

template <typename Dispatcher, typename Handler>
class wrapped_handler
{
public:
  typedef void result_type;

  wrapped_handler(Dispatcher& dispatcher, Handler handler)
    : dispatcher_(dispatcher),
      handler_(handler)
  {
  }

  void operator()()
  {
    dispatcher_.dispatch(handler_);
  }

  void operator()() const
  {
    dispatcher_.dispatch(handler_);
  }

  template <typename Arg1>
  void operator()(Arg1 arg1)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1));
  }

  template <typename Arg1>
  void operator()(Arg1 arg1) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1));
  }

  template <typename Arg1, typename Arg2>
  void operator()(Arg1 arg1, Arg2 arg2)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2));
  }

  template <typename Arg1, typename Arg2>
  void operator()(Arg1 arg1, Arg2 arg2) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2));
  }

  template <typename Arg1, typename Arg2, typename Arg3>
  void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2, arg3));
  }

  template <typename Arg1, typename Arg2, typename Arg3>
  void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2, arg3));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
  void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
  void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) const
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4,
      typename Arg5>
  void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4, arg5));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4,
      typename Arg5>
  void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5) const
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4, arg5));
  }

private:
  Dispatcher& dispatcher_;
  Handler handler_;
  friend class asio::handler_alloc_hook<
    wrapped_handler<Dispatcher, Handler> >;
};

} // namespace detail
} // namespace asio

template <typename Dispatcher, typename Handler>
class asio::handler_alloc_hook<
  asio::detail::wrapped_handler<Dispatcher, Handler> >
{
public:
  typedef asio::detail::wrapped_handler<Dispatcher, Handler> handler_type;

  template <typename Allocator>
  static typename Allocator::pointer allocate(handler_type& handler,
      Allocator& allocator, typename Allocator::size_type count)
  {
    return asio::handler_alloc_hook<Handler>::allocate(
        handler.handler_, allocator, count);
  }

  template <typename Allocator>
  static void deallocate(handler_type& handler, Allocator& allocator,
      typename Allocator::pointer pointer, typename Allocator::size_type count)
  {
    return asio::handler_alloc_hook<Handler>::deallocate(
        handler.handler_, allocator, pointer, count);
  }
};

#include "asio/detail/pop_options.hpp"

#endif // ASIO_DETAIL_WRAPPED_HANDLER_HPP
