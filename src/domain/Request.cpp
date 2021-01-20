#include "domain/Request.hpp"

using namespace getit::domain;

void Request::registerPipeline(std::shared_ptr<BeforeRequestPipeline> beforePipeline)
{
    this->beforePipelines.push_back(beforePipeline);
}

void Request::registerPipeline(std::shared_ptr<AfterRequestPipeline> afterPipeline)
{
    this->afterPipelines.push_back(afterPipeline);
}

void Request::send()
{
    std::shared_ptr<RequestData> requestData = std::make_shared<RequestData>();

    for (std::shared_ptr<BeforeRequestPipeline> pipeline : this->beforePipelines) {
        pipeline->executeBeforeRequest(requestData);
    }

    std::shared_ptr<Response> response = this->sendRequest(requestData);

    for (std::shared_ptr<AfterRequestPipeline> pipeline : this->afterPipelines) {
        pipeline->executeAfterRequest(response);
    }
}