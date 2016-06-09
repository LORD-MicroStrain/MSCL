/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Utils.h"

#include <bitset>
#include <chrono>
#include <locale>
#include <thread>

#include "HighResClock.h"
#include "Types.h"
#include "mscl/Endianness.h"
#include "Exceptions.h"

namespace mscl
{

#ifndef SWIG
    namespace Utils
    {
        uint32 valueTypeSize(ValueType type)
        {
            switch(type)
            {
            case valueType_double:
                return 8;

            case valueType_float:
            case valueType_int32:
                return 4;

            case valueType_int16:
            case valueType_uint16:
            case valueType_uint32:
                return 2;

            case valueType_uint8:
            case valueType_bool:
                return 1;

            default:
                throw Error("Requested ValueType does not have a given size");
            }
        }

        //Function: msb
        //    gets the Most Significant Byte from the 2-Byte value
        uint8 msb(uint16 value)
        {
            return value >> 8;
        }

        //Function: lsb
        //    gets the Least Significant Byte from the 2-Byte value
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

        //    gets the 2-byte signed value from the 2 MSB and LSB bytes
        int16 make_int16(uint8 msb, uint8 lsb)
        {
            return (static_cast<int16>(msb) << 8) | static_cast<int16>(lsb);
        }

        //    Converts the 2 byte value into its 2 bytes
        void split_uint16(uint16 value, uint8& msb, uint8& lsb)
        {
            //Shift 8 bits right, drop the lower byte
            msb = value >> 8;    

            //Mask out the upper byte
            lsb = value & 0xFF;
        }

        //    gets the 2-byte unsigned value from the 2 MSB and LSB bytes
        uint16 make_uint16(uint8 msb, uint8 lsb)
        {
            return (static_cast<uint16>(msb) << 8) | static_cast<uint16>(lsb);
        }

        //    Converts the 4 byte value into its 4 bytes
        void split_uint32(uint32 value, uint8& byte1, uint8& byte2, uint8& byte3, uint8& byte4)
        {
            //Shift 24 bits right, drop the lower bytes
            byte1 = value >> 24;    

            //Shift 16 bits right, drop the lower bytes, mask out the upper bytes
            byte2 = (value >> 16) & 0xFF;

            //Shift 8 bits right, drop the lower byte, mask out the upper bytes
            byte3 = (value >> 8) & 0xFF;

            //Mask out the upper bytes
            byte4 = value & 0xFF;
        }

        void split_uint32(uint32 value, uint16& msw, uint16& lsw)
        {
            //Shift 16 bits right, drop the lower bytes
            msw = value >> 16;

            //Mask out the upper bytes
            lsw = value & 0xFFFF;
        }

        //    gets the 4-byte value from the 4 passed in bytes
        uint32 make_uint32(uint8 byte1, uint8 byte2, uint8 byte3, uint8 byte4)
        {
            //Shift msb 8 bits left, OR the lsb in
            uint16 hiWord = (byte1 << 8) | byte2;

            //Shift lsb 8 bits left, OR the lsb in
            uint16 loWord = (byte3 << 8) | byte4;

            return make_uint32(hiWord, loWord);
        }

        uint32 make_uint32(uint16 msw, uint16 lsw)
        {
            return (static_cast<uint32>(msw) << 16) | static_cast<uint32>(lsw);
        }

        uint64 make_uint64(uint8 msb, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7, uint8 lsb)
        {
            uint32 high = make_uint32(msb, byte2, byte3, byte4);
            uint32 low = make_uint32(byte5, byte6, byte7, lsb);

            return (static_cast<uint64>(high) << 32 | static_cast<uint64>(low));
        }

        void split_float_big_endian(float value, uint8& msb, uint8& byte2, uint8& byte3, uint8& lsb)
        {
            //convert the float from system endian to big endian
            float bigEndianVal = SystemEndian_To_BigEndian(value);

            //map the float to a byte array
            uint8* tmp = (uint8*)&bigEndianVal;

            //get each byte of the float
            msb        = tmp[0];
            byte2      = tmp[1];
            byte3      = tmp[2];
            lsb        = tmp[3];
        }

        void split_float_little_endian(float value, uint8& lsb, uint8& byte2, uint8& byte3, uint8& msb)
        {
            //convert the float from system endian to little endian
            float littleEndianVal = SystemEndian_To_LittleEndian(value);

            //map the float to a byte array
            uint8* tmp = (uint8*)&littleEndianVal;

            //get each byte of the float
            lsb        = tmp[0];
            byte2      = tmp[1];
            byte3      = tmp[2];
            msb        = tmp[3];
        }

        float make_float_big_endian(uint8 msb, uint8 byte2, uint8 byte3, uint8 lsb)
        {
            float result = 0;

            //map the float to a byte array
            uint8* tmp = (uint8*)&result;

            //set each byte of the float via the byte array (in big endian)
            tmp[0] = msb;
            tmp[1] = byte2;
            tmp[2] = byte3;
            tmp[3] = lsb;

            //convert the big endian float to a system endian
            return BigEndian_To_SystemEndian(result);
        }

