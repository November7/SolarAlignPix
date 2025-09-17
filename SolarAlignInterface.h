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
#include <pcl/ImageView.h>
#include <pcl/PushButton.h>
#include <pcl/NetworkTransfer.h>

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
        bool ValidateProcess(const ProcessImplementation&, String&) const override;
        bool RequiresInstanceValidation() const override;
        bool ImportProcess(const ProcessImplementation&) override;
        void OnLoadImageClicked(Button&, bool);
        bool DownloadImage(const String& , const String& );
        void ShowImage(const String& localPath);
        bool OnDataAvailable(NetworkTransfer& , const void* , fsize_type );


    private:
        SolarAlignInstance m_instance;
        ByteArray downloadedData;
        class GUIData
        {
        public:
            GUIData(SolarAlignInterface&);

            VerticalSizer   Global_Sizer;
            Label           SampleLabel;
            ImageView       ImageDisplay;
			PushButton      LoadImageButton;
            
        };

        GUIData* GUI = nullptr;

    

        friend class GUIData;
    };


    PCL_BEGIN_LOCAL
        extern SolarAlignInterface* TheSolarAlignInterface;
    PCL_END_LOCAL

} //pcl