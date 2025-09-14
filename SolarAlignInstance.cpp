#include "SolarAlignInstance.h"


#include <pcl/AutoViewLock.h>
#include <pcl/Console.h>
#include <pcl/StandardStatus.h>
#include <pcl/View.h>


namespace pcl
{
    SolarAlignInstance::SolarAlignInstance(const MetaProcess* m) : ProcessImplementation(m)
    {
    }

    // ----------------------------------------------------------------------------

    SolarAlignInstance::SolarAlignInstance(const SolarAlignInstance& x) : ProcessImplementation(x)
    {
        Assign(x);
    }

    // ----------------------------------------------------------------------------

    void SolarAlignInstance::Assign(const ProcessImplementation& p)
    {
        
    }

    // ----------------------------------------------------------------------------

    UndoFlags SolarAlignInstance::UndoMode(const View&) const
    {
        return UndoFlag::PixelData;
    }

    // ----------------------------------------------------------------------------

    bool SolarAlignInstance::CanExecuteOn(const View& view, String& whyNot) const
    {
        if (view.Image().IsComplexSample())
        {
            whyNot = "";
            return false;
        }
        return true;
    }

    // ----------------------------------------------------------------------------
    // ----------------------------------------------------------------------------

    class SolarAlignEngine
    {
    public:

        template <class P>
        static void Apply(GenericImage<P>& image, const SolarAlignInstance& instance)
        {
           
        }
    };

    // ----------------------------------------------------------------------------

    bool SolarAlignInstance::ExecuteOn(View& view)
    {
     
        AutoViewLock lock(view);

        ImageVariant image = view.Image();
        if (image.IsComplexSample())
            return false;

        StandardStatus status;
        image.SetStatusCallback(&status);

        Console().EnableAbort();

        
       

        return true;
    }

    // ----------------------------------------------------------------------------

    void* SolarAlignInstance::LockParameter(const MetaParameter* p, size_type /*tableRow*/)
    {
       

        return nullptr;
    }

    // ----------------------------------------------------------------------------

    bool SolarAlignInstance::AllocateParameter(size_type sizeOrLength, const MetaParameter* p, size_type tableRow)
    {
        

        return true;
    }

    // ----------------------------------------------------------------------------

    size_type SolarAlignInstance::ParameterLength(const MetaParameter* p, size_type tableRow) const
    {

        return 0;
    }
} //pcl