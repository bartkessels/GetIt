#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include <future>
#include <map>
#include <memory>
#include <string>

#include "data/contracts/RequestRepositoryFactory.hpp"
#include "data/exceptions/NoAvailableRepositoryException.hpp"

#include "domain/contracts/RequestFactory.hpp"

#include "domain/models/Request.hpp"
#include "domain/models/RequestBody.hpp"

#include "presentation/windows/IMainWindow.hpp"
#include "presentation/windows/MainWindowViewModel.hpp"

#include "service/contracts/RequestService.hpp"
#include "service/contracts/RequestServiceFactory.hpp"

using namespace getit;
using namespace getit::presentation;
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
        MAKE_MOCK0(getRequestService, std::shared_ptr<getit::service::contracts::RequestService>(), override);
};

class RequestServiceMock: public getit::service::contracts::RequestService
{
    public:
        MAKE_MOCK1(send, std::future<std::shared_ptr<getit::domain::models::Response>>(std::shared_ptr<getit::domain::models::Request>), override);
};

class RequestRepositoryFactoryMock: public getit::data::contracts::RequestRepositoryFactory
{
    public:
        MAKE_MOCK0(getRepository, std::shared_ptr<RequestRepository>(), override);
};

class RequestRepositoryMock: public getit::data::contracts::RequestRepository
{
    public:
        MAKE_MOCK2(saveRequest, void(const std::string&, std::shared_ptr<Request>), override);
        MAKE_MOCK1(loadRequest, std::shared_ptr<Request>(const std::string&), override);
};

class MainWindowStub: public IMainWindow
{
    public:
        std::shared_ptr<states::RequestState> state;

        void setViewModel(std::shared_ptr<IMainWindowViewModel>) override {}
        void updateState(std::shared_ptr<states::RequestState> state) override {
            this->state = state;
        }
};

TEST_CASE("MainWindowViewModel.openRequest")
{
    auto requestFactory = std::make_shared<RequestFactoryMock>();
    auto requestServiceFactory = std::make_shared<RequestServiceFactoryMock>();
    auto requestRepositoryFactory = std::make_shared<RequestRepositoryFactoryMock>();

    SECTION("updates the state to FileOpened")
    {
        // Arrange
        auto view = std::make_shared<MainWindowStub>();
        auto requestService = std::make_shared<RequestServiceMock>();
        auto requestRepository = std::make_shared<RequestRepositoryMock>();

        const auto& sut = std::make_unique<MainWindowViewModel>(requestFactory, requestServiceFactory,
                                                                requestRepositoryFactory, view);

        auto expectedRequest = std::make_shared<Request>();
        expectedRequest->setMethod("PUT");
        expectedRequest->setUri("://success");

        ALLOW_CALL(*requestServiceFactory, getRequestService()).RETURN(requestService);
        ALLOW_CALL(*requestRepositoryFactory, getRepository()).RETURN(requestRepository);
        ALLOW_CALL(*requestRepository, loadRequest(trompeloeil::_)).RETURN(expectedRequest);

        // Act
        sut->openRequest("");

        // Assert
        REQUIRE(std::dynamic_pointer_cast<presentation::states::FileOpened>(view->state));

        const auto& actualState = std::dynamic_pointer_cast<presentation::states::FileOpened>(view->state);
        REQUIRE(actualState->request->getMethod() == expectedRequest->getMethod());
        REQUIRE(actualState->request->getUri() == expectedRequest->getUri());
    }

    SECTION("updates the state to Error when an exception is thrown")
    {
        // Arrange
        auto view = std::make_shared<MainWindowStub>();
        auto requestService = std::make_shared<RequestServiceMock>();
        auto requestRepository = std::make_shared<RequestRepositoryMock>();

        const auto& sut = std::make_unique<MainWindowViewModel>(requestFactory, requestServiceFactory,
                                                                requestRepositoryFactory, view);

        ALLOW_CALL(*requestServiceFactory, getRequestService()).RETURN(requestService);
        ALLOW_CALL(*requestRepositoryFactory, getRepository()).RETURN(requestRepository);
        ALLOW_CALL(*requestRepository, loadRequest(trompeloeil::_))
            .THROW(data::exceptions::NoAvailableRepositoryException());

        // Act
        sut->openRequest("");

        // Assert
        REQUIRE(std::dynamic_pointer_cast<presentation::states::Error>(view->state));

        const auto& actualState = std::dynamic_pointer_cast<presentation::states::Error>(view->state);
        REQUIRE(actualState->message == data::exceptions::NoAvailableRepositoryException::message);
    }
}