        float make_float_little_endian(uint8 lsb, uint8 byte2, uint8 byte3, uint8 msb)
        {
            float result = 0;

            //map the float to a byte array
            uint8* tmp = (uint8*)&result;

            //set each byte of the float via the byte array (in little endian)
            tmp[0] = lsb;
            tmp[1] = byte2;
            tmp[2] = byte3;
            tmp[3] = msb;

            //convert the little endian float to a system endian
            return LittleEndian_To_SystemEndian(result);
        }

        void split_double_big_endian(double value, uint8& msb, uint8& byte2, uint8& byte3, uint8& byte4, uint8& byte5, uint8& byte6, uint8& byte7, uint8& lsb)
        {
            //convert the double from system endian to big endian
            double bigEndianVal = SystemEndian_To_BigEndian(value);

            //map the double to a byte array
            uint8* tmp = (uint8*)&bigEndianVal;

            //get each byte of the double
            msb = tmp[0];
            byte2 = tmp[1];
            byte3 = tmp[2];
            byte4 = tmp[3];
            byte5 = tmp[4];
            byte6 = tmp[5];
            byte7 = tmp[6];
            lsb = tmp[7];
        }

        void split_double_little_endian(double value, uint8& lsb, uint8& byte2, uint8& byte3, uint8& byte4, uint8& byte5, uint8& byte6, uint8& byte7, uint8& msb)
        {
            //convert the double from system endian to little endian
            double littleEndianVal = SystemEndian_To_LittleEndian(value);

            //map the double to a byte array
            uint8* tmp = (uint8*)&littleEndianVal;

            //get each byte of the double
            lsb = tmp[0];
            byte2 = tmp[1];
            byte3 = tmp[2];
            byte4 = tmp[3];
            byte5 = tmp[4];
            byte6 = tmp[5];
            byte7 = tmp[6];
            msb = tmp[7];
        }

        double make_double_big_endian(uint8 msb, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7, uint8 lsb)
        {
            double result = 0;

            //map the double to a byte array
            uint8* tmp = (uint8*)&result;

            //set each byte of the double via the byte array
            tmp[0] = msb;
            tmp[1] = byte2;
            tmp[2] = byte3;
            tmp[3] = byte4;
            tmp[4] = byte5;
            tmp[5] = byte6;
            tmp[6] = byte7;
            tmp[7] = lsb;

            //convert from big endian to system endian
            return BigEndian_To_SystemEndian(result);
        }

        double make_double_little_endian(uint8 lsb, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7, uint8 msb)
        {
            double result = 0;

            //map the double to a byte array
            uint8* tmp = (uint8*)&result;

            //set each byte of the double via the byte array
            tmp[0] = lsb;
            tmp[1] = byte2;
            tmp[2] = byte3;
            tmp[3] = byte4;
            tmp[4] = byte5;
            tmp[5] = byte6;
            tmp[6] = byte7;
            tmp[7] = msb;

            //convert from little endian to system endian
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
            return std::floor( value + 0.5f );
        }

        uint32 floorBase2(double value)
        {
            return static_cast<uint32>( std::pow( 2, std::floor( std::log2(value) ) ) );
        }

        uint32 ceilBase2(double value)
        {
            return static_cast<uint32>( std::pow(2, std::ceil( std::log2(value) ) ) );
        }

        double radiansToDegrees(float angle)
        {
            return (angle * 180.0 / 3.14159265358979323846);
        }

        bool bitIsSet(uint32 value, size_t bitPos)
        {
            std::bitset<32> bitset(value);

            return bitset.test(bitPos);
        }

        void removeChar(std::string& src, char charToRemove)
        {
            src.erase(std::remove(src.begin(), src.end(), charToRemove), src.end());
        }

        void removeStr(std::string& src, const std::string& strToRemove)
        {
            std::string::size_type strPos;
            
            //attempt to find the strToRemove for as many times as it exists in the src string
            for(strPos = src.find(strToRemove); strPos != std::string::npos; strPos = src.find(strToRemove))
            {
                //erase the string from the source string
                src.erase(strPos, strToRemove.length());
            }
        }

        bool containsStr(const std::string& src, const std::string& containsThis)
        {
            return (src.find(containsThis) != std::string::npos);
        }

        void strTrimLeft(std::string& src)
        {
            std::size_t found = src.find_first_not_of(" \t\f\v\n\r");

            if(found != std::string::npos)
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

            if(found != std::string::npos)
            {
                src.erase(found + 1);
            }
            else
            {
                src.clear();  //src is all whitespace
            }
        }

        void filterSensorcloudName(std::string& str)
        {
            //replace all characters that don't match (a-z)(A-Z)(0-9)-_. with a '-'
            for(std::size_t i=0; i < str.length(); i++) 
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

            if(angle < 0.0f)
            {
                angle = 360 + angle;
            }

            return angle;
        }
    }
#endif
}
