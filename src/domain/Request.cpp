#include "domain/Request.hpp"

using namespace getit::domain;

void Request::registerPipeline(std::shared_ptr<RequestPipeline> pipeline)
{
    this->pipelines.push_back(pipeline);
}

void Request::send()
{
    std::shared_ptr<RequestData> requestData = std::make_shared<RequestData>();

    for (std::shared_ptr<RequestPipeline> pipeline : this->pipelines) {
        pipeline->executeBeforeRequest(requestData);
    }

    std::shared_ptr<Response> response = this->sendRequest(requestData);

    for (std::shared_ptr<RequestPipeline> pipeline : this->pipelines) {
        pipeline->executeAfterRequest(response);
    }
}