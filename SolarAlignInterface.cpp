#include "SolarAlignInterface.h"
#include "SolarAlignProcess.h"



#include <pcl/NetworkTransfer.h>
#include <pcl/ImageView.h>
#include <pcl/ImageVariant.h>
#include <pcl/ImageWindow.h>
#include <pcl/FileFormat.h>
#include <pcl/FileFormatInstance.h>
#include <pcl/AutoPointer.h>
#include <pcl/Console.h>
#include <pcl/File.h>
#include <pcl/Bitmap.h>


namespace pcl
{

	SolarAlignInterface* TheSolarAlignInterface = nullptr;

	SolarAlignInterface::SolarAlignInterface() : m_instance(TheSolarAlignProcess)
	{
		TheSolarAlignInterface = this;
	}


	SolarAlignInterface::~SolarAlignInterface()
	{
		if (GUI != nullptr)
		{
			delete GUI;
			GUI = nullptr;
		}
			
	}

	// ----------------------------------------------------------------------------

	IsoString SolarAlignInterface::Id() const
	{
		return "SolarAlign";
	}

	// ----------------------------------------------------------------------------

	MetaProcess* SolarAlignInterface::Process() const
	{
		return TheSolarAlignProcess;
	}

	// ----------------------------------------------------------------------------

	String SolarAlignInterface::IconImageSVGFile() const
	{
		return "";
	}

	// ----------------------------------------------------------------------------

	void SolarAlignInterface::ApplyInstance() const
	{
		m_instance.LaunchOnCurrentView();
	}

	// ----------------------------------------------------------------------------

	void SolarAlignInterface::ResetInstance()
	{
		SolarAlignInstance defaultInstance(TheSolarAlignProcess);
		ImportProcess(defaultInstance);
	}

	// ----------------------------------------------------------------------------

	bool SolarAlignInterface::Launch(const MetaProcess& P, const ProcessImplementation*, bool& dynamic, unsigned& /*flags*/)
	{
		if (GUI == nullptr)
		{
			GUI = new GUIData(*this);
			SetWindowTitle("Solar Align Tool");
			//UpdateControls();
		}

		dynamic = false;
		return &P == TheSolarAlignProcess;
	}

	// ----------------------------------------------------------------------------

	ProcessImplementation* SolarAlignInterface::NewProcess() const
	{
		return new SolarAlignInstance(m_instance);
	}

	// ----------------------------------------------------------------------------

	bool SolarAlignInterface::ValidateProcess(const ProcessImplementation& p, String& whyNot) const
	{
		if (dynamic_cast<const SolarAlignInstance*>(&p) != nullptr)
			return true;
		whyNot = "Not a SolarAlign instance.";
		return false;
	}

	// ----------------------------------------------------------------------------

	bool SolarAlignInterface::RequiresInstanceValidation() const
	{
		return true;
	}

	// ----------------------------------------------------------------------------

	bool SolarAlignInterface::ImportProcess(const ProcessImplementation& p)
	{
		m_instance.Assign(p);
		//UpdateControls();
		return true;
	}


/*************************************************************************************/
	SolarAlignInterface::GUIData::GUIData(SolarAlignInterface& w)
	{
		pcl::Font font = w.Font();
		int labelWidth1 = font.Width(String("---------------------"));

		Global_Sizer.SetMargin(5);
		Global_Sizer.SetSpacing(5);

		SampleLabel.SetText("Sample Label: ");
		SampleLabel.SetMinWidth(labelWidth1);
		SampleLabel.SetToolTip("<p>This is the second parameter.</p>");
		SampleLabel.SetTextAlignment(TextAlign::Right | TextAlign::VertCenter);



		String url = "https://sdo.gsfc.nasa.gov/assets/img/browse/2025/05/02/20250502_000000_1024_HMIIC.jpg";

		LoadImageButton.SetText("Click me");
		LoadImageButton.SetToolTip("Kliknij, aby pobraæ i wyœwietliæ obraz.");
		LoadImageButton.OnClick((Button::click_event_handler)&SolarAlignInterface::OnLoadImageClicked, w);






		ImageDisplay.SetFixedHeight(400);
		ImageDisplay.SetFixedWidth(400);	
		

		Global_Sizer.Add(SampleLabel);
		Global_Sizer.Add(LoadImageButton);
		
		Global_Sizer.Add(ImageDisplay);


		w.SetSizer(Global_Sizer);

		w.EnsureLayoutUpdated();
		w.SetMinSize(400, 300);
		w.SetMaxSize(1024, 1024);

	}
	void SolarAlignInterface::OnLoadImageClicked(Button& sender, bool checked)
	{
		String url = "https://sdo.gsfc.nasa.gov/assets/img/browse/2025/05/02/20250502_000000_1024_HMIIC.jpg";

		String tempPath = File::SystemTempDirectory() + "/temp_image.jpg";
		
		Console().WriteLn("Download image.");
		
		if (DownloadImage(url, tempPath))
		{
			Console().WriteLn("Image downloaded.Loading into ImageView...");
			ShowImage(tempPath);
		}
		else
		{
			Console().WriteLn("Failed to download image.");
		}


	}

	bool SolarAlignInterface::DownloadImage(const String& url, const String& localPath)
	{
		pcl::NetworkTransfer net;
		net.SetURL(url);
		if (!net.Download())
			return false;

		// Zapisz dane do pliku
		File file(localPath, FileMode::Create);
		//file.Write(net.Data(), net.DataLength());
		file.Close();

		return true;
	}

	void SolarAlignInterface::ShowImage(const String& localPath)
	{
		

	}





}