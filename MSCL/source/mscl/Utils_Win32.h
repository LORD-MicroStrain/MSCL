/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <string>
#include <vector>
#include <Windows.h>


//Title: Utils_Win32

#ifdef UNICODE
    //Typedef: hstring
    //    The "host-string" (as a wstring on UNICODE) that can be used interchangably between unicode and multi-byte builds
    typedef std::wstring hstring;
#else
    //Typedef: hstring
    //    The "host-string" (as a string on MULTIBYTE) that can be used interchangably between unicode and multi-byte builds
    typedef std::string hstring;
#endif

namespace mscl
{ 
    //Namespace: Utils_Win32
    //    Contains Windows helper functions
    namespace Utils_Win32
    {
        //Function: wstring_to_string
        //    Converts a std::wstring to a std::string
        //
        //Parameters:
        //    in - the wstring to convert to a string
        //
        //Returns:
        //    the std::string representation of the input
        inline std::string wstring_to_string(const std::wstring& in)
        {
            std::vector<char> buffer(in.length() + 1);
            WideCharToMultiByte(CP_ACP, 0, in.c_str(), -1, &buffer[0], static_cast<int>(buffer.size()), NULL, NULL);
            return std::string(&buffer[0]);
        }

        //Function: string_to_wstring
        //    Converts a std::string to a std::wstring
        //
        //Parameters:
        //    in - the string to convert to a wstring
        //
        //Returns:
        //    the std::wstring representation of the input
        inline std::wstring string_to_wstring(const std::string& in)
        {
            std::vector<wchar_t> buffer(in.length() + 1);
            MultiByteToWideChar(CP_ACP, 0, in.c_str(), -1, &buffer[0], static_cast<int>(buffer.size()));
            return std::wstring(&buffer[0]);
        }

    #ifdef UNICODE
        //Function: toHstring
        //    Converts a std::string to an hstring
        //
        //Parameters:
        //    in - the std::string to convert to an hstring
        //
        //Returns:
        //    An hstring representation of the passed in string
        inline hstring toHstring(const std::string& in)
        {
            //unicode so convert the string to a wstring
            return string_to_wstring(in);
        }

        //Function: toHstring
        //    Converts a std::wstring to an hstring
        //
        //Parameters:
        //    in - the std::wstring to convert to an hstring
        //
        //Returns:
        //    An hstring representation of the passed in wstring
        inline hstring toHstring(const std::wstring& in)
        {
            //unicode so just return the wstring
            return in;
        }

        //Function: toString
        //    Converts a hstring to an std::string
        //
        //Parameters:
        //    in - the hstring to convert to an std::string
        //
        //Returns:
        //    An std::string representation of the passed in hstring
        inline std::string toString(const hstring& in)
        {
            //unicode so convert the hstring to a string
            return wstring_to_string(in);
        }

        //Function: toWstring
        //    Converts a hstring to an std::wstring
        //
        //Parameters:
        //    in - the hstring to convert to an std::wstring
        //
        //Returns:
        //    An std::wstring representation of the passed in hstring
        inline std::wstring toWstring(const hstring& in)
        {
            //unicode so just return the hstring
            return in;
        }
    #else
        //Function: toHstring
        //    Converts a std::string to an hstring
        //
        //Parameters:
        //    in - the std::string to convert to an hstring
        //
        //Returns:
        //    An hstring representation of the passed in string
        inline hstring toHstring(const std::string& in)
        {
            return in;
        }

        //Function: toHstring
        //    Converts a std::wstring to an hstring
        //
        //Parameters:
        //    in - the std::wstring to convert to an hstring
        //
        //Returns:
        //    An hstring representation of the passed in wstring
        inline hstring toHstring(const std::wstring& in)
        {
            return wstring_to_string(in);
        }

        //Function: toString
        //    Converts a hstring to an std::string
        //
        //Parameters:
        //    in - the hstring to convert to an std::string
        //
        //Returns:
        //    An std::string representation of the passed in hstring
        inline std::string toString(const hstring& in)
        {
            return in;
        }

        //Function: toWstring
        //    Converts a hstring to an std::wstring
        //
        //Parameters:
        //    in - the hstring to convert to an std::wstring
        //
        //Returns:
        //    An std::wstring representation of the passed in hstring
        inline std::wstring toWstring(const hstring& in)
        {
            return string_to_wstring(in);
        }
    #endif
    }
}