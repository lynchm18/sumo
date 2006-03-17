#ifndef MSVehicleType_H
#define MSVehicleType_H
/***************************************************************************
                          MSVehicleType.h  -  Base Class for Vehicle
                          parameters.
                             -------------------
    begin                : Mon, 12 Mar 2001
    copyright            : (C) 2001 by ZAIK http://www.zaik.uni-koeln.de/AFS
    author               : Christian Roessel
    email                : roessel@zpr.uni-koeln.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
// $Log$
// Revision 1.13  2006/03/17 09:01:12  dkrajzew
// .icc-files removed
//
// Revision 1.12  2005/10/07 11:37:45  dkrajzew
// THIRD LARGE CODE RECHECK: patched problems on Linux/Windows configs
//
// Revision 1.11  2005/09/22 13:45:51  dkrajzew
// SECOND LARGE CODE RECHECK: converted doubles and floats to SUMOReal
//
// Revision 1.10  2005/09/15 11:10:46  dkrajzew
// LARGE CODE RECHECK
//
// Revision 1.9  2004/11/23 10:20:11  dkrajzew
// new detectors and tls usage applied; debugging
//
// Revision 1.8  2004/07/02 09:26:24  dkrajzew
// classes prepared to be derived
//
// Revision 1.7  2003/10/17 06:52:01  dkrajzew
// acceleration is now time-dependent
//
// Revision 1.6  2003/07/30 10:02:38  dkrajzew
// support for the vehicle display removed by now
//
// Revision 1.5  2003/05/27 18:40:49  roessel
// Removed superfluous const.
//
// Revision 1.4  2003/05/20 09:31:47  dkrajzew
// emission debugged; movement model reimplemented (seems ok); detector output
// debugged; setting and retrieval of some parameter added
//
// Revision 1.3  2003/02/07 10:41:51  dkrajzew
// updated
//
// Revision 1.2  2002/10/16 16:39:03  dkrajzew
// complete deletion within destructors implemented; clear-operator added for
// container; global file include
//
// Revision 1.1  2002/10/16 14:48:26  dkrajzew
// ROOT/sumo moved to ROOT/src
//
// Revision 1.4  2002/07/31 17:33:01  roessel
// Changes since sourceforge cvs request.
//
// Revision 1.4  2002/07/31 14:41:05  croessel
// New methods return often used precomputed values.
//
// Revision 1.3  2002/05/29 17:06:04  croessel
// Inlined some methods. See the .icc files.
//
// Revision 1.2  2002/04/11 15:25:56  croessel
// Changed SUMOReal to SUMOReal.
//
// Revision 1.1.1.1  2002/04/08 07:21:24  traffic
// new project name
//
// Revision 2.0  2002/02/14 14:43:20  croessel
// Bringing all files to revision 2.0. This is just cosmetics.
//
// Revision 1.9  2002/02/13 10:10:20  croessel
// Added two static methods: minDecel() and maxLength(). They are needed
// to calculate safe gaps in the case no predecessor resp. successor is
// known.
//
// Revision 1.8  2002/02/05 13:51:53  croessel
// GPL-Notice included.
// In *.cpp files also config.h included.
//
// Revision 1.7  2002/02/01 13:57:07  croessel
// Changed methods and members bmax/dmax/sigma to more meaningful names
// accel/decel/dawdle.
//
// Revision 1.6  2001/12/20 14:53:34  croessel
// using namespace std replaced by std::
// Copy-ctor and assignment-operator moved to private.
//
// Revision 1.5  2001/11/15 17:12:14  croessel
// Outcommented the inclusion of the inline *.iC files. Currently not
// needed.
//
// Revision 1.4  2001/11/14 11:45:54  croessel
// Resolved conflicts which appeared during suffix-change and
// CR-line-end commits.
//
// Revision 1.3  2001/09/06 15:37:06  croessel
// Set default values in the constructor.
//
// Revision 1.2  2001/07/16 12:55:47  croessel
// Changed id type from unsigned int to string. Added string-pointer dictionaries and dictionary methods.
//
// Revision 1.1.1.1  2001/07/11 15:51:13  traffic
// new start
//
/* =========================================================================
 * compiler pragmas
 * ======================================================================= */
#pragma warning(disable: 4786)


/* =========================================================================
 * included modules
 * ======================================================================= */
#ifdef HAVE_CONFIG_H
#ifdef WIN32
#include <windows_config.h>
#else
#include <config.h>
#endif
#endif // HAVE_CONFIG_H

#include <map>
#include <string>
#include <utils/common/SUMOTime.h>


/* =========================================================================
 * class declarations
 * ======================================================================= */
