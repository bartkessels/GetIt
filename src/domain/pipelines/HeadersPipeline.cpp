#include "domain/pipelines/HeadersPipeline.hpp"

using namespace getit::domain::pipelines;

void HeadersPipeline::executeBeforeRequest(std::shared_ptr<RequestData> data)
{
    data->addOrUpdateHeader("test", "test");
}

void HeadersPipeline::executeAfterRequest(std::shared_ptr<Response> response)
{

}
