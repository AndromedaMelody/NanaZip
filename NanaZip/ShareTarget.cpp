#include "ShareTarget.h"

#include <Windows.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.ShareTarget.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>

#include "../SevenZip/CPP/Common/Common.h"
#include "../SevenZip/CPP/7zip/UI/Common/CompressCall.h"

namespace winrt
{
    using winrt::Windows::ApplicationModel::AppInstance;
    using winrt::Windows::ApplicationModel::Activation::ActivationKind;
    using winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs;
    using winrt::Windows::ApplicationModel::Activation::ShareTargetActivatedEventArgs;
    using winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats;
    using winrt::Windows::ApplicationModel::DataTransfer::ShareTarget::ShareOperation;
    using winrt::Windows::Foundation::Collections::IVectorView;
    using winrt::Windows::Storage::IStorageItem;
    using winrt::Windows::Storage::IStorageItem2;
}

bool NanaZip::FileManager::ShareTarget::Handel()
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);

    winrt::IActivatedEventArgs activatedArgs = winrt::AppInstance::GetActivatedEventArgs();
    if (activatedArgs)
    {
        switch (activatedArgs.Kind())
        {
        case winrt::ActivationKind::ShareTarget:
            winrt::ShareOperation shareOperation = activatedArgs.as<winrt::ShareTargetActivatedEventArgs>().ShareOperation();
            if (shareOperation.Data().Contains(winrt::StandardDataFormats::StorageItems()))
            {
                winrt::IVectorView<winrt::IStorageItem> items = shareOperation.Data().GetStorageItemsAsync().get();

                UStringVector fileNames;
                for (winrt::IStorageItem const item : items)
                {
                    fileNames.Add(item.Path().c_str());
                }
                
                winrt::IStorageItem2 baseFolder = items.GetAt(0).as<winrt::IStorageItem2>().GetParentAsync().get();

                CompressFiles(
                    baseFolder.Path().c_str(),
                    baseFolder.Name().c_str(),
                    L"zip",
                    true,
                    fileNames,
                    true,
                    true,
                    false);
            }
            shareOperation.ReportCompleted();
            return true;
        }
    }
    return false;
}
