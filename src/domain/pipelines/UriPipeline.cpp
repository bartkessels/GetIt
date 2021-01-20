#include "domain/pipelines/UriPipeline.hpp"

using namespace getit::domain::pipelines;

UriPipeline::UriPipeline(std::string uri):
    uri(uri)
{

}

void UriPipeline::executeBeforeRequest(std::shared_ptr<RequestData> data)
{
    data->setUri(this->uri);
}