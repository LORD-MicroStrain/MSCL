#include "stdafx.h"
#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    //////////  Matrix  //////////

    Matrix_3x3::Matrix_3x3(float i00, float i01, float i02, float i10, float i11, float i12, float i20, float i21, float i22)
    {
        // Not sure why I need firstArray.  Just putting this list in the initialization below doesn't compile.
        std::array<float, 3> firstRow{ i00, i01, i02 };
        m_array = { firstRow,{ i10, i11, i12 },{ i20, i21, i22 } };
    }

    Matrix_3x3::~Matrix_3x3()
    { }

    void Matrix_3x3::set(uint8 row, uint8 col, float value)
    {
        m_array[row][col] = value;
    }


    float Matrix_3x3::operator() (uint8 row, uint8 col) const
    {
        return m_array.at(row).at(col);
    }

    float Matrix_3x3::at(uint8 row, uint8 col) const
    {
        return (*this)(row, col);
    }

    //////////  GeometricVector  //////////

    GeometricVector::GeometricVector(float x_init, float y_init, float z_init) :
        x(x_init),
        y(y_init),
        z(z_init)
    { }

    GeometricVector::GeometricVector() :
        x(0),
        y(0),
        z(0)
    { }

    GeometricVector::~GeometricVector()
    { }



    //////////  TimeUpdate  //////////

TimeUpdate::TimeUpdate(double timeOfWeek, uint16 weekNumber, float timeAccuracy) :
    m_timeOfWeek(timeOfWeek),
    m_weekNumber(weekNumber),
    m_timeAccuracy(timeAccuracy)
{ }

TimeUpdate::~TimeUpdate()
{
}



//////////  HeadingUpdateOptions  //////////


uint8 HeadingUpdateOptions::AsUint8() const
{
    if (useInternalMagnetometer)
    {
        if (useInternalGNSSVelocityVector)
        {
            if (useExternalHeadingMessages)
                return 0x07;
            else
                return 0x04;
        }
        else
        {
            if (useExternalHeadingMessages)
                return 0x06;
            else
                return 0x01;
        }
    }
    else
    {
        if (useInternalGNSSVelocityVector)
        {
            if (useExternalHeadingMessages)
                return 0x05;
            else
                return 0x02;
        }
        else
        {
            if (useExternalHeadingMessages)
                return 0x03;
            else
                return 0x00;
        }
    }
}

//  This constructor converts a uint8 to a HeadingUpdateOptions object according to the Communications Protocol.
HeadingUpdateOptions::HeadingUpdateOptions(const mscl::uint8& headingUpdateOption)
{
    switch (headingUpdateOption)
    {
    case 0x00:
        useInternalMagnetometer = false;
        useInternalGNSSVelocityVector = false;
        useExternalHeadingMessages = false;
        break;
    case 0x01:
        useInternalMagnetometer = true;
        useInternalGNSSVelocityVector = false;
        useExternalHeadingMessages = false;
        break;
    case 0x02:
        useInternalMagnetometer = false;
        useInternalGNSSVelocityVector = true;
        useExternalHeadingMessages = false;
        break;
    case 0x03:
        useInternalMagnetometer = false;
        useInternalGNSSVelocityVector = false;
        useExternalHeadingMessages = true;
        break;
    case 0x04:
        useInternalMagnetometer = true;
        useInternalGNSSVelocityVector = true;
        useExternalHeadingMessages = false;
        break;
    case 0x05:
        useInternalMagnetometer = false;
        useInternalGNSSVelocityVector = true;
        useExternalHeadingMessages = true;
        break;
    case 0x06:
        useInternalMagnetometer = true;
        useInternalGNSSVelocityVector = false;
        useExternalHeadingMessages = true;
        break;
    case 0x07:
        useInternalMagnetometer = true;
        useInternalGNSSVelocityVector = true;
        useExternalHeadingMessages = true;
        break;
    default:
        throw Error_MipCmdFailed("An invalid option value was passed in to HeadingUpdateOptions.");
    }
}



}  // namespace mscl