#include <catch2/catch.hpp>
#include <future>
#include <trompeloeil.hpp>
#include <memory>
#include <utility>

#include "domain/contracts/RequestTransformation.hpp"
#include "domain/contracts/ResponseTransformation.hpp"
#include "domain/models/Request.hpp"
#include "service/implementations/BaseRequestService.hpp"

using namespace getit::domain::contracts;
using namespace getit::domain::models;
using namespace getit::service::implementations;

/**
 * Class to change the uri of a request
 */
class SmallRequestTransformation : public RequestTransformation
{
    public:
        std::string changedUri;

        SmallRequestTransformation(std::string changedUri) : changedUri(std::move(changedUri)) {}

        std::shared_ptr<Request> transform(std::shared_ptr<Request> request) override
        {
            request->setUri(changedUri);
            return request;
        }
};

/**
 * Class to change the body of a response
 */
class SmallResponseTransformation : public ResponseTransformation
{
    public:
        std::string changedBody;

        SmallResponseTransformation(std::string changedBody) : changedBody(std::move(changedBody)) {}

        std::shared_ptr<Response> transform(std::shared_ptr<Response> response) override
        {
            response->body = changedBody;
            return response;
        }
};

class RequestServiceStub: public BaseRequestService
{
    public:
        std::shared_ptr<Request> sentRequest;

    protected:
        std::future<std::shared_ptr<Response>> sendRequest(std::shared_ptr<Request> request) override
        {
            this->sentRequest = request;

            return std::async(std::launch::async, []() {
                return std::make_shared<Response>();
            });
        }
};

TEST_CASE("BaseRequestService.send")
{
    const auto& sut = std::make_shared<RequestServiceStub>();

    SECTION("Applies request transformations to the request before sending")
    {
        // Arrange
        std::string expectedRequestUri = "https://bartkessels.net/changed-uri";
        const auto& requestTransformation = std::make_shared<SmallRequestTransformation>(expectedRequestUri);

        std::list<std::shared_ptr<RequestTransformation>> requestTransformations = {
                requestTransformation
        };

        // Act
        sut->setRequestTransformations(requestTransformations);
        sut->send(std::make_shared<Request>()).get();

        // Assert
        REQUIRE(sut->sentRequest->getUri() == expectedRequestUri);
    }

    SECTION("Applies response transformations to the response before returning the future")
    {
        // Arrange
        std::string expectedResponseBody = "This is my new raw body!";
        const auto& responseTransformation = std::make_shared<SmallResponseTransformation>(expectedResponseBody);

        std::list<std::shared_ptr<ResponseTransformation>> responseTransformations = {
                responseTransformation
        };

        // Act
        sut->setResponseTransformations(responseTransformations);
        const auto& response = sut->send(std::make_shared<Request>()).get();

        // Assert
        REQUIRE(response->body == expectedResponseBody);
    }
}