#include "SolarAlignInstance.h"


namespace pcl
{
    SolarAlignInstance::SolarAlignInstance(const MetaProcess* m)
        : ProcessImplementation(m)
    {
    }

    // ----------------------------------------------------------------------------

    SolarAlignInstance::SolarAlignInstance(const SolarAlignInstance& x)
        : ProcessImplementation(x)
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
        /*
         * The following flag assumes that your process modifies pixel sample values
         * *exclusively*. If you are going to change anything else, such as image
         * geometry, keywords, etc., or maybe nothing at all (in case you are
         * implementing an image observer process), see the UpdateFlag enumeration
         * in pcl/ImageWindow.h for complete information.
         */
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