#pragma once

#include "mscl/Types.h"
#include <array>


namespace mscl
{

    //API Typedef: GeometricVector
    //  A container of floats to represent a geometric vector.
    typedef std::vector<float> GeometricVector;

    //API Typedef: SatellitePRNs
    //  A vector of <uint16> PRN#s for satellites.
    typedef std::vector<uint16> SatellitePRNs;

    ///////////////  TimeUpdate  ///////////////
    
//API Class: TimeUpdate
//    Contains time data for the GNSS_AssistTimeUpdate class.
class TimeUpdate
{
public:
    //API Constructor: TimeUpdate
    //    Creates a TimeUpdate object.
    //
    //Parameters:
    //    timeOfWeek    - time into a given week in seconds.
    //    weekNumber    - the week number.
    //    timeAccuracy  - accuracy in seconds.
    TimeUpdate(double timeOfWeek, uint16 weekNumber, float timeAccuracy);

    //API Destructor: ~TimeUpdate
    //    Destroys a TimeUpdate object.
    ~TimeUpdate();

    //API Function: timeOfWeek
    //  time into a given week in seconds.
    double timeOfWeek() const { return m_timeOfWeek; }

    //API Function: weekNumber
    //  the week number.
    uint16 weekNumber() const { return m_weekNumber; }

    //API Function: timeAccuracy
    //  accuracy in seconds.
    float timeAccuracy() const { return m_timeAccuracy; }

private:
    //Constant: timeOfWeek
    //  time into a given week in seconds.
    const double m_timeOfWeek;

    //Constant: weekNumber
    //  the week number.
    const uint16 m_weekNumber;

    //Constant: timeAccuracy
    //  accuracy in seconds.
    const float m_timeAccuracy;
};


                /////  SBASSettings  /////

//API Struct: SBASSettingsData
//    Contains the data for the SBASSettings class.
struct SBASSettingsData
{
    //API Variable: enableSBAS
    bool enableSBAS;

    //API Variable: enableRanging
    bool enableRanging;

    //API Variable: enableCorrectionData
    bool enableCorrectionData;

    //API Variable: applyIntergityInfo
    bool applyIntergityInfo;

    //API Variable: SatellitePRNs 
    //  The <SatellitePRNs> for all included satellites.
    SatellitePRNs satellitePRNs;
};

//API Struct: Constellation
//    Contains the satellite constellation data used in the <ConstellationSettingsData> class.
struct Constellation
{
    //API Variable: constellationID
    uint8 constellationID;

    //API Variable: enabled
    bool enabled;

    //API Variable: reservedChannelCount
    //  The number of reserved channels.  (Must be <= 32)
    uint8 reservedChannelCount;

    //API Variable: maxChannels
    //  The maximum number of tracking channels.
    uint8 maxChannels;

    //API Variable: enableL1SAIF
    //  enables L1AIF for constellation QZSS
    bool enableL1SAIF;
};

typedef std::vector<Constellation> Constellations;

//API Struct: ConstellationSettingsData
//    Contains the data for the <InertialNode::setConstellationSettings> API call.
struct ConstellationSettingsData
{
    //API Variable: maxChannelsAvailable
    uint16 maxChannelsAvailable;  // Ignored on send.  Only relevent on reply.

    //API Variable: maxChannelsToUse
    uint16 maxChannelsToUse;

    //API Variable: constellations
    Constellations constellations;
};


}
