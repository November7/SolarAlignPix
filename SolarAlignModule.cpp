#include "SolarAlignModule.h"
#include "SolarAlignProcess.h"
#include "SolarAlignInterface.h"




#define MODULE_VERSION_MAJOR     0
#define MODULE_VERSION_MINOR     0
#define MODULE_VERSION_REVISION  1
#define MODULE_VERSION_BUILD     1
#define MODULE_VERSION_LANGUAGE  eng

namespace pcl
{
	SolarAlignModule::SolarAlignModule() {}

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

	String SolarAlignModule::Author() const
	{
		
		return "Nov7";
	}

	// Rejestracja modu³u
	PCL_MODULE_EXPORT int InstallPixInsightModule(int mode)
	{
		new pcl::SolarAlignModule;

		if (mode == pcl::InstallMode::FullInstall)
		{
			new pcl::SolarAlignProcess;
			//new pcl::SolarAlignInterface;
		}
		
		return 0;
	}



}	 //pcl