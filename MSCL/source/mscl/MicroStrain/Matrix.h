/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "ByteStream.h"

namespace mscl
{
    //API Class: Matrix
    //    Represents a Matrix of values (varying size)
    class Matrix
    {
    public:
        //Default Constructor: Matrix
        //    Creates a Matrix object with default values
        Matrix();

#ifndef SWIG
        //Constructor: Matrix
        //    Creates a Matrix object given its size and data
        //
        //Parameters:
        //    rows - The number of rows that are in the Matrix
        //    columns - The number of columns that are in the Matrix
        //    storedAs - The <ValueType> representing how all the values in the Matrix are stored
        //    data - The <ByteStream> that hold the values to be stored in the Matrix
        Matrix(uint16 rows, uint16 columns, ValueType storedAs, const ByteStream& data);
#endif
    private:
        //Variable: m_numRows
        //    The number of rows in the Matrix
        uint16 m_numRows;

        //Variable: m_numColumns
        //    The number of columns in the Matrix
        uint16 m_numColumns;

        //Variable: m_valuesType
        //    How each value within the Matrix is stored
        ValueType m_valuesType;

        //Variable: m_valueTypeSize
        //    The size of each values' type within the Matrix
        uint32 m_valuesTypeSize;

    protected:
        //Variable: m_data
        //    A vector of vectors making the matrix that contains all the data values
        ByteStream m_data;

    protected:        
        //Function: getBytePos
        //    Gets the byte position to read in data from the m_data <ByteStream>
        //
        //Parameters:
        //    row - The row being requested
        //    col - The column being requested
        //
        //Exceptions:
        //    - std::out_of_range: The position requested is out of range
        uint32 getBytePos(uint16 row, uint16 col) const;

        //Function: checkIndex
        //    Checks that the given row and column indices (0-based) are within range, throwing an exception if not
        //
        //Parameters:
        //    row - The 0-based row index to check within range
        //    col - The 0-based column index to check within range
        //
        //Exceptions:
        //    - std::out_of_range: The position requested is out of range
        void checkIndex(uint16 row, uint16 col) const;

    public:
        //API Function: valuesType
        //    Gets how each value within the Matrix is stored
        //
        //Returns:
        //    A <ValueType> representing how each value in the Matrix is stored
        ValueType valuesType() const;

        //API Function: rows
        //    Gets the number of rows in the Matrix
        //
        //Returns:
        //    The number of rows in the Matrix
        uint16 rows() const;

        //API Function: columns
        //    Gets the number of columns in the Matrix
        //
        //Returns:
        //    The number of columns in the Matrix
        uint16 columns() const;

        //API Function: as_doubleAt
        //    Gets the value stored at the given row and column (0-based), as an 8-byte double
        //
        //Parameters:
        //    row - The 0-based row index of which to get the value
        //    column - The 0-based column index of which to get the value
        //
        //Returns:
        //    The value stored at the given row and column, as a double
        //
        //Exceptions:
        //    - std::out_of_range: The position requested is out of range
        double as_doubleAt(uint16 row, uint16 column) const;

        //API Function: as_floatAt
        //    Gets the value stored at the given row and column (0-based), as a 4-byte float
        //
        //Parameters:
        //    row - The 0-based row index of which to get the value
        //    column - The 0-based column index of which to get the value
        //
        //Returns:
        //    The value stored at the given row and column, as a float
        //
        //Exceptions:
        //    - std::out_of_range: The position requested is out of range
        float as_floatAt(uint16 row, uint16 column) const;

        //API Function: as_uint16At
        //    Gets the value stored at the given row and column (0-based), as a 2-byte unsigned integer
        //
        //Parameters:
        //    row - The 0-based row index of which to get the value
        //    column - The 0-based column index of which to get the value
        //
        //Returns:
        //    The value stored at the given row and column, as a 2-byte unsigned integer
        //
        //Exceptions:
        //    - std::out_of_range: The position requested is out of range
        uint16 as_uint16At(uint16 row, uint16 column) const;

        //API Function: as_uint8At
        //    Gets the value stored at the given row and column (0-based), as a 1-byte uint8
        //
        //Parameters:
        //    row - The 0-based row index of which to get the value
        //    column - The 0-based column index of which to get the value
        //
        //Returns:
        //    The value stored at the given row and column, as a 1-byte uint8
        //
        //Exceptions:
        //    - std::out_of_range: The position requested is out of range
        uint8 as_uint8At(uint16 row, uint16 column) const;

        //API Function: str
        //    Creates a string from the Matrix
        //
        //Returns:
        //    A string representing the entire Matrix object (ex. "[[0,0.1,0.2],[1,1.1,1.2],[2,2.1,2.2]]")
        std::string str() const;
    };
}