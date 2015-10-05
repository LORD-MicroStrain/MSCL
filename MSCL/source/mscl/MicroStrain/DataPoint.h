/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include "mscl/Value.h"
#include "mscl/Types.h"
#include "Vector.h"
#include "Matrix.h"
#include "mscl/Histogram.h"
#include "mscl/Timestamp.h"
#include "mscl/MicroStrain/Wireless/StructuralHealth.h"

namespace mscl
{
	//API Class: DataPoint
	//	Base class representing common functionality between Wireless and Inertial data points
	//
	//See Also:
	//	- <Value>
	//	- <InertialDataPoint>
	//	- <WirelessDataPoint>
	class DataPoint : public Value
	{
	private:
		DataPoint();		//default constructor disabled

	public:
#ifndef SWIG
		//Constructor: DataPoint
		//	Creates a DataPoint object
		//
		//Parameters:
		//	type - The <ValueType> of the data that is stored
		//	value - The data that is to be stored
		DataPoint(ValueType type, const anyType& value);
#endif

		virtual ~DataPoint(){}

	public:
		//API Function: as_Vector
		//	Gets the data value as a <Vector> object
		//
		//Returns:
		//	The data value as a <Vector> object
		//
		//Exceptions:
		//	- <Error_BadDataType>: The type in which the value was stored could not be converted to <Vector>
		//
		//Example Use:
		//	(start code)
		//		SerialConnection connection("COM25");
		//		InertialNode device(&connection);
		//		InertialDataPoints data = device.getNextDataPacket().data();
		//		if(data[0].storedAs() == valueType_Vector)
		//		{
		//			std::cout << data[0].as_Vector().at_float(0);
		//			std::cout << data[0].as_Vector().at_float(1);
		//		}
		//	(end code)
		const Vector as_Vector() const;

		//API Function: as_Matrix
		//	Gets the data value as a <Matrix> object
		//
		//Returns:
		//	The data value as a <Matrix> object
		//
		//Exceptions:
		//	- <Error_BadDataType>: The type in which the value was stored could not be converted to a <Matrix>
		//
		//Example Use:
		//	(start code)
		//		SerialConnection connection("COM25");
		//		InertialNode device(&connection);
		//		InertialDataPoints data = device.getNextDataPacket().data();
		//		if(data[0].storedAs() == valueType_Matrix)
		//		{
		//			std::cout << data[0].as_Matrix().at_float(0, 0);
		//			std::cout << data[0].as_Matrix().at_float(0, 1);
		//		}
		//	(end code)
		const Matrix as_Matrix() const;

		//API Function: as_Timestamp
		//	Gets the data value as a <Timestamp> object
		//
		//Returns:
		//	The data value as a <Timestamp> object
		//
		//Exceptions:
		//	- <Error_BadDataType>: The type in which the value was stored could not be converted to a <Timestamp>
		//
		//Example Use:
		//	(start code)
		//		SerialConnection connection("COM25");
		//		InertialNode device(&connection);
		//		InertialDataPoints data = device.getNextDataPacket().data();
		//		if(data[0].storedAs() == valueType_Timestamp)
		//		{
		//			std::cout << data[0].as_Timestamp().nanoseconds();
		//		}
		//	(end code)
		const Timestamp as_Timestamp() const;

		//API Function: as_Bytes
		//	Gets the data value as a <Bytes> object (vector of uint8).
		//
		//Returns:
		//	The data value as a <Bytes> object.
		//
		//Exceptions:
		//	- <Error_BadDataType>: The type in which the value was stored could not be converted to a <Bytes> object.
		const Bytes as_Bytes() const;

		//API Function: as_StructuralHealth
		//	Gets the data value as a <StructuralHealth> object.
		//
		//Returns:
		//	The data value as a <StructuralHealth> object.
		//
		//Exceptions:
		//	- <Error_BadDataType>: The type in which the value was stored could not be converted to a <StructuralHealth> object.
		const StructuralHealth as_StructuralHealth() const;

		//API Function: as_string
		//	Gets the data value as a string
		//
		//Returns:
		//	A string representing the data value. This will be created using the value's current valueType.
		//	- A value stored as a float will return a string as so: "1.2345".
		//	- A value stored as a <Vector> will return a string as so: "[1.2,3.4,5.6]"
		//	- A value stored as a <Matrix> will return a string as so: "[[0,0.1,0.2],[1,1.1,1.2],[2,2.1,2.2]]"
		//	- A value stored as <Bytes> will return a string as so: "0x01 0x02 0x03 0x0a 0xab"
		//
		//Exceptions:
		//	- <Error_BadDataType>: The type in which the value was stored could not be converted to a string.
		//		
		//Example Use:
		//	(start code)
		//		SerialConnection connection("COM25");
		//		InertialNode device(&connection);
		//		InertialDataPoints data = device.getNextDataPacket().data();
		//		std::cout << data[0].as_string();
		//	(end code)
		std::string as_string() const;
	};
}