#include "SolarAlignInterface.h"
#include "SolarAlignProcess.h"

namespace pcl
{

	SolarAlignInterface* TheSolarAlignInterface = nullptr;

	SolarAlignInterface::SolarAlignInterface() : m_instance(TheSolarAlignProcess)
	{
		TheSolarAlignInterface = this;
	}
}