class MSLane;


/* =========================================================================
 * class definitions
 * ======================================================================= */
/**
 */
class MSVehicleType
{
public:

    // !!!
    friend class MSVehicle;

    /// Constructor.
    MSVehicleType( std::string id, SUMOReal length, SUMOReal maxSpeed,
                   SUMOReal accel = 0.8, SUMOReal decel = 4.5, SUMOReal dawdle = 0.5 );

    /// Destructor.
    virtual ~MSVehicleType();

    /// Get vehicle type's length [m].
    SUMOReal length() const {
        return myLength;
    }

    /// Get vehicle type's maximum speed [m/s].
    SUMOReal maxSpeed() const {
        return myMaxSpeed;
    }

    /// Get the vehicle type's maximum acceleration [m/s^2]
    SUMOReal accel(SUMOReal v) const {
        return (SUMOReal) (myAccel * (1.0 - (v/myMaxSpeed)));
    }

    /// Get the vehicle type's maximum deceleration [m/s^2]
    SUMOReal decel() const {
        return myDecel;
    }

    /// Get the vehicle type's dawdle-probability. Out of [0,1]
    SUMOReal dawdle() const {
        return myDawdle;
    }

    /// Returns the minimum deceleration-ability of all vehicle-types.
    static SUMOReal minDecel() {
        return myMinDecel;
    }

    /// Returns the maximum length of all vehicle-types.
    static SUMOReal maxLength() {
        return myMaxLength;
    }

    /// Returns precomputed accel * deltaT
    SUMOReal accelSpeed( SUMOReal v ) const {
        return (SUMOReal) (ACCEL2SPEED(myAccel * (1.0 - (v/(myMaxSpeed*2.0)))));
    }

    /// Returns precomputed decel * deltaT
    SUMOReal decelSpeed( void ) const {
        return myDecelSpeed;
    }

    /// Returns precomputed ( accel + decel ) * deltaT
    SUMOReal accelPlusDecelSpeed( SUMOReal v ) const {
	    return ACCEL2SPEED( accel(v) + myDecel );
    //    return myAccelPlusDecelSpeed;
    }

    /// Returns precomputed 1 / ( 2 * decel )
    SUMOReal inversTwoDecel( void ) const {
        return myInversTwoDecel;
    }

    /// Returns precomputed accel * deltaT^2
    SUMOReal accelDist( SUMOReal v ) const {
        return ACCEL2DIST(accel(v));
    }

    /// Returns precomputed decel * deltaT^2
    SUMOReal decelDist( void ) const {
        return myDecelDist;
    }

    /** Inserts a MSVehicleType into the static dictionary and returns true
        if the key id isn't already in the dictionary. Otherwise returns
        false. */
    static bool dictionary( std::string id, MSVehicleType* edge);

    /** Returns the MSVehicleType associated to the key id if exists,
        otherwise returns 0. */
    static MSVehicleType* dictionary( std::string id);

    static MSVehicleType* dict_Random();

    /** Clears the dictionary */
    static void clear();

    /// returns the name of the vehicle type
    const std::string &id() const;

private:
    /// Unique ID.
    std::string myID;

    /// Vehicle type's length [m].
    SUMOReal myLength;

    /// Vehicle type's maximum speed [m/s].
    SUMOReal myMaxSpeed;

    /// The vehicle type's maximum acceleration [m/s^2]
    SUMOReal myAccel;

    /// The vehicle type's maximum deceleration [m/s^2]
    SUMOReal myDecel;

    /// The vehicle type's dawdle-parameter. 0 for no dawdling, 1 for max.
    SUMOReal myDawdle;


//    SUMOReal myAccelSpeed;
    SUMOReal myDecelSpeed;
//    SUMOReal myAccelPlusDecelSpeed;
    SUMOReal myInversTwoDecel;
//    SUMOReal myAccelDist;
    SUMOReal myDecelDist;

    /// Minimum deceleration-ability of all vehicle-types.
    static SUMOReal myMinDecel;

    /// Maximum length of all vehicle-types.
    static SUMOReal myMaxLength;

    /// Definition of the type of the static dictionary to associate string-ids with objects.
    typedef std::map< std::string, MSVehicleType* > DictType;
    /// Static dictionary to associate string-ids with objects.
    static DictType myDict;

    /// Default constructor.
    MSVehicleType();

    /// Copy constructor.
    MSVehicleType( const MSVehicleType& );

    /// Assignment operator.
    MSVehicleType& operator=( const MSVehicleType& );

};


/**************** DO NOT DECLARE ANYTHING AFTER THE INCLUDE ****************/

#endif

// Local Variables:
// mode:C++
// End:
