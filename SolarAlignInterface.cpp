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
		String url = "https://sdo.gsfc.nasa.gov/assets/img/latest/latest_1024_0193.jpg";
		//String url = "https://fits.gsfc.nasa.gov/samples/FGSf64y0106m_a1f.fits";

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

	bool SolarAlignInterface::OnDataAvailable(NetworkTransfer& sender, const void* buffer, fsize_type size)
	{
		const uint8* byteBuffer = reinterpret_cast<const uint8*>(buffer);
		int s = 0;
		for (fsize_type i = 0; i < size; ++i,++s)
		{
			downloadedData.Add(byteBuffer[i]);		

		}
		Console().WriteLn(String().Format("%u", s));
		return true;
	}

	bool SolarAlignInterface::DownloadImage(const String& url, const String& localPath)
	{
		NetworkTransfer net;
		net.SetURL(url);

		downloadedData.Clear();

		net.OnDownloadDataAvailable(
			(NetworkTransfer::download_event_handler)&SolarAlignInterface::OnDataAvailable,
			*this
		);

		Console().WriteLn("Starting download...");

		if (!net.Download())
		{
			Console().WriteLn("Download failed.");
			return false;
		}

		Console().WriteLn("Download complete. Saving to disk...");

		try
		{
			File file;
			file.Create(localPath);
			file.Write(downloadedData.Begin(), downloadedData.Length());
			file.Close();
		}
		catch (...)
		{
			Console().WriteLn("Failed to write image to disk.");
			return false;
		}

		return net.Download();
	}

	void SolarAlignInterface::ShowImage(const String& localPath)
	{
		
		ImageWindow imageWindow;
		Array<ImageWindow> windows = ImageWindow::Open(localPath);

		if (!windows.IsEmpty())
			windows[0].Show();
		else
			Console().WriteLn("Failed to open image.");
	}



}