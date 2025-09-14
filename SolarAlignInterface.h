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
        virtual ~SolarAlignInterface();
        IsoString Id() const override;
        MetaProcess* Process() const override;
        String IconImageSVGFile() const override;
        void ApplyInstance() const override;
        void ResetInstance() override;
        bool Launch(const MetaProcess&, const ProcessImplementation*, bool& dynamic, unsigned& /*flags*/) override;
        ProcessImplementation* NewProcess() const override;
        bool ValidateProcess(const ProcessImplementation&, String& whyNot) const override;
        bool RequiresInstanceValidation() const override;
        bool ImportProcess(const ProcessImplementation&) override;



    private:
        SolarAlignInstance m_instance;

        class GUIData
        {
        public:
            GUIData(SolarAlignInterface&);

            VerticalSizer   Global_Sizer;
            Label           SampleLabel;
            
        };

        GUIData* GUI = nullptr;

    

        friend class GUIData;
    };


    PCL_BEGIN_LOCAL
        extern SolarAlignInterface* TheSolarAlignInterface;
    PCL_END_LOCAL

} //pcl