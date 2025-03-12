/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#ifdef _MSC_VER
#pragma warning( disable : 4100 )                                  //"unreferenced formal parameter"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif // !_MSC_VER

#include <boost/asio.hpp>                                          //for boost asio communication
#include <boost/asio/deadline_timer.hpp>
#include <boost/circular_buffer.hpp>                               //for boost circular buffer
#include <boost/date_time.hpp>                                     //for boost::posix_time::from_time_t
#include <boost/date_time/posix_time/posix_time_duration.hpp>      //for boost::posix_time::nanosec
#include <boost/date_time/posix_time/ptime.hpp>                    //for boost ptime
#include <boost/detail/endian.hpp>                                 //for endianess
#include <boost/lambda/lambda.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>                       //for boost::numeric_cast
#include <boost/optional.hpp>                                      //for boost::optional
#include <boost/utility/binary.hpp>                                //for BOOST_BINARY

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4245)  //initializing conversion from int to boost::detail::mask_uint_t<8>::least, signed/unsigned mismatch
#pragma warning(disable: 4244)  //return conversion from unsigned int to unsigned char
#endif // !_MSC_VER
#include <boost/crc.hpp>
#ifdef _MSC_VER
#pragma warning(pop)
#endif // !_MSC_VER

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
