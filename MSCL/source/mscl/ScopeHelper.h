/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <functional>
#include <string>
#include "Types.h"

namespace mscl
{
	//Class: ScopeHelper
	//	Class that allows a function to be run when this object goes out of scope.
	class ScopeHelper
	{
	private:
		//Variable: m_outOfScopeFunction
		//	The function to run when the ScopeHelper goes out of scope.
		std::function<void()> m_outOfScopeFunction;

		//Variable: m_canceled
		//	Whether the scope function has been canceled or not.
		bool m_canceled;

		ScopeHelper();								//default constructor disabled
		ScopeHelper(const ScopeHelper&);			//copy constructor disabled
		ScopeHelper& operator=(const ScopeHelper&);	//assignment operator disabled

	public:
		ScopeHelper(std::function<void()> scopeFunction);

		~ScopeHelper();

		void cancel();
	};
}