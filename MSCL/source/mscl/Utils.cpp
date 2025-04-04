/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Utils.h"

#include "mscl/Endianness.h"
#include "mscl/HighResClock.h"

namespace mscl
{
#ifndef SWIG
    namespace Utils
    {
        uint32 valueTypeSize(ValueType type)
        {
            switch (type)
            {
            case valueType_double:
            case valueType_uint64:
                return 8;

            case valueType_float:
            case valueType_int32:
            case valueType_uint32:
                return 4;

            case valueType_int16:
            case valueType_uint16:
                return 2;

            case valueType_uint8:
            case valueType_int8:
            case valueType_bool:
                return 1;

            default:
                throw Error("Requested ValueType does not have a given size");
            }
        }

        uint8 msb(uint16 value)
        {
            return value >> 8;
        }

        uint8 lsb(uint16 value)
        {
            return value & 0x00ff;
        }

        //gets the Most Significant Nibble
        uint8 msNibble(uint8 value)
        {
            return value >> 4;
        }

        //gets the Least Significant Nibble
        uint8 lsNibble(uint8 value)
        {
            return value & 0x0f;
        }

        void split_int16(int16 value, uint8& low, uint8& high, Endianness endian /*= bigEndian*/)
        {
            int16 val;

            if (endian == bigEndian)
            {
                val = SystemEndian_To_BigEndian(value);
            }
            else
            {
                val = SystemEndian_To_LittleEndian(value);
            }

            //map the int16 to a byte array
            uint8* tmp = reinterpret_cast<uint8*>(&val);

            //get each byte of the int16
            low = tmp[0];
            high = tmp[1];
        }

        int16 make_int16(uint8 low, uint8 high, Endianness endian /*= bigEndian*/)
        {
            int16 result = 0;

            //map the int16 to a byte array
            uint8* temp = reinterpret_cast<uint8*>(&result);

            //set each byte of the int16 via the byte array (in big endian)
            temp[0] = low;
            temp[1] = high;

            if (endian == bigEndian)
            {
                return BigEndian_To_SystemEndian(result);
            }

            return LittleEndian_To_SystemEndian(result);
        }

        int32 make_int32(uint8 low, uint8 byte2, uint8 byte3, uint8 high, Endianness endian /*= bigEndian*/)
        {
            int32 result = 0;

            //map the int32 to a byte array
            uint8* temp = reinterpret_cast<uint8*>(&result);

            //set each byte of the uint16 via the byte array (in big endian)
            temp[0] = low;
            temp[1] = byte2;
            temp[2] = byte3;
            temp[3] = high;

            if (endian == bigEndian)
            {
                return BigEndian_To_SystemEndian(result);
            }

            return LittleEndian_To_SystemEndian(result);
        }

        void split_uint16(uint16 value, uint8& low, uint8& high, Endianness endian /*= bigEndian*/)
        {
            uint16 val;

            if (endian == bigEndian)
            {
                val = SystemEndian_To_BigEndian(value);
            }
            else
            {
                val = SystemEndian_To_LittleEndian(value);
            }

            //map the uint16 to a byte array
            uint8* tmp = reinterpret_cast<uint8*>(&val);

            //get each byte of the uint16
            low = tmp[0];
            high = tmp[1];
        }

        uint16 make_uint16(uint8 low, uint8 high, Endianness endian /*= bigEndian*/)
        {
            uint16 result = 0;

            //map the float to a byte array
            uint8* temp = reinterpret_cast<uint8*>(&result);

            //set each byte of the uint16 via the byte array (in big endian)
            temp[0] = low;
            temp[1] = high;

            if (endian == bigEndian)
            {
                return BigEndian_To_SystemEndian(result);
            }

            return LittleEndian_To_SystemEndian(result);
        }

        void split_uint32(uint32 value, uint8& low, uint8& byte2, uint8& byte3, uint8& high, Endianness endian /*= bigEndian*/)
        {
            uint32 val;

            if (endian == bigEndian)
            {
                val = SystemEndian_To_BigEndian(value);
            }
            else
            {
                val = SystemEndian_To_LittleEndian(value);
            }

            //map the uint32 to a byte array
            uint8* tmp = reinterpret_cast<uint8*>(&val);

            //get each byte of the uint16
            low = tmp[0];
            byte2 = tmp[1];
            byte3 = tmp[2];
            high = tmp[3];
        }

