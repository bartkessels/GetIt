#include "domain/pipelines/HeadersPipeline.hpp"

using namespace getit::domain::pipelines;


void HeadersPipeline::addHeader(std::string header, std::string value)
{
    this->headers.insert({header, value});
}

void HeadersPipeline::removeHeader(std::string header)
{
    this->headers.erase(header);
}

void HeadersPipeline::executeBeforeRequest(std::shared_ptr<RequestData> data)
{
    for (auto const& [header, value] : this->headers) {
        data->addOrUpdateHeader(header, value);
    }
}
