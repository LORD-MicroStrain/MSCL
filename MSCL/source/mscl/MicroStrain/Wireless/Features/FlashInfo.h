/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"

namespace mscl
{
    //Struct: FlashInfo
    //  Contains flash information of a <WirelessNode>.
    struct FlashInfo
    {
        //Variable: storageSize
        //  The total storage size, in bytes.
        uint32 storageSize;

        //Variable: blockSize
        //  The size of a datalogging Block, in bytes.
        uint32 blockSize;

        //Variable: pageSize
        //  The size of a datalogging Page, in bytes.
        uint32 pageSize;

        //Variable: maxBandwidth
        //  The max flash bandwidth (bytes per second) that is supported for logging.
        uint32 maxBandwidth;

    private:
        //Constructor: FlashInfo
        //  Creates a FlashInfo object.
        FlashInfo(uint32 storage, uint32 block, uint32 page, uint32 bandwidth);

        FlashInfo();    //disabled default constructor

        //Function: FLASH_SST25VF032B
        //  Static function to create a FlashInfo object for the SST25VF032B Flash.
        //
        //Returns:
        //  A <FlashInfo> made for the SST25VF032B.
        static FlashInfo FLASH_SST25VF032B();
        
        //Function: FLASH_IS25WP128
        //  Static function to create a FlashInfo object for the IS25WP128 Flash.
        //
        //Returns:
        //  A <FlashInfo> made for the IS25WP128.
        static FlashInfo FLASH_IS25WP128();

    public:
        //Function: FROM_FLASH_ID
        //  Static function to create a FlashInfo object from the given flash ID from eeprom.
        //
        //Returns:
        //  A <FlashInfo> for the given flash ID.
        static FlashInfo FROM_FLASH_ID(uint16 flashId);
    };
}