TEST_CASE("MainWindowViewModel.saveRequest")
{
    const auto& requestFactory = std::make_shared<RequestFactoryMock>();
    const auto& requestServiceFactory = std::make_shared<RequestServiceFactoryMock>();
    const auto& requestRepositoryFactory = std::make_shared<RequestRepositoryFactoryMock>();

    const auto& requestService = std::make_shared<RequestServiceMock>();
    const auto& requestRepository = std::make_shared<RequestRepositoryMock>();

    ALLOW_CALL(*requestServiceFactory, getRequestService()).RETURN(requestService);
    ALLOW_CALL(*requestRepositoryFactory, getRepository()).RETURN(requestRepository);

    SECTION("builds the request using the request factory and adds the body to the request")
    {
        // Arrange
        auto view = std::make_shared<MainWindowStub>();
        auto requestService = std::make_shared<RequestServiceMock>();
        auto requestRepository = std::make_shared<RequestRepositoryMock>();

        const auto& sut = std::make_unique<MainWindowViewModel>(requestFactory, requestServiceFactory,
                                                                requestRepositoryFactory, view);

        auto expectedRequest = std::make_shared<Request>();
        expectedRequest->setMethod("PUT");
        expectedRequest->setUri("://success");

        ALLOW_CALL(*requestServiceFactory, getRequestService()).RETURN(requestService);
        ALLOW_CALL(*requestRepositoryFactory, getRepository()).RETURN(requestRepository);
        ALLOW_CALL(*requestRepository, loadRequest(trompeloeil::_)).RETURN(expectedRequest);

        // Assert
        REQUIRE_CALL(*requestFactory, getRequest(
                expectedRequest->getMethod(),
                expectedRequest->getUri(),
                expectedRequest->getHeaders())
        ).RETURN(expectedRequest);

        REQUIRE_CALL(*requestRepository, saveRequest(trompeloeil::_, expectedRequest));

        // Act
        sut->saveRequest(
                expectedRequest->getMethod(),
                expectedRequest->getUri(),
                expectedRequest->getHeaders(),
                expectedRequest->getBody(),
                "./save-location/request.getit");
    }

    SECTION("updates the state to Error when an exception is thrown")
    {
        // Arrange
        auto view = std::make_shared<MainWindowStub>();
        auto requestService = std::make_shared<RequestServiceMock>();
        auto requestRepository = std::make_shared<RequestRepositoryMock>();

        const auto& sut = std::make_unique<MainWindowViewModel>(requestFactory, requestServiceFactory,
                                                                requestRepositoryFactory, view);

        ALLOW_CALL(*requestServiceFactory, getRequestService()).RETURN(requestService);
        ALLOW_CALL(*requestRepositoryFactory, getRepository()).RETURN(requestRepository);
        ALLOW_CALL(*requestFactory, getRequest(trompeloeil::_, trompeloeil::_, trompeloeil::_))
            .RETURN(std::make_shared<domain::models::Request>());
        ALLOW_CALL(*requestRepository, saveRequest(trompeloeil::_, trompeloeil::_))
            .THROW(data::exceptions::NoAvailableRepositoryException());

        // Act
        sut->saveRequest("", "", {}, nullptr, "");

        // Assert
        REQUIRE(std::dynamic_pointer_cast<presentation::states::Error>(view->state));

        const auto& actualState = std::dynamic_pointer_cast<presentation::states::Error>(view->state);
        REQUIRE(actualState->message == data::exceptions::NoAvailableRepositoryException::message);
    }
}

