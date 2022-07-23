#pragma once

#include <memory>

#include "presentation/states/RequestState.hpp"
#include "presentation/windows/IMainWindowViewModel.hpp"

namespace getit::presentation::windows
{
    struct IMainWindow
    {
        public:
            virtual ~IMainWindow() = default;

            virtual void setViewModel(std::shared_ptr<IMainWindowViewModel> viewModel) = 0;
            virtual void updateState(std::shared_ptr<states::RequestState> state) = 0;
    };
}