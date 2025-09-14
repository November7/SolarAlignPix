#include "SolarAlignProcess.h"
#include "SolarAlignInterface.h"
#include "SolarAlignInstance.h"


#include <pcl/Arguments.h>
#include <pcl/Console.h>
#include <pcl/Exception.h>
#include <pcl/View.h>

namespace pcl
{
	SolarAlignProcess* TheSolarAlignProcess = nullptr;


	SolarAlignProcess::SolarAlignProcess()
	{
		TheSolarAlignProcess = this;
	}

	IsoString SolarAlignProcess::Id() const
	{
		return "SolarAlign";
	}

	IsoString SolarAlignProcess::Category() const
	{
		return IsoString();
	}

	String SolarAlignProcess::Description() const
	{
		return
			"<html>"
			"<p>"
			"SolarAlign: Align solar images based on solar limb detection and rotation correction."
			"</p>"
			"</html>";
	}


	String SolarAlignProcess::IconImageSVGFile() const
	{
		return "";
	}

	uint32 SolarAlignProcess::Version() const
	{
		return 0x101;
	}

	ProcessInterface* SolarAlignProcess::DefaultInterface() const
	{
		return TheSolarAlignInterface;
	}

	ProcessImplementation* SolarAlignProcess::Create() const
	{
		return new SolarAlignInstance(this);
	}

    ProcessImplementation* SolarAlignProcess::Clone(const ProcessImplementation& p) const
    {
        const SolarAlignInstance* instance = dynamic_cast<const SolarAlignInstance*>(&p);
        return (instance != nullptr) ? new SolarAlignInstance(*instance) : nullptr;
    }

    // ----------------------------------------------------------------------------

    bool SolarAlignProcess::CanProcessCommandLines() const
    {
        return true;
    }

    // ----------------------------------------------------------------------------

    static void ShowHelp()
    {
        Console().Write(
            "<raw>"
            "Usage: SolarAlign [<arg_list>] [<view_list>]"
            "\n"
            "\n--interface"
            "\n"
            "\n      Launches the interface of this process."
            "\n"
            "\n--help"
            "\n"
            "\n      Displays this help and exits."
            "</raw>");
    }

    int SolarAlignProcess::ProcessCommandLine(const StringList& argv) const
    {
        ArgumentList arguments = ExtractArguments(argv, ArgumentItemMode::AsViews, ArgumentOption::AllowWildcards);

        SolarAlignInstance instance(this);

        bool launchInterface = false;
        int count = 0;


        if (launchInterface)
            instance.LaunchInterface();
        else if (count == 0)
        {
            if (ImageWindow::ActiveWindow().IsNull())
                throw Error("There is no active image window.");
            instance.LaunchOnCurrentView();
        }

        return 0;
    }

} // pcl