TEST_CASE("MainWindowViewModel.sendRequest")
{
    const auto &requestFactory = std::make_shared<RequestFactoryMock>();
    const auto &requestServiceFactory = std::make_shared<RequestServiceFactoryMock>();
    const auto &requestRepositoryFactory = std::make_shared<RequestRepositoryFactoryMock>();

    const auto &requestService = std::make_shared<RequestServiceMock>();
    const auto &requestRepository = std::make_shared<RequestRepositoryMock>();

    ALLOW_CALL(*requestServiceFactory, getRequestService()).RETURN(requestService);
    ALLOW_CALL(*requestRepositoryFactory, getRepository()).RETURN(requestRepository);

    SECTION("builds the request using the request factory and adds the body to the request")
    {
        // Arrange
        auto view = std::make_shared<MainWindowStub>();
        auto requestService = std::make_shared<RequestServiceMock>();
        auto requestRepository = std::make_shared<RequestRepositoryMock>();

        const auto& sut = std::make_unique<MainWindowViewModel>(requestFactory, requestServiceFactory,
                                                                requestRepositoryFactory, view);

        auto expectedRequest = std::make_shared<Request>();
        expectedRequest->setMethod("PUT");
        expectedRequest->setUri("://success");

        ALLOW_CALL(*requestServiceFactory, getRequestService()).RETURN(requestService);
        ALLOW_CALL(*requestRepositoryFactory, getRepository()).RETURN(requestRepository);
        ALLOW_CALL(*requestRepository, loadRequest(trompeloeil::_)).RETURN(expectedRequest);

        // Assert
        REQUIRE_CALL(*requestFactory, getRequest(
                expectedRequest->getMethod(),
                expectedRequest->getUri(),
                expectedRequest->getHeaders())
        ).RETURN(expectedRequest);

        REQUIRE_CALL(*requestService, send(expectedRequest))
            .RETURN(std::async(std::launch::async, [] { return std::make_shared<domain::models::Response>(); }));

        // Act
        sut->sendRequest(
                expectedRequest->getMethod(),
                expectedRequest->getUri(),
                expectedRequest->getHeaders(),
                expectedRequest->getBody());
    }

    SECTION("updates the state to Sent when the request is sent")
    {
        // Arrange
        auto view = std::make_shared<MainWindowStub>();
        auto requestService = std::make_shared<RequestServiceMock>();
        auto requestRepository = std::make_shared<RequestRepositoryMock>();

        const auto& sut = std::make_unique<MainWindowViewModel>(requestFactory, requestServiceFactory,
                                                                requestRepositoryFactory, view);

        auto expectedResponse = std::make_shared<domain::models::Response>();
        expectedResponse->body = "Success!";

        ALLOW_CALL(*requestServiceFactory, getRequestService()).RETURN(requestService);
        ALLOW_CALL(*requestRepositoryFactory, getRepository()).RETURN(requestRepository);
        ALLOW_CALL(*requestFactory, getRequest(trompeloeil::_, trompeloeil::_, trompeloeil::_))
            .RETURN(std::make_shared<domain::models::Request>());
        ALLOW_CALL(*requestService, send(trompeloeil::_))
            .RETURN(std::async(std::launch::async, [expectedResponse] { return expectedResponse; }));

        // Act
        sut->sendRequest("", "", {}, nullptr);

        // Assert
        REQUIRE(std::dynamic_pointer_cast<presentation::states::Sent>(view->state));

        const auto& actualState = std::dynamic_pointer_cast<presentation::states::Sent>(view->state);
        REQUIRE(actualState->response->body == expectedResponse->body);
    }

    SECTION("updates the state to Error when an exception is thrown")
    {
        // Arrange
        auto view = std::make_shared<MainWindowStub>();
        auto requestService = std::make_shared<RequestServiceMock>();
        auto requestRepository = std::make_shared<RequestRepositoryMock>();

        const auto& sut = std::make_unique<MainWindowViewModel>(requestFactory, requestServiceFactory,
                                                                requestRepositoryFactory, view);

        ALLOW_CALL(*requestServiceFactory, getRequestService()).RETURN(requestService);
        ALLOW_CALL(*requestRepositoryFactory, getRepository()).RETURN(requestRepository);
        ALLOW_CALL(*requestFactory, getRequest(trompeloeil::_, trompeloeil::_, trompeloeil::_))
            .RETURN(std::make_shared<domain::models::Request>());
        ALLOW_CALL(*requestService, send(trompeloeil::_))
            .THROW(data::exceptions::NoAvailableRepositoryException());

        // Act
        sut->sendRequest("", "", {}, nullptr);

        // Assert
        REQUIRE(std::dynamic_pointer_cast<presentation::states::Error>(view->state));

        const auto& actualState = std::dynamic_pointer_cast<presentation::states::Error>(view->state);
        REQUIRE(actualState->message == data::exceptions::NoAvailableRepositoryException::message);
    }
}

// Send request ->
//
//  builds the request using the request factory and adds the body to the request
//
//  updates the state to Error when an exception is thrown