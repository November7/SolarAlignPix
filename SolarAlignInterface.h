#pragma once

#include "SolarAlignInstance.h"

#include <pcl/CheckBox.h>
#include <pcl/ComboBox.h>
#include <pcl/Edit.h>
#include <pcl/Label.h>
#include <pcl/NumericControl.h>
#include <pcl/ProcessInterface.h>
#include <pcl/Sizer.h>
#include <pcl/SpinBox.h>

namespace pcl
{
    class SolarAlignInterface : public ProcessInterface
    {
    public:
		SolarAlignInterface();

    private:
        SolarAlignInstance m_instance;
    };


    PCL_BEGIN_LOCAL
        extern SolarAlignInterface* TheSolarAlignInterface;
    PCL_END_LOCAL

} //pcl