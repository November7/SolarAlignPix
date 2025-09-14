#include "SolarAlignInterface.h"
#include "SolarAlignProcess.h"

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
		int labelWidth1 = font.Width(String("Three:"));

		Global_Sizer.SetMargin(5);
		Global_Sizer.SetSpacing(5);

		SampleLabel.SetText("Sample Label: ");
		SampleLabel.SetMinWidth(labelWidth1);
		SampleLabel.SetToolTip("<p>This is the second parameter.</p>");
		SampleLabel.SetTextAlignment(TextAlign::Right | TextAlign::VertCenter);
		
		Global_Sizer.Add(SampleLabel);



		w.SetSizer(Global_Sizer);

		w.EnsureLayoutUpdated();
		//w.AdjustToContents();
		//w.SetFixedSize(1024, 1024);
		w.SetMinSize(400, 300);
		w.SetMaxSize(1024, 1024);

	}
}