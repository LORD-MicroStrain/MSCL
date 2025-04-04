/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
#ifndef SWIG
    //Class: GeographicSource
    //    Contains the logic for the Inertial GeographicSource command.
    class GeographicSource : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return m_commandName; }

        //Function: MakeSetCommand
        //
        //Parameter: dataToUse
        //    The <GeographicSourceOptions> to set the option and fixed value.
        //
        //Returns:
        //    GeographicSource - object set up for sending a set command.
        static GeographicSource MakeSetCommand(const GeographicSourceOptions& dataToUse);

        //Function: MakeGetCommand
        //
        //Returns:
        //    GeographicSource - object set up for sending a get command.
        static GeographicSource MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    GeographicSourceOptions - the object containing the current source and fixed value.
        static GeographicSourceOptions getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    protected:
        // Function: Constructor GeographicSource
        //    Private constructor creates an GeographicSource object.  Use Make___Command methods to create an object.
        GeographicSource(MipTypes::FunctionSelector function_selector, const GeographicSourceOptions& dataToUse);
        GeographicSource(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return m_commandType; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return m_fieldDataByte; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_sourceOptions
        //    The GeographicSourceOptions to send to the device.
        GeographicSourceOptions m_sourceOptions;

        //Variable: m_fieldDataByte
        //    The byte ID for field data in the reply.
        uint8 m_fieldDataByte;

        //Variable: m_commandType
        //    The command ID.
        MipTypes::Command m_commandType;

        //Variable: m_commandName
        //    The command name.
        std::string m_commandName;

    public:
        // Destructor
        ~GeographicSource() {}
    };

    //Class: InclinationSource
    //    Contains the logic for the Inertial Inclination GeographicSource command.
    class InclinationSource : public GeographicSource {
    public:
        //Function: MakeSetCommand
        //
        //Parameter: dataToUse
        //    The <GeographicSourceOptions> to set the option and fixed value.
        //
        //Returns:
        //    GeographicSource - object set up for sending a set command.
        static GeographicSource MakeSetCommand(const GeographicSourceOptions& dataToUse);

        //Function: MakeGetCommand
        //
        //Returns:
        //    GeographicSource - object set up for sending a get command.
        static GeographicSource MakeGetCommand();

    private:
        // Function: Constructor InclinationSource
        //    Private constructor creates an InclinationSource object.  Use Make___Command methods to create an object.
        InclinationSource(MipTypes::FunctionSelector function_selector, const GeographicSourceOptions& dataToUse);
        InclinationSource(MipTypes::FunctionSelector function_selector);
    };

    //Class: DeclinationSource
    //    Contains the logic for the Inertial Declination GeographicSource command.
    class DeclinationSource : public GeographicSource {
    public:
        //Function: MakeSetCommand
        //
        //Parameter: dataToUse
        //    The <GeographicSourceOptions> to set the option and fixed value.
        //
        //Returns:
        //    GeographicSource - object set up for sending a set command.
        static GeographicSource MakeSetCommand(const GeographicSourceOptions& dataToUse);

        //Function: MakeGetCommand
        //
        //Returns:
        //    GeographicSource - object set up for sending a get command.
        static GeographicSource MakeGetCommand();

    private:
        // Function: Constructor InclinationSource
        //    Private constructor creates an InclinationSource object.  Use Make___Command methods to create an object.
        DeclinationSource(MipTypes::FunctionSelector function_selector, const GeographicSourceOptions& dataToUse);
        DeclinationSource(MipTypes::FunctionSelector function_selector);
    };

    //Class: MagneticFieldMagnitudeSource
    //    Contains the logic for the Inertial Magnetic Field Magnitude GeographicSource command.
    class MagneticFieldMagnitudeSource : public GeographicSource {
    public:
        //Function: MakeSetCommand
        //
        //Parameter: dataToUse
        //    The <GeographicSourceOptions> to set the option and fixed value.
        //
        //Returns:
        //    GeographicSource - object set up for sending a set command.
        static GeographicSource MakeSetCommand(const GeographicSourceOptions& dataToUse);

        //Function: MakeGetCommand
        //
        //Returns:
        //    GeographicSource - object set up for sending a get command.
        static GeographicSource MakeGetCommand();

    private:
        MagneticFieldMagnitudeSource(MipTypes::FunctionSelector function_selector, const GeographicSourceOptions& dataToUse);
        MagneticFieldMagnitudeSource(MipTypes::FunctionSelector function_selector);
    };
#endif // !SWIG
} // namespace mscl
