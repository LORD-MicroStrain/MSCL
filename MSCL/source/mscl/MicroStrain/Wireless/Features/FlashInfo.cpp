/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "FlashInfo.h"

namespace mscl
{
    FlashInfo::FlashInfo(uint64 storage, uint64 block, uint64 page):
        storageSize(storage),
        blockSize(block),
        pageSize(page)
    {
    }

    FlashInfo FlashInfo::FLASH_SST25VF032B()
    {
        //Total Size: 4 MiB
        //Block Size: 64 KiB
        //Page Size: 256 Bytes
        return FlashInfo((4 * 1049000), (64 * 1024), 256);
    }

    FlashInfo FlashInfo::FLASH_IS25WP128()
    {
        //Total Size: 16 MiB
        //Block Size: 64 KiB
        //Page Size: 256 Bytes
        return FlashInfo((16 * 1049000), (64 * 1024), 256);
    }

    FlashInfo FlashInfo::FROM_FLASH_ID(uint16 flashId)
    {
        switch(flashId)
        {
            case 0:
                return FLASH_SST25VF032B();

            case 1:
                return FLASH_IS25WP128();

            //invalid flash id
            default:
                return FlashInfo(0, 0, 0);
        }
    }
}