        void split_uint64(uint64 value, uint8& low, uint8& byte2, uint8& byte3, uint8& byte4, uint8& byte5, uint8& byte6, uint8& byte7, uint8& high, Endianness endian /*= bigEndian*/)
        {
            uint64 val;

            if (endian == bigEndian)
            {
                val = SystemEndian_To_BigEndian(value);
            }
            else
            {
                val = SystemEndian_To_LittleEndian(value);
            }

            //map the uint64 to a byte array
            uint8* tmp = reinterpret_cast<uint8*>(&val);

            //get each byte of the uint16
            low = tmp[0];
            byte2 = tmp[1];
            byte3 = tmp[2];
            byte4 = tmp[3];
            byte5 = tmp[4];
            byte6 = tmp[5];
            byte7 = tmp[6];
            high = tmp[7];
        }

        uint32 make_uint32(uint8 low, uint8 byte2, uint8 byte3, uint8 high, Endianness endian /*= bigEndian*/)
        {
            uint32 result = 0;

            //map the float to a byte array
            uint8* temp = reinterpret_cast<uint8*>(&result);

            //set each byte of the uint16 via the byte array (in big endian)
            temp[0] = low;
            temp[1] = byte2;
            temp[2] = byte3;
            temp[3] = high;

            if (endian == bigEndian)
            {
                return BigEndian_To_SystemEndian(result);
            }

            return LittleEndian_To_SystemEndian(result);
        }

        uint64 make_uint64(uint8 low, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7, uint8 high, Endianness endian /*= bigEndian*/)
        {
            uint64 result = 0;

            //map the float to a byte array
            uint8* temp = reinterpret_cast<uint8*>(&result);

            //set each byte of the uint16 via the byte array (in big endian)
            temp[0] = low;
            temp[1] = byte2;
            temp[2] = byte3;
            temp[3] = byte4;
            temp[4] = byte5;
            temp[5] = byte6;
            temp[6] = byte7;
            temp[7] = high;

            if (endian == bigEndian)
            {
                return BigEndian_To_SystemEndian(result);
            }

            return LittleEndian_To_SystemEndian(result);
        }

        void split_float(float value, uint8& low, uint8& byte2, uint8& byte3, uint8& high, Endianness endian /*= bigEndian*/)
        {
            float val;

            if (endian == bigEndian)
            {
                val = SystemEndian_To_BigEndian(value);
            }
            else
            {
                val = SystemEndian_To_LittleEndian(value);
            }

            //map the float to a byte array
            uint8* tmp = reinterpret_cast<uint8*>(&val);

            //get each byte of the float
            low = tmp[0];
            byte2 = tmp[1];
            byte3 = tmp[2];
            high = tmp[3];
        }

        float make_float(uint8 low, uint8 byte2, uint8 byte3, uint8 high, Endianness endian /*= bigEndian*/)
        {
            float result = 0;

            //map the float to a byte array
            uint8* temp = reinterpret_cast<uint8*>(&result);

            //set each byte of the float via the byte array (in big endian)
            temp[0] = low;
            temp[1] = byte2;
            temp[2] = byte3;
            temp[3] = high;

            if (endian == bigEndian)
            {
                return BigEndian_To_SystemEndian(result);
            }

            return LittleEndian_To_SystemEndian(result);
        }

        void split_double(double value, uint8& low, uint8& byte2, uint8& byte3, uint8& byte4, uint8& byte5, uint8& byte6, uint8& byte7, uint8& high, Endianness endian /*= bigEndian*/)
        {
            double val;

            if (endian == bigEndian)
            {
                val = SystemEndian_To_BigEndian(value);
            }
            else
            {
                val = SystemEndian_To_LittleEndian(value);
            }

            //map the double to a byte array
            uint8* tmp = reinterpret_cast<uint8*>(&val);

            //get each byte of the double
            low = tmp[0];
            byte2 = tmp[1];
            byte3 = tmp[2];
            byte4 = tmp[3];
            byte5 = tmp[4];
            byte6 = tmp[5];
            byte7 = tmp[6];
            high = tmp[7];
        }

        double make_double(uint8 low, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7, uint8 high, Endianness endian /*= bigEndian*/)
        {
            double result = 0;

            //map the float to a byte array
            uint8* temp = reinterpret_cast<uint8*>(&result);

            //set each byte of the float via the byte array (in big endian)
            temp[0] = low;
            temp[1] = byte2;
            temp[2] = byte3;
            temp[3] = byte4;
            temp[4] = byte5;
            temp[5] = byte6;
            temp[6] = byte7;
            temp[7] = high;

            if (endian == bigEndian)
            {
                return BigEndian_To_SystemEndian(result);
            }

            return LittleEndian_To_SystemEndian(result);
        }

