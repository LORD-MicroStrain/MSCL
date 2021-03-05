/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{

#ifndef SWIG
    //Class: MipDataField
    //    An Inertial data field object that represents a data field within an Inertial Data Packet
    class MipDataField
    {
    public:
        //Default Constructor: MipDataField
        //    Creates an empty, invalid MipDataField
        MipDataField();

        //Constructor: MipDataField
        //    Creates a MipDataField with the given fieldId and no field data
        //
        //Parameters:
        //    fieldId - The field id describing the type of the field data
        explicit MipDataField(uint16 fieldId);

        //Constructor: MipDataField
        //    Creates a MipDataField with the given fieldId and field data
        //
        //Parameters:
        //    fieldId - The field id describing the type of the field data
        //    fieldData - The <Bytes> that make up the field data points (not including the field length or descriptor bytes)
        MipDataField(uint16 fieldId, Bytes fieldData);

    private:
        //Variable: m_fieldId
        //    The field type describing the type of the field data
        uint16 m_fieldId;

        //Variable: m_fieldData
        //    The <ByteStream> that holds the bytes making up the field data
        ByteStream m_fieldData;

    public:
        //Function: fieldId
        //    Gets the field id of the field data
        //    
        //Returns:
        //    The field type describing the type of the field data
        uint16 fieldId() const;

        //Function: fieldDescriptor
        //    Gets the field descriptor of the field data
        //
        //Returns:
        //    The field descriptor of the field data
        uint8 fieldDescriptor() const;

        //Function: descriptorSet
        //    Gets the descriptor set of the field data
        //
        //Returns:
        //    The descriptor set of the field data
        uint8 descriptorSet() const;

        //Function: fieldData
        //    Gets the field data as a <ByteStream>
        //
        //Returns:
        //    The <ByteStream> containing the raw bytes of the field data
        ByteStream fieldData() const;
    };

    //Typedef: MipDataFields
    //    Typedef for a vector of <MipDataField> objects
    typedef std::vector<MipDataField> MipDataFields;
#endif
}