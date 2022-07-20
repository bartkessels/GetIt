#pragma once

#include <map>
#include <memory>
#include <string>

#include "data/contracts/RequestRepositoryFactory.hpp"

#include "domain/contracts/RequestFactory.hpp"

#include "domain/models/Request.hpp"
#include "domain/models/RequestBody.hpp"

#include "presentation/states/Error.hpp"
#include "presentation/states/FileOpened.hpp"
#include "presentation/states/RequestState.hpp"
#include "presentation/states/Sending.hpp"
#include "presentation/states/Sent.hpp"

#include "presentation/windows/IMainWindow.hpp"
#include "presentation/windows/IMainWindowViewModel.hpp"

#include "service/contracts/RequestServiceFactory.hpp"

using namespace getit::data::contracts;
using namespace getit::domain::contracts;
using namespace getit::domain::models;
using namespace getit::service::contracts;

namespace getit::presentation::windows
{
    class MainWindowViewModel: public IMainWindowViewModel
    {
        public:
            explicit MainWindowViewModel(
                    std::shared_ptr<RequestFactory> requestFactory,
                    std::shared_ptr<RequestServiceFactory> requestServiceFactory,
                    std::shared_ptr<RequestRepositoryFactory> requestRepositoryFactory,
                    std::shared_ptr<IMainWindow> view);
            ~MainWindowViewModel() override = default;

            void sendRequest(std::string method, std::string uri, std::map<std::string, std::string> headers,
                             std::shared_ptr<RequestBody> body) override;
            void saveRequest(std::string method, std::string uri, std::map<std::string, std::string> headers,
                             std::shared_ptr<RequestBody> body, const std::string& location) override;
            void openRequest(const std::string& location) override;

        private:
            std::shared_ptr<RequestFactory> requestFactory;
            std::shared_ptr<RequestServiceFactory> requestServiceFactory;
            std::shared_ptr<RequestRepositoryFactory> requestRepositoryFactory;
            std::shared_ptr<IMainWindow> view;
    };
}