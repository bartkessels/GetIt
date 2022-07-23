#include "presentation/windows/MainWindowViewModel.hpp"

using namespace getit;
using namespace getit::presentation::windows;

MainWindowViewModel::MainWindowViewModel(
        std::shared_ptr<RequestFactory> requestFactory,
        std::shared_ptr<RequestServiceFactory> requestServiceFactory,
        std::shared_ptr<RequestRepositoryFactory> requestRepositoryFactory,
        std::shared_ptr<IMainWindow> view):
    requestFactory(std::move(requestFactory)),
    requestServiceFactory(std::move(requestServiceFactory)),
    requestRepositoryFactory(std::move(requestRepositoryFactory)),
    view(std::move(view))
{

}

void MainWindowViewModel::sendRequest(std::string method, std::string uri, std::map<std::string, std::string> headers,
                                      std::shared_ptr<RequestBody> body)
{
    this->view->updateState(std::make_shared<states::Sending>());
    const auto& requestService = requestServiceFactory->getRequestService();
    const auto& request = requestFactory->getRequest(method, uri, headers);
    request->setBody(body);

    try
    {
        auto response = requestService->send(request).get();
        this->view->updateState(std::make_shared<states::Sent>(response));
    }
    catch(const std::exception& e)
    {
        this->view->updateState(std::make_shared<states::Error>(e.what()));
    }
}

void MainWindowViewModel::saveRequest(std::string method, std::string uri, std::map<std::string, std::string> headers,
                                      std::shared_ptr<RequestBody> body, const std::string& location)
{
    const auto& repository = requestRepositoryFactory->getRepository();
    const auto& request = requestFactory->getRequest(method, uri, headers);
    request->setBody(body);

    try
    {
        repository->saveRequest(location, request);
    }
    catch(const std::exception& e)
    {
        this->view->updateState(std::make_shared<states::Error>(e.what()));
    }
}

void MainWindowViewModel::openRequest(const std::string& location)
{
    const auto& repository = requestRepositoryFactory->getRepository();

    try
    {
        const auto& request = repository->loadRequest(location);
        view->updateState(std::make_shared<states::FileOpened>(request));
    }
    catch(const std::exception& e) {
        this->view->updateState(std::make_shared<states::Error>(e.what()));
    }
}