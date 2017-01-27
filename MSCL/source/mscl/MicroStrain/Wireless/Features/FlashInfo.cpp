/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "FlashInfo.h"

namespace mscl
{
    FlashInfo::FlashInfo(uint32 storage, uint32 block, uint32 page, uint32 bandwidth):
        storageSize(storage),
        blockSize(block),
        pageSize(page),
        maxBandwidth(bandwidth)
    {
    }

    FlashInfo FlashInfo::FLASH_SST25VF032B()
    {
        //Total Size: 4 MiB
        //Block Size: 64 KiB
        //Page Size: 256 Bytes
        //Max Bandwidth: 65535 ??
        return FlashInfo((4 * 1024 * 1024), (64 * 1024), 256, 65535);
    }

    FlashInfo FlashInfo::FLASH_IS25WP128()
    {
        //Total Size: 16 MiB
        //Block Size: 64 KiB
        //Page Size: 256 Bytes
        //Max Bandwidth: 65535
        return FlashInfo((16 * 1024 * 1024), (64 * 1024), 256, 65535);
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
                return FlashInfo(0, 0, 0, 0);
        }
    }
}