        //Function: getCurrentSystemTime
        //    Gets the current system time in nanoseconds since unix epoch
        uint64 getCurrentSystemTime()
        {
            //create a static HighResClock
            static const HighResClock clock;

            //call getCurrentSystemTime on the clock
            return clock.getCurrentSystemTime();
        }

        void threadSleep(uint64 milli)
        {
            //perform a sleep on this thread for the specified number of milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(milli));
        }

        float round(float value)
        {
            return std::floor(value + 0.5f);
        }

        uint32 floorBase2(double value)
        {
            return static_cast<uint32>(std::pow(2, std::floor(std::log2(value))));
        }

        uint32 ceilBase2(double value)
        {
            return static_cast<uint32>(std::pow(2, std::ceil(std::log2(value))));
        }

        double radiansToDegrees(float angle)
        {
            return angle * 180.0 / 3.14159265358979323846;
        }

        void removeChar(std::string& src, char charToRemove)
        {
            src.erase(std::remove(src.begin(), src.end(), charToRemove), src.end());
        }

        void removeStr(std::string& src, const std::string& strToRemove)
        {
            std::string::size_type strPos;

            //attempt to find the strToRemove for as many times as it exists in the src string
            for (strPos = src.find(strToRemove); strPos != std::string::npos; strPos = src.find(strToRemove))
            {
                //erase the string from the source string
                src.erase(strPos, strToRemove.length());
            }
        }

        bool containsStr(const std::string& src, const std::string& containsThis)
        {
            return src.find(containsThis) != std::string::npos;
        }

        void strTrimLeft(std::string& src)
        {
            std::size_t found = src.find_first_not_of(" \t\f\v\n\r");

            if (found != std::string::npos)
            {
                src.erase(0, found);
            }
            else
            {
                src.clear();  //src is all whitespace
            }
        }

        void strTrimRight(std::string& src)
        {
            std::size_t found = src.find_last_not_of(" \t\f\v\n\r");

            if (found != std::string::npos)
            {
                src.erase(found + 1);
            }
            else
            {
                src.clear();  //src is all whitespace
            }
        }

        void strTrim(std::string& src)
        {
            strTrimLeft(src);
            strTrimRight(src);
        }

        std::vector<std::string> regexFindAll(const std::string& basicString, const std::regex& pattern)
        {
            // Create an iterator of all the matches
            const auto matches = std::sregex_iterator(basicString.begin(), basicString.end(), pattern);

            // List to add each match
            std::vector<std::string> matchList;

            // Add each match to the list
            for (std::sregex_iterator subMatch = matches; subMatch != std::sregex_iterator(); ++subMatch)
            {
                // Get the string from the match
                std::string found = subMatch->str();

                // Add it to the list to return
                matchList.push_back(found);
            }

            return matchList;
        }

        std::vector<std::string> tokenize(const std::string& basicString, const std::string& delimiter, bool includeEmpty)
        {
            // List to store all the delimited segments
            std::vector<std::string> segments;

            // Position tracking of delimiters
            std::size_t previousPosition = 0;

            // Find the first delimiter
            std::size_t found;

            // Extract segments until the end of the string
            do
            {
                // Find the next delimiter
                found = basicString.find(delimiter, previousPosition);

                // Get the substring between the previous and current delimiter
                const std::string substring = basicString.substr(previousPosition, found - previousPosition);

                // Delimiter at the beginning/end of the string will get an empty substring
                if (includeEmpty || !substring.empty())
                {
                    // Add the substring to the list
                    segments.push_back(substring);
                }

                // Set the next read position after the delimiter
                previousPosition = found + delimiter.length();
            }
            while(found != std::string::npos);

            // Return all the segments
            return segments;
        }

        void filterSensorcloudName(std::string& str)
        {
            //replace all characters that don't match (a-z)(A-Z)(0-9)-_. with a '-'
            for (std::size_t i = 0; i < str.length(); i++)
            {
                if (!isalnum(str[i]) && str[i] != '-' && str[i] != '.' && str[i] != '_')
                {
                    str[i] = '-';
                }
            }
        }

        float normalizeAngle(float angle)
        {
            angle = fmod(angle, 360.0f);

            if (angle < 0.0f)
            {
                angle = 360 + angle;
            }

            return angle;
        }
    } // namespace Utils
#endif // !SWIG
} // namespace mscl
