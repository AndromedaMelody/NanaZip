#include "pch.h"

#include "App.h"

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.ShareTarget.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>

#include <Mile.Xaml.h>

#include "../ThirdParty/LZMA/CPP/Common/Common.h"
#include "../SevenZip/CPP/7zip/UI/Common/CompressCall.h"

namespace winrt
{
    using winrt::Windows::ApplicationModel::AppInstance;
    using winrt::Windows::ApplicationModel::Activation::ActivationKind;
    using winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs;
    using winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats;
    using winrt::Windows::ApplicationModel::DataTransfer::ShareTarget::ShareOperation;
    using winrt::Windows::Foundation::Collections::IVectorView;
    using winrt::Windows::Storage::IStorageItem;
    using winrt::Windows::Storage::IStorageItem2;
}


namespace winrt::NanaZip::implementation
{
    App::App()
    {
        ::MileXamlGlobalInitialize();
    }

    void App::Close()
    {
        Exit();
        ::MileXamlGlobalUninitialize();
    }

    void App::OnLaunched(winrt::LaunchActivatedEventArgs const& args)
    {
        UNREFERENCED_PARAMETER(args);
        if (winrt::IActivatedEventArgs e = winrt::AppInstance::GetActivatedEventArgs())
        {
            switch (e.Kind())
            {
            case winrt::ActivationKind::ShareTarget:
                this->OnShareTargetActivated(e.as<winrt::ShareTargetActivatedEventArgs>());
                break;
            default:
                break;
            }
        }
    }

    void App::OnShareTargetActivated(winrt::ShareTargetActivatedEventArgs const& args)
    {
        if (args.ShareOperation().Data().Contains(winrt::StandardDataFormats::StorageItems()))
        {
            winrt::IVectorView<winrt::IStorageItem> items = args.ShareOperation().Data().GetStorageItemsAsync().get();
            UStringVector fileNames;
            for (winrt::IStorageItem const item : items)
            {
                fileNames.Add(item.Path().c_str());
            }
            winrt::IStorageItem2 baseFolder = items.GetAt(0).as<winrt::IStorageItem2>().GetParentAsync().get();

            winrt::check_hresult(::CompressFiles(
                baseFolder.Path().c_str(),
                baseFolder.Name().c_str(),
                L"",
                true,
                fileNames,
                true,
                true,
                false));
        }

        args.ShareOperation().ReportCompleted();
        ::ExitProcess(0);
    }
}
