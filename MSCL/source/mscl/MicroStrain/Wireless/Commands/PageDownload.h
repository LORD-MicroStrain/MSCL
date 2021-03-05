/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/Types.h"

namespace mscl
{
    //Title: PageDownload

#ifndef SWIG

    //Class: PageDownload
    //    Contains logic for the PageDownload Node command
    class PageDownload
    {
    private:
        PageDownload();                                    //default constructor disabled
        PageDownload(const PageDownload&);                //copy constructor disabled
        PageDownload& operator=(const PageDownload&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the PageDownload command packet
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for
        //    pageIndex - the page index to download from the Node's memory
        //
        //Returns:
        //    A <ByteStream> containing the command packet
        static ByteStream buildCommand(NodeAddress nodeAddress, uint16 pageIndex);

        //Class: Response
        //    Handles the response to the PageDownload Node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a PageDownload Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_dataPoints
            //    The data points that make up the "page" that was downloaded from the Node
            ByteStream m_dataPoints;

            //Variable: m_matchedPart1
            //    Whether or not part 1 (the Command Byte) of the response has been matched
            bool m_matchedPart1;

        public:
            //Function: match
            //    Checks if the <DataBuffer> passed in matches the expected response pattern's bytes
            //
            //Parameters:
            //    data - The <DataBuffer> containing the bytes to match
            //
            //Returns:
            //    true if the bytes match a response pattern, false otherwise
            virtual bool match(DataBuffer& data) override;

            //Function: dataPoints
            //    Gets the dataPoints that were downloaded from the Node
            //
            //Returns:
            //    A <ByteStream> holding the data points (if any) that were downloaded from the Node
            ByteStream dataPoints();

        private:
            //Function: matchSuccessResponsePart1
            //    Checks if the <DataBuffer> passed in matches the first part (Command Byte) of the response bytes
            //
            //Parameters:
            //    data - The <DataBuffer> containing the bytes to match
            //
            //Returns:
            //    true if the bytes match the first part of the success response pattern, false otherwise
            bool matchSuccessResponsePart1(DataBuffer& data);

            //Function: matchSuccessResponse
            //    Checks if the <DataBuffer> passed in matches the success response bytes
            //
            //Parameters:
            //    data - The <DataBuffer> containing the bytes to match
            //
            //Returns:
            //    true if the bytes match the success response pattern, false otherwise
            bool matchSuccessResponse(DataBuffer& data) override;

            //Function: matchSuccessResponse
            //    Checks if the <DataBuffer> passed in matches the fail response bytes
            //
            //Parameters:
            //    data - The <DataBuffer> containing the bytes to match
            //
            //Returns:
            //    true if the bytes match the fail response pattern, false otherwise
            bool matchFailResponse(DataBuffer& data) override;
        };
    };

#endif
}