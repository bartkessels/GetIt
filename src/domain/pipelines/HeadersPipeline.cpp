#include "domain/pipelines/HeadersPipeline.hpp"

using namespace getit::domain::pipelines;


void HeadersPipeline::addHeader(std::string header, std::string value)
{
    this->headers.push_back(
        std::make_pair(header, value)
    );
}

void HeadersPipeline::executeBeforeRequest(std::shared_ptr<RequestData> data)
{
    for (auto const& [header, value] : this->headers) {
        data->addHeader(header, value);
    }
}
