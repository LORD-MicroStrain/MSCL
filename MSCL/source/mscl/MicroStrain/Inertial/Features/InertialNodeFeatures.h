/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <memory>

#include "mscl/MicroStrain/Inertial/InertialNodeInfo.h"

namespace mscl
{    
    //API Class: InertialNodeFeatures
    //    Contains information on which features are supported by an <InertialNode>.
    class InertialNodeFeatures
    {
    private:
        InertialNodeFeatures();                                            //disabled default constructor
        InertialNodeFeatures(const InertialNodeFeatures&);                //disabled copy constructor
        InertialNodeFeatures& operator=(const InertialNodeFeatures&);    //disable assignment operator

    public:
        virtual ~InertialNodeFeatures() {};

    protected:
        //Constructor: InertialNodeFeatures
        //    Creates a InertialNodeFeatures object.
        //
        //Parameters:
        //    info - An <InertialNodeInfo> object representing standard information of the <InertialNode>.
        InertialNodeFeatures(const InertialNodeInfo& info);

        //Variable: m_nodeInfo
        //    The <InertialNodeInfo> object containing basic information retreived from eeprom about the <InertialNode>.
        InertialNodeInfo m_nodeInfo;

    public:
#ifndef SWIG
        //Function: create
        //    Builds and returns a InertialNodeFeatures pointer based on the given parameters.
        //
        //Parameters:
        //    info - An <InertialNodeInfo> object representing standard information of the device.
        //
        //Returns:
        //    An InertialNodeFeatures unique_ptr.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Node model is not supported by MSCL.
        static std::unique_ptr<InertialNodeFeatures> create(const InertialNodeInfo& info);
#endif
    };
}