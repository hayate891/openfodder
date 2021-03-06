/*
 *  Cannon Fodder
 *  ------------------------
 *
 *  Copyright (C) 2008-2017 Robert Crossfield
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

enum eMissionGoals {
	eGoal_None = 0,
	eGoal_Kill_All_Enemy = 1,
	eGoal_Destroy_Enemy_Buildings = 2,
	eGoal_Rescue_Hostages = 3,
	eGoal_Protect_Civilians = 4,
	eGoal_Kidnap_Leader = 5,
	eGoal_Destroy_Factory = 6,
	eGoal_Destroy_Computer = 7,
	eGoal_Get_Civilian_Home = 8,
	eGoal_Activate_All_Switches = 9,		// CF2
	eGoal_Rescue_Hostage = 10,				// CF2: The CF2 engine has this as goal 3 instead of 10, and vica versa

	eGoal_End = -1
};

struct sAggression {
	int16 mMin;
	int16 mMax;

	int16 getAverage() const {

		return (mMin + mMax) / 2;
	}
};

struct sMissionCustom {
	std::string mName;
	std::string mAuthor;
};

class cMissionData {
	public:
	std::vector<std::string>				mMissionNames;
	std::vector<size_t>						mMissionPhases;

	std::vector<std::string>				mMapNames;
	std::vector<std::vector<eMissionGoals>> mMapGoals;
	std::vector<sAggression>				mMapAggression;
	std::vector<std::string>				mMapFilenames;

	std::string								mCustomMap;
	sMissionCustom							mCustomMission;

	cMissionData( const std::vector<std::string>& pMissionNames, const std::vector<std::string>& pMissionPhaseNames, const std::vector< size_t >& pMissionPhases, const std::vector< std::vector<eMissionGoals> >& pMapGoals, const std::vector<sAggression>& pEnemyAggression );

	void Clear();

	bool LoadCustomMap( const std::string& pMapName );
	bool LoadCustomMissionSet( const std::string& pMissionSet );

	/**
	 * Get the filename for a map
	 */
	std::string getMapFilename( size_t pMapNumber ) const {

		if (pMapNumber >= mMapFilenames.size()) {

			std::stringstream	filename;

			filename << "mapm" << (pMapNumber + 1);

			return filename.str();
		}

		return mMapFilenames[pMapNumber];
	}

	/**
	 * Get the mission name
	 */
	std::string getMissionName( size_t pMissionNumber ) const {
		// Mission Number is always + 1
		pMissionNumber -= 1;

		if (pMissionNumber >= mMissionNames.size() )
			return mCustomMap;

		return mMissionNames[pMissionNumber ];
	}

	/**
	* Number of phases on this mission
	*/
	uint16 getNumberOfPhases( size_t pMissionNumber ) const {
		// Mission Number is always + 1
		pMissionNumber -= 1;

		if (pMissionNumber >= mMissionPhases.size())
			return 1;

		return (uint16) mMissionPhases[pMissionNumber];
	}

	/**
	 * Get the map name
	 */
	std::string getMapName( const size_t& pMapNumber ) const {

		if (pMapNumber >= mMapNames.size() )
			return mCustomMap;

		return mMapNames[pMapNumber];
	}

	/**
	 * Get the goals for this map
	 */
	const std::vector<eMissionGoals>& getMapGoals( const uint16& pMapNumber ) const {

		if (pMapNumber >= mMapGoals.size())
			return mMapGoals[0];

		return mMapGoals[ pMapNumber ];
	}

	/**
	 * Get the enemy aggression for this map
	 */
	const sAggression& getMapAggression( const uint16& pMapNumber ) const {

		if (pMapNumber >= mMapAggression.size())
			return mMapAggression[0];

		return mMapAggression[ pMapNumber ];
	}

	/** 
	 * Get the number of available maps
	 */
	const size_t getMapCount() const {

		return mMapNames.size();
	}
};

extern const cMissionData	mMissionData_Plus;
extern const cMissionData	mMissionData_AmigaFormat;
extern const cMissionData	mMissionData_Retail;
extern const cMissionData	mMissionData_Retail2;
extern		 cMissionData   mMissionData_Custom;

extern const std::vector<std::string>	mMissionGoal_Titles;
