#pragma once

#include <winrt/Windows.ApplicationModel.Activation.h>

#include "App.xaml.g.h"

namespace winrt
{
    using Windows::ApplicationModel::Activation::LaunchActivatedEventArgs;
    using Windows::ApplicationModel::Activation::ShareTargetActivatedEventArgs;
}

namespace winrt::NanaZip::implementation
{
    class App : public AppT<App>
    {
    public:
        App();
        void Close();
        void OnLaunched(winrt::LaunchActivatedEventArgs const& args);
        void OnShareTargetActivated(winrt::ShareTargetActivatedEventArgs const& args);
    };
}
