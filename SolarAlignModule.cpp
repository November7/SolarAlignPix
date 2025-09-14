#include "SolarAlignModule.h"
#include "SolarAlignProcess.h"
#include "SolarAlignInterface.h"




#define MODULE_VERSION_MAJOR     0
#define MODULE_VERSION_MINOR     0
#define MODULE_VERSION_REVISION  1
#define MODULE_VERSION_BUILD     13
#define MODULE_VERSION_LANGUAGE  eng

#define MODULE_RELEASE_YEAR      2025
#define MODULE_RELEASE_MONTH     9
#define MODULE_RELEASE_DAY       14

namespace pcl
{
	SolarAlignModule::SolarAlignModule() 
	{
	}

	const char* SolarAlignModule::Version() const
	{
		return PCL_MODULE_VERSION(	MODULE_VERSION_MAJOR,
									MODULE_VERSION_MINOR,
									MODULE_VERSION_REVISION,
									MODULE_VERSION_BUILD,
									MODULE_VERSION_LANGUAGE);
	}

	IsoString SolarAlignModule::Name() const
	{
		return "SolarAlign";
	}

	String SolarAlignModule::Description() const
	{
		
		return "PixInsight SolarAlign Process Module";
	}

	// ----------------------------------------------------------------------------

	String SolarAlignModule::Company() const
	{
	
		return "Nov7";
	}

	String SolarAlignModule::Author() const
	{
		
		return "Nov7";
	}

	String SolarAlignModule::Copyright() const
	{
		
		return "Copyright (c) 2025-2025 Nov7";
	}


	String SolarAlignModule::TradeMarks() const
	{
		return "Nov7";
	}

	void SolarAlignModule::GetReleaseDate(int& year, int& month, int& day) const
	{
		year = MODULE_RELEASE_YEAR;
		month = MODULE_RELEASE_MONTH;
		day = MODULE_RELEASE_DAY;
	}


	// Rejestracja modu³u
	PCL_MODULE_EXPORT int InstallPixInsightModule(int mode)
	{
		new pcl::SolarAlignModule;

		if (mode == pcl::InstallMode::FullInstall)
		{
			new pcl::SolarAlignProcess;
			new pcl::SolarAlignInterface;
		}
		
		return 0;
	}



}	 //pcl