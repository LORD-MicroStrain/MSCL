/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/
#pragma once

// MSVC
#if defined _MSC_VER
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define DISABLE_WARNING_PUSH           __pragma(warning(push))
#define DISABLE_WARNING_POP            __pragma(warning(pop))
#define DISABLE_WARNING(warningNumber) __pragma(warning(disable : warningNumber))

#define DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER       DISABLE_WARNING(4100)
#define DISABLE_WARNING_VARIABLE_INITIALIZE_NOT_REFERENCED  DISABLE_WARNING(4189)
#define DISABLE_WARNING_GLOBAL_DECLARATION_HIDDEN           DISABLE_WARNING(4459)
#define DISABLE_WARNING_DECORATED_NAME_EXCEEDED             DISABLE_WARNING(4503)
#define DISABLE_WARNING_UNINITIALIZED_LOCAL_VARIABLE        DISABLE_WARNING(4701)
#define DISABLE_WARNING_FORCE_VALUE_TO_BOOL                 DISABLE_WARNING(4800)

// GCC and Clang
#elif defined __GNUC__ || defined __clang__
#define DO_PRAGMA(X) _Pragma(#X)
#define DISABLE_WARNING_PUSH           DO_PRAGMA(GCC diagnostic push)
#define DISABLE_WARNING_POP            DO_PRAGMA(GCC diagnostic pop)
#define DISABLE_WARNING(warningName)   DO_PRAGMA(GCC diagnostic ignored #warningName)

#define DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER       DISABLE_WARNING(-Wunused-parameter)
#define DISABLE_WARNING_VARIABLE_INITIALIZE_NOT_REFERENCED
#define DISABLE_WARNING_GLOBAL_DECLARATION_HIDDEN
#define DISABLE_WARNING_DECORATED_NAME_EXCEEDED
#define DISABLE_WARNING_UNINITIALIZED_LOCAL_VARIABLE
#define DISABLE_WARNING_FORCE_VALUE_TO_BOOL
#else
#define DISABLE_WARNING_PUSH
#define DISABLE_WARNING_POP

#define DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER
#define DISABLE_WARNING_VARIABLE_INITIALIZE_NOT_REFERENCED
#define DISABLE_WARNING_GLOBAL_DECLARATION_HIDDEN
#define DISABLE_WARNING_DECORATED_NAME_EXCEEDED
#define DISABLE_WARNING_UNINITIALIZED_LOCAL_VARIABLE
#define DISABLE_WARNING_FORCE_VALUE_TO_BOOL
#endif // _MSC_VER

// Disable all Boost warnings
#define DISABLE_WARNING_BOOST_START                     \
    DISABLE_WARNING_PUSH                                \
    DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER       \
    DISABLE_WARNING_VARIABLE_INITIALIZE_NOT_REFERENCED  \
    DISABLE_WARNING_GLOBAL_DECLARATION_HIDDEN           \
    DISABLE_WARNING_DECORATED_NAME_EXCEEDED             \
    DISABLE_WARNING_UNINITIALIZED_LOCAL_VARIABLE        \
    DISABLE_WARNING_FORCE_VALUE_TO_BOOL

#define DISABLE_WARNING_BOOST_END \
    DISABLE_WARNING_POP

//TODO: Look into fixing typedefs to only use this for Boost
DISABLE_WARNING_DECORATED_NAME_EXCEEDED

DISABLE_WARNING_BOOST_START
#include <boost/asio.hpp>                                          //for boost asio communication
#include <boost/asio/deadline_timer.hpp>
#include <boost/circular_buffer.hpp>                               //for boost circular buffer
#include <boost/crc.hpp>
#include <boost/date_time.hpp>                                     //for boost::posix_time::from_time_t
#include <boost/date_time/posix_time/posix_time_duration.hpp>      //for boost::posix_time::nanosec
#include <boost/date_time/posix_time/ptime.hpp>                    //for boost ptime
#if BOOST_VERSION < 106900
#include <boost/detail/endian.hpp>                                 //for endianess
#else // BOOST_VERSION >= 106900
#include <boost/predef/other/endian.h>                             //for endianess
#endif // BOOST_VERSION < 106900
#include <boost/lambda/lambda.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>                       //for boost::numeric_cast
#include <boost/optional.hpp>                                      //for boost::optional
#include <boost/utility/binary.hpp>                                //for BOOST_BINARY

#ifndef _WIN32
#include <boost/filesystem.hpp>
#endif // !_WIN32

#ifndef MSCL_DISABLE_SSL
#include <boost/asio/ssl.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/websocket/ssl.hpp>
#endif // !MSCL_DISABLE_SSL

#ifndef MSCL_DISABLE_WEBSOCKETS
#include <boost/beast.hpp>
#endif // !MSCL_DISABLE_WEBSOCKETS
DISABLE_WARNING_BOOST_END

#include <algorithm>                                               //for std::min, std::replace
#include <array>                                                   //for std::array
#include <bitset>                                                  //for std::bitset
#include <cassert>
#include <chrono>                                                  //for std::chrono::duration
#include <cmath>
#include <condition_variable>                                      //for std::condition_variable
#include <cstdint>                                                 //for std::uint16_t and like fixed-width types
#include <ctime>
#include <exception>                                               //for std::exception
#include <fstream>
#include <functional>                                              //for std::function
#include <iomanip>                                                 //for std::setprecision
#include <map>                                                     //for std::map
#include <memory>                                                  //for std::shared_ptr, std::unique_ptr
#include <mutex>                                                   //for std::mutex
#include <numeric>                                                 //for std::accumulate
#include <regex>
#include <set>                                                     //for std::set
#include <sstream>                                                 //for std::stringstream
#include <string>                                                  //for std::string
#include <thread>                                                   //for gmtime_r and gmtime_s
#include <tuple>                                                   //for std:tuple, std::get
#include <typeinfo>
#include <unordered_map>                                           //for std::unordered_map
#include <vector>                                                  //for std::vector

//common MSCL files that will rarely change
#include "mscl/Types.h"

#include "mscl/Communication/BoostCommunication.h"
#include "mscl/Communication/Connection.h"
#include "mscl/Communication/OperatingSystemErrorCodes.h"
#include "mscl/Exceptions.h"
#include "mscl/TimedCondition.h"
#include "mscl/TimeSpan.h"
#include "mscl/Timestamp.h"
#include "mscl/Version.h"
