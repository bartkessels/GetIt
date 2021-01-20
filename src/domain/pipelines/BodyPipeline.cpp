#include "domain/pipelines/BodyPipeline.hpp"

using namespace getit::domain::pipelines;

BodyPipeline::BodyPipeline(std::shared_ptr<RequestBody> body):
    body(body)
{
    if (body == nullptr) {
        throw std::invalid_argument("Body cannot be a nullptr, if you don't have a body don't use the Body Pipeline");
    }
}

void BodyPipeline::executeBeforeRequest(std::shared_ptr<RequestData> data)
{
    if (this->body != nullptr) {
        data->setBody(body);
    }
}
