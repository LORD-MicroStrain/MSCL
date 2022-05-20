/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "InertialFieldParser_System.h"

namespace mscl
{
    //the classes in this file do not get referenced anywhere, therefore the
    //linker will not include this compilation unit when statically
    //linking to an executable. Defining this variable, and then using it
    //elsewhere, will force this file to be included
    bool _forceLibraryToIncludeCompilationUnit_System;

    //=====================================================================================================================================================
    //                                                        MipSystemFieldParser
    bool MipSystemFieldParser::registerSystemParser(const MipTypes::ChannelField chField, const MipFieldParser* parser)
    {
        bool registered = true;
        const MipTypes::MipChannelFields fields = MipTypes::getChannelFields_allDataClasses(chField);
        for (const MipTypes::ChannelField field : fields)
        {
            // any failures should return false
            registered = registered && registerParser(field, parser);
        }

        return registered;
    }
    //=====================================================================================================================================================
}