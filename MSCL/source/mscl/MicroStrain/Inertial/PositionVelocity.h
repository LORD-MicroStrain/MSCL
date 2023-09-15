/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include <vector>

namespace mscl
{
    typedef std::vector<Value> MipFieldValues;

    //API Enum: PositionVelocityReferenceFrame
    //    Enum representing position and velocity reference frame options.
    //
    //  ECEF    - 0x01  -   Earth-Centered, Earth-Fixed
    //  LLH_NED - 0x02  -   Position: Lat/Long/Height, Velocity: North/East/Down
    enum PositionVelocityReferenceFrame
    {
        ECEF = 0x01,
        LLH_NED = 0x02,
        LOCAL = 0x03
    };

    //API Class: GeometricVector
    //    Defines a 3 dimensional, spatial vector.
    class GeometricVector
    {
    public:
        //API Function: VectorECEF
        //    Initializes and returns a new vector with the reference frame set to Earth-Centered, Earth-Fixed
        //
        //Parameters:
        //    x_init - initial x coordinate
        //    y_init - initial y coordinate
        //    z_init - initial z coordinate
        static GeometricVector VectorECEF(float x_init, float y_init, float z_init) { return GeometricVector(x_init, y_init, z_init); }

        //API Function: VectorNED
        //    Initializes and returns a new vector with the reference frame set to North-East-Down
        //
        //Parameters:
        //    north - initial x coordinate
        //    east - initial y coordinate
        //    down - initial z coordinate
        static GeometricVector VectorNED(float north, float east, float down) { return GeometricVector(north, east, down, PositionVelocityReferenceFrame::LLH_NED); }

        //API Constructor: GeometricVector
        //    Creates a GeometricVector object.
        //
        //Parameters:
        //    x_init - initial x coordinate
        //    y_init - initial y coordinate
        //    z_init - initial z coordinate
        //    ref - reference frame (default: ECEF)
        GeometricVector(float x_init, float y_init, float z_init, PositionVelocityReferenceFrame ref = PositionVelocityReferenceFrame::ECEF);

        //API Constructor: GeometricVector
        //    Creates a zero-filled GeometricVector object.
        //    Default reference frame: ECEF
        GeometricVector();

        //API Destructor: ~GeometricVector
        //    Destroys a TimeUpdate object.
        ~GeometricVector();

    public:
        void fromMipFieldValues(const MipFieldValues& data, uint8 offset = 0, bool includesFrame = false);
        MipFieldValues asMipFieldValues(bool includeFrame = false) const;
        void appendMipFieldValues(MipFieldValues& appendTo, bool includeFrame = false) const;

    public:
        //API Variable: referenceFrame
        //    The <PositionVelocityReferenceFrame> of this vector.
        //    Default: ECEF
        PositionVelocityReferenceFrame referenceFrame;

        //API Function: x
        // Only valid if referenceFrame is ECEF
        float x() const { return vec_0; }
        void x(float x) { vec_0 = x; };

        //API Function: y
        // Only valid if referenceFrame is ECEF
        float y() const { return vec_1; }
        void y(float y) { vec_1 = y; };

        //API Function: z
        // Only valid if referenceFrame is ECEF
        float z() const { return vec_2; }
        void z(float z) { vec_2 = z; };

        //API Function: north
        // Only valid if referenceFrame is LLH_NED
        float north() const { return vec_0; }
        void north(float north) { vec_0 = north; }

        //API Function: east
        // Only valid if referenceFrame is LLH_NED
        float east() const { return vec_1; }
        void east(float east) { vec_1 = east; }

        //API Function: down
        // Only valid if referenceFrame is LLH_NED
        float down() const { return vec_2; }
        void down(float down) { vec_2 = down; }

    private:
        //API Variable: vec_0, _1, _2
        //  The vector values.
        float vec_0, vec_1, vec_2;
    };

    //API Class: PositionOffset
    //    Represents a position offset (x, y, z).
    class PositionOffset : public GeometricVector
    {
    public:
        PositionOffset(float x_init, float y_init, float z_init, PositionVelocityReferenceFrame ref = PositionVelocityReferenceFrame::ECEF) :
            GeometricVector(x_init, y_init, z_init, ref)
        {}

        PositionOffset() : GeometricVector() {}

        ~PositionOffset() {}
    };

    //API Class: Velocity
    //    Represents a velocity (x, y, z).
    class Velocity : public GeometricVector
    {
    public:
        Velocity(float x_init, float y_init, float z_init, PositionVelocityReferenceFrame ref = PositionVelocityReferenceFrame::ECEF) :
            GeometricVector(x_init, y_init, z_init, ref)
        {}

        Velocity() : GeometricVector() {}

        ~Velocity() {}

