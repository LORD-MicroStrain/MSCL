/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

//This is a custom Error Policy needed so that Turtle doesn't output to standard out
//which was causing errors in the output xml file
//https://sourceforge.net/apps/mediawiki/turtle/index.php?title=Turtle#Error_policy

// template< typename Result >
// struct custom_policy
// {
//     static Result abort()
//     {
//         // ...
//         return true;
//     }
//     template< typename Context >
//     static void unexpected_call( const Context& context )
//     {
//         // ...
//     }
//     template< typename Context >
//     static void expected_call( const Context& context, const std::string& file, int line )
//     {
//         // ...
//     }
//     template< typename Context >
//     static void missing_action( const Context& context, const std::string& file, int line )
//     {
//         // ...
//     }
//     template< typename Context >
//     static void sequence_failed( const Context& context, const std::string& file, int line )
//     {
//         // ...
//     }
//     template< typename Context >
//     static void verification_failed( const Context& context, const std::string& file, int line )
//     {
//         // ...
//     }
//     template< typename Context >
//     static void untriggered_expectation( const Context& context, const std::string& file, int line )
//     {
//         // ...
//     }
// };
//
// #define MOCK_ERROR_POLICY custom_policy
