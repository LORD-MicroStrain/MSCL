/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "Matrix.h"
#include "DataBuffer.h"
#include "ByteStream.h"
#include "mscl/Utils.h"

namespace mscl
{
    Matrix::Matrix():
        m_numRows(0),
        m_numColumns(0),
        m_valuesType(valueType_float),
        m_valuesTypeSize(4)
    {
    }

    Matrix::Matrix(uint16 rows, uint16 columns, ValueType storedAs, const ByteStream& data):
        m_numRows(rows),
        m_numColumns(columns),
        m_data(data.data()),
        m_valuesType(storedAs),
        m_valuesTypeSize(Utils::valueTypeSize(storedAs))
    {
    }

    uint32 Matrix::getBytePos(uint16 row, uint16 col) const
    {
        //check the row and column indicies
        checkIndex(row, col);

        //byte position = (row * (bytes per column * # columns)) + (column * bytes per column)
        return (row * (m_valuesTypeSize * m_numColumns)) + (col * m_valuesTypeSize);
    }

    void Matrix::checkIndex(uint16 row, uint16 col) const
    {
        //check the rows
        if(row >= m_numRows)
        {
            throw std::out_of_range("The row index is out of range");
        }
        //check the columns
        else if(col >= m_numColumns)
        {
            throw std::out_of_range("The column index is out of range");
        }
    }

    ValueType Matrix::valuesType() const
    {
        return m_valuesType;
    }

    uint16 Matrix::rows() const
    {
        return m_numRows;
    }

    uint16 Matrix::columns() const
    {
        return m_numColumns;
    }

    float Matrix::as_floatAt(uint16 row, uint16 column) const
    {
        //return the float at the requested position
        return m_data.read_float(getBytePos(row, column));
    }

    uint16 Matrix::as_uint16At(uint16 row, uint16 column) const
    {
        //return the uint16 at the requested position
        return m_data.read_uint16(getBytePos(row, column));
    }

    uint8 Matrix::as_uint8At(uint16 row, uint16 column) const
    {
        //return the uint8 at the requested position
        return m_data.read_uint8(getBytePos(row, column));
    }

    std::string Matrix::str() const
    {
        std::stringstream result;

        result << "[";
        //for every value in the Matrix
        for (uint16 row = 0; row < m_numRows; row++)
        {
            result << "[";
            for(uint16 col = 0; col < m_numColumns; col++)
            {
                //get the value of the value depending on how it is stored
                switch(m_valuesType)
                {
                case valueType_uint16:
                    result << as_uint16At(row, col);
                    break;

                case valueType_float:
                    result << as_floatAt(row, col);
                    break;

                //all other values not supported as a Vector type as of now
                default:
                    break;
                }

                //if this isn't the last column in the row
                if(col != (m_numColumns - 1))
                {
                    //add a separator
                    result << ",";
                }
            }
            result << "]";

            //if this isnt the last row
            if(row != (m_numRows - 1))
            {
                //add a separator
                result << ",";
            }
        }
        result << "]";

        return result.str();
    }
}