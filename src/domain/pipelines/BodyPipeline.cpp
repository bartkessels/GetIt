#include "domain/pipelines/BodyPipeline.hpp"

using namespace getit::domain::pipelines;

BodyPipeline::BodyPipeline(std::shared_ptr<RequestBody> body):
    body(body)
{
    
}

void BodyPipeline::executeBeforeRequest(std::shared_ptr<RequestData> data)
{
    if (this->body != nullptr) {
        data->setBody(body);
    }
}

void BodyPipeline::executeAfterRequest(std::shared_ptr<Response> response)
{

}