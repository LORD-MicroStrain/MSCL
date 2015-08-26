/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#pragma once

//This is a custom Error Policy needed so that Turtle doesn't output to standard out
//which was causing errors in the output xml file
//http://sourceforge.net/apps/mediawiki/turtle/index.php?title=Turtle#Error_policy
 
/*
template< typename Result >
struct custom_policy
{
	static Result abort()
	{
		// ...
		return true;
	}
	template< typename Context >
	static void unexpected_call( const Context& context )
	{
		// ...
	}
	template< typename Context >
	static void expected_call( const Context& context, const std::string& file, int line )
	{
		// ...
	}
	template< typename Context >
	static void missing_action( const Context& context, const std::string& file, int line )
	{
		// ...
	}
	template< typename Context >
	static void sequence_failed( const Context& context, const std::string& file, int line )
	{
		// ...
	}
	template< typename Context >
	static void verification_failed( const Context& context, const std::string& file, int line )
	{
		// ...
	}
	template< typename Context >
	static void untriggered_expectation( const Context& context, const std::string& file, int line )
	{
		// ...
	}
};

#define MOCK_ERROR_POLICY custom_policy
*/