    public:
        //API Function: ECEF
        //    Creates a Velocity vectory with the reference frame set to Earth-Centered, Earth-Fixed
        //
        //Parameters:
        //    x_init - initial x coordinate
        //    y_init - initial y coordinate
        //    z_init - initial z coordinate
        static Velocity ECEF(float x_init, float y_init, float z_init) { return Velocity(x_init, y_init, z_init); }

        //API Function: NED
        //    Creates a Velocity vector with the reference frame set to North-East-Down
        //
        //Parameters:
        //    north - initial x coordinate
        //    east - initial y coordinate
        //    down - initial z coordinate
        static Velocity NED(float north, float east, float down) { return Velocity(north, east, down, PositionVelocityReferenceFrame::LLH_NED); }
    };

    //API Typedef: GeometricVectors
    //  A vector of <GeometricVector> objects
    typedef std::vector<GeometricVector> GeometricVectors;

    ///////////////  Position  ///////////////

    //API Struct: Position
    //    Defines a geographic position.
    class Position
    {
    public:
        //API Function: LLH
        //    Creates a Position object with the reference frame set to LLH
        //
        //Parameters:
        //    lat_init - initial latitude
        //    long_init - initial longitude
        //    alt_init - initial altitude
        static Position LLH(double lat_init, double long_init, double alt_init) { return Position(lat_init, long_init, alt_init, PositionVelocityReferenceFrame::LLH_NED); }

        //API Function: ECEF
        //    Creates a Position object with the reference frame set to ECEF
        //
        //Parameters:
        //    x_init - initial x
        //    y_init - initial y
        //    z_init - initial z
        static Position ECEF(double x_init, double y_init, double z_init) { return Position(x_init, y_init, z_init, PositionVelocityReferenceFrame::ECEF); }

        //API Constructor: Position
        //    Creates a Position object.
        //
        //Parameters:
        //    lat_init - initial latitude
        //    long_init - initial longitude
        //    alt_init - initial altitude
        //    ref - reference frame (default: LLH)
        Position(double lat_init, double long_init, double alt_init, PositionVelocityReferenceFrame ref = PositionVelocityReferenceFrame::LLH_NED) :
            position_0(lat_init),
            position_1(long_init),
            position_2(alt_init),
            referenceFrame(ref) {}

        //API Constructor: Position
        //    Creates a zero-filled Position object.
        //    Default reference frame: LLH
        Position() :
            position_0(0),
            position_1(0),
            position_2(0),
            referenceFrame(PositionVelocityReferenceFrame::LLH_NED) {}

        //API Destructor: ~Position
        //    Destroys a TimeUpdate object.
        ~Position() {}

        //API Variable: referenceFrame
        //    The <PositionVelocityReferenceFrame> of this position.
        //    Default: LLH
        PositionVelocityReferenceFrame referenceFrame;

        //API Function: latitude
        // Only valid if referenceFrame is LLH_NED
        double latitude() const { return position_0; }
        void latitude(double latitude) { position_0 = latitude; }

        //API Function: longitude
        // Only valid if referenceFrame is LLH_NED
        double longitude() const { return position_1; }
        void longitude(double longitude) { position_1 = longitude; }

        //API Function: altitude
        // Only valid if referenceFrame is LLH_NED
        double altitude() const { return position_2; }
        void altitude(double altitude) { position_2 = altitude; }

        //API Function: height
        // Only valid if referenceFrame is LLH_NED
        double height() const { return position_2; }
        void height(double height) { position_2 = height; }

        //API Function: x
        // Only valid if referenceFrame is ECEF
        double x() const { return position_0; }
        void x(double x) { position_0 = x; }

        //API Function: y
        // Only valid if referenceFrame is ECEF
        double y() const { return position_1; }
        void y(double y) { position_1 = y; }

        //API Function: z
        // Only valid if referenceFrame is ECEF
        double z() const { return position_2; }
        void z(double z) { position_2 = z; }

    private:
        //API Variable: position_0, _1, _2
        // The position values
        double position_0, position_1, position_2;
    };

    //API Class: GeometricUncertainty
    //    Represents uncertainty values correlating to a position or velocity.
    class GeometricUncertainty : public GeometricVector
    {
    public:
        GeometricUncertainty(float x_init, float y_init, float z_init, const GeometricVector& correlatingValue) :
            GeometricVector(x_init, y_init, z_init, correlatingValue.referenceFrame)
        {}

        GeometricUncertainty(float x_init, float y_init, float z_init, const Position& correlatingValue) :
            GeometricVector(x_init, y_init, z_init, correlatingValue.referenceFrame)
        {}

        GeometricUncertainty(float x_init, float y_init, float z_init, PositionVelocityReferenceFrame ref = PositionVelocityReferenceFrame::ECEF) :
            GeometricVector(x_init, y_init, z_init, ref)
        {}

        GeometricUncertainty() : GeometricVector() {}

        ~GeometricUncertainty() {}
    };
}