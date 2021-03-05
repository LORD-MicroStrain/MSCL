/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Value.h"
#include "mscl/Types.h"
#include "Vector.h"
#include "Matrix.h"
#include "mscl/Histogram.h"
#include "mscl/Timestamp.h"
#include "mscl/MicroStrain/Wireless/StructuralHealth.h"

#include <map>

namespace mscl
{
    //API Title: DataPoint

    //API Typedef: RfSweep
    //    Typedef for a map of uint32 to int16 values.
    typedef std::map<uint32, int16> RfSweep;

    //API Class: DataPoint
    //    Base class representing common functionality between Wireless and Inertial data points
    //
    //See Also:
    //    - <Value>
    //    - <MipDataPoint>
    //    - <WirelessDataPoint>
    class DataPoint : public Value
    {
    private:
        DataPoint();        //default constructor disabled

    public:
        //API Enum: ChannelPropertyId
        //  Available channel properties that can be stored with the WirelessDataPoint.
        //
        //  channelPropertyId_angle                 - 0 - The angle (float) that the channel is from.
        //  channelPropertyId_derivedFrom           - 1 - The <ChannelMask> that a derived channel is representing.
        //  channelPropertyId_derivedAlgorithmId    - 2 - The <WirelessTypes::DerivedDataPacketAlgorithmId> of the derived channel.
        enum ChannelPropertyId
        {
            channelPropertyId_angle = 0,
            channelPropertyId_derivedFrom = 1,
            channelPropertyId_derivedAlgorithmId = 2,
        };

        //Typedef: ChannelProperties
        //  Typedef for a map of <ChannelPropertyId> to <Value> pairs.
        typedef std::map<ChannelPropertyId, Value> ChannelProperties;

#ifndef SWIG
        //Constructor: DataPoint
        //    Creates a DataPoint object
        //
        //Parameters:
        //    type - The <ValueType> of the data that is stored
        //    value - The data that is to be stored
        DataPoint(ValueType type, const anyType& value, const ChannelProperties& channelProperties = ChannelProperties());
#endif

        virtual ~DataPoint(){}

    protected:
        //Variable: m_channelProperties
        //  The <ChannelProperties> associated with the data point (if any).
        ChannelProperties m_channelProperties;

    public:
        //API Function: channelProperty
        //  Gets the channel property for the specified <ChannelPropertyId> associated with the data point.
        //
        //Parameters:
        //  id - The <ChannelPropertyId> to request.
        //
        //Returns:
        //  A <Value> representing the channel property.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The provided <ChannelPropertyId> is not supported for this data point.
        const Value& channelProperty(ChannelPropertyId id) const;

        //API Function: as_Vector
        //    Gets the data value as a <Vector> object
        //
        //Returns:
        //    The data value as a <Vector> object
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to <Vector>
        const Vector as_Vector() const;

        //API Function: as_Matrix
        //    Gets the data value as a <Matrix> object
        //
        //Returns:
        //    The data value as a <Matrix> object
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a <Matrix>
        const Matrix as_Matrix() const;

        //API Function: as_Timestamp
        //    Gets the data value as a <Timestamp> object
        //
        //Returns:
        //    The data value as a <Timestamp> object
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a <Timestamp>
        const Timestamp as_Timestamp() const;

        //API Function: as_Bytes
        //    Gets the data value as a <Bytes> object (vector of uint8).
        //
        //Returns:
        //    The data value as a <Bytes> object.
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a <Bytes> object.
        const Bytes as_Bytes() const;

        //API Function: as_StructuralHealth
        //    Gets the data value as a <StructuralHealth> object.
        //
        //Returns:
        //    The data value as a <StructuralHealth> object.
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a <StructuralHealth> object.
        const StructuralHealth as_StructuralHealth() const;

        //API Function: as_RfSweep
        //    Gets the data value as an <RfSweep>.
        //
        //Returns:
        //    The data value as an <RfSweep>.
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to an <RfSweep>.
        const RfSweep as_RfSweep() const;

        //API Function: as_string
        //    Gets the data value as a string
        //
        //Returns:
        //    A string representing the data value. This will be created using the value's current valueType.
        //    - A value stored as a float will return a string as so: "1.2345".
        //    - A value stored as a <Vector> will return a string as so: "[1.2,3.4,5.6]"
        //    - A value stored as a <Matrix> will return a string as so: "[[0,0.1,0.2],[1,1.1,1.2],[2,2.1,2.2]]"
        //    - A value stored as <Bytes> will return a string as so: "0x01 0x02 0x03 0x0a 0xab"
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a string.
        std::string as_string() const override;
    };
}