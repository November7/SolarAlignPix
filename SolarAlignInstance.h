#pragma once

//#include <pcl/MetaParameter.h> // pcl_bool, pcl_enum

#include <pcl/ProcessImplementation.h>

namespace pcl
{
    class SolarAlignInstance :
        public ProcessImplementation
    {
    public:
        SolarAlignInstance(const MetaProcess*);
        SolarAlignInstance(const SolarAlignInstance&);

        void Assign(const ProcessImplementation&) override;
        UndoFlags UndoMode(const View&) const override;
        bool CanExecuteOn(const View&, pcl::String& whyNot) const override;
        bool ExecuteOn(View&) override;
        void* LockParameter(const MetaParameter*, size_type tableRow) override;
        bool AllocateParameter(size_type sizeOrLength, const MetaParameter* p, size_type tableRow) override;
        size_type ParameterLength(const MetaParameter* p, size_type tableRow) const override;
    };

} //pcl