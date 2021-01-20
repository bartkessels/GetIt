#include "domain/pipelines/MethodPipeline.hpp"

using namespace getit::domain::pipelines;

MethodPipeline::MethodPipeline(std::string httpMethod):
    httpMethod(httpMethod)
{

}

void MethodPipeline::executeBeforeRequest(std::shared_ptr<RequestData> data)
{
    data->setMethod(this->httpMethod);
}