/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#define _WIN32_DCOM
#include <comdef.h>
#include <Wbemidl.h>

# pragma comment(lib, "wbemuuid.lib")

#include <map>
#include <string>
#include <vector>


//Class: WMI_Helper
//    WMI_Helper makes it simple to interface and request information from the WMI.
class WMI_Helper
{
public:
    //Typedef: wmiValue
    //    A map of string property names to their VARIANT values
    typedef std::map<std::string, VARIANT> wmiValue;

    //Typedef: wmiValues
    //    A vector of wmiValue maps
    typedef std::vector<wmiValue> wmiValues;

public:
    //Constructor: WMI_Helper
    //    Creates a WMI_Helper object
    //
    //Parameters:
    //    wmi_namespace - The string name of the WMI Namespace (ie. "root\\CIMV2\\Applications\\Games")
    //    wmi_class - The string name of the WMI Class (ie. "Game")
    //
    //Exceptions:
    //    std::exception - Thrown if any errors occur during the <connect> stage 
    WMI_Helper(std::string wmi_namespace, std::string wmi_class);
    
    //Destructor: WMI_Helper
    //    Destroys the WMI_Helper object
    ~WMI_Helper();

public:
    //Function: request
    //    Starts a request for information received from WMI
    //
    //Parameters:
    //    valuesToGet - A vector of strings to request from the namespace and class that was given at construction time
    //
    //Returns:
    //    A vector containing a map for each found item, with each map containing a parameter-value pair
    //
    //Exceptions:
    //    std::exception - Thrown if any errors occur, including if the values that were requested were incorrect
    wmiValues request(std::vector<std::string> valuesToGet);

private:
    void requestThread(std::vector<std::string> valuesToGet);

    //Function: connect
    //    Connects and retrieves information from the WMI namespace and class that was given at construction time
    //
    //Exceptions:
    //    std::exception - Thrown if any errors occur, including if the namespace or class are incorrect
    void connect();

private:
    //Variable: m_wmi_namespace
    //    The WMI namespace that this is using
    std::string m_wmi_namespace;

    //Variable: m_wmi_class
    //    The WMI class that this is using
    std::string m_wmi_class;

    wmiValues m_values;

private:
    //Variable: m_enumerator
    //    The enumerator that holds all the information internally from the request
    IEnumWbemClassObject* m_enumerator;
};

