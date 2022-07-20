#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include <map>
#include <memory>
#include <string>

#include "data/contracts/RequestRepositoryFactory.hpp"

#include "domain/contracts/RequestFactory.hpp"

#include "domain/models/Request.hpp"
#include "domain/models/RequestBody.hpp"

#include "presentation/windows/IMainWindow.hpp"
#include "presentation/windows/MainWindowViewModel.hpp"

#include "service/contracts/RequestServiceFactory.hpp"

using namespace getit;
using namespace getit::presentation::windows;

class RequestFactoryMock: public getit::domain::contracts::RequestFactory
{
    public:
        MAKE_MOCK3(getRequest, std::shared_ptr<getit::domain::models::Request>(const std::string&, const std::string&, std::map<std::string, std::string>), override);
        MAKE_MOCK4(getRequest, std::shared_ptr<getit::domain::models::Request>(const std::string&, const std::string&, std::map<std::string, std::string>, const std::string&), override);
        MAKE_MOCK5(getRequest, std::shared_ptr<getit::domain::models::Request>(const std::string&, const std::string&, std::map<std::string, std::string>, const std::string&, const std::string&), override);
        MAKE_MOCK6(getRequest, std::shared_ptr<getit::domain::models::Request>(const std::string&, const std::string&, std::map<std::string, std::string>, std::map<std::string, std::string>, std::map<std::string, std::string>, const std::string&), override);
};

class RequestServiceFactoryMock: public getit::service::contracts::RequestServiceFactory
{
    public:
        MAKE_MOCK0(getRequestService, std::shared_ptr<RequestService>(), override);
};

class RequestRepositoryFactoryMock: public getit::data::contracts::RequestRepositoryFactory
{
    public:
        MAKE_MOCK0(getRepository, std::shared_ptr<RequestRepository>(), override);
};

class MainWindowMock: public IMainWindow
{
    public:
        MAKE_MOCK1(setViewModel, void(std::shared_ptr<IMainWindowViewModel>), override);
        MAKE_MOCK1(updateState, void(std::shared_ptr<presentation::states::RequestState>), override);
};

const auto& requestFactory = std::make_shared<RequestFactoryMock>();
const auto& requestServiceFactory = std::make_shared<RequestServiceFactoryMock>();
const auto& requestRepositoryFactory = std::make_shared<RequestRepositoryFactoryMock>();

TEST_CASE("MainWindowViewModel.openRequest")
{
    SECTION("updates the state to FileOpened")
    {
        // Arrange
        const auto& view = std::make_shared<MainWindowMock>();

        const auto& sut = std::make_unique<MainWindowViewModel>(requestFactory, requestServiceFactory,
                                                                requestRepositoryFactory, view);

        const auto& expectedRequest = std::make_shared<Request>();
        expectedRequest->setMethod("PUT");
        expectedRequest->setUri("://success");

        // Act
        sut->openRequest("");

        // Assert
    }
}

// Open request ->
//  updates the state to FileOpened
//  updates the state to Error when an exception is thrown

// Save request ->
//  builds the request using the request factory and adds the body to the request
//  saves the built request to the specified location
//  updates the state to Error when an exception is thrown

// Send request ->
//  updates the state to Sending when the request hasn't been sent
//  builds the request using the request factory and adds the body to the request
//  updates the state to Sent when the request is sent
//  updates the state to Error when an exception is thrown