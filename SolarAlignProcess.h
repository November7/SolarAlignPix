#pragma once
#include <pcl/MetaProcess.h>

namespace pcl
{
	class SolarAlignProcess : public MetaProcess
	{
	public:
		SolarAlignProcess();
		IsoString Id() const override;
		IsoString Category() const override;
		String Description() const override;
		String IconImageSVGFile() const override;	 		
		uint32 Version() const override;
		ProcessInterface* DefaultInterface() const override;
		ProcessImplementation* Create() const override;
		ProcessImplementation* Clone(const ProcessImplementation&) const override;
		bool CanProcessCommandLines() const override;
		int ProcessCommandLine(const StringList&) const override;
	};

	PCL_BEGIN_LOCAL
		extern SolarAlignProcess* TheSolarAlignProcess;
	PCL_END_LOCAL

}  //pcl

