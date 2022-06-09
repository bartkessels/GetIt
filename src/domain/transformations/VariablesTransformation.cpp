#include "domain/transformations/VariablesTransformation.hpp"

using namespace getit::domain::transformations;
using namespace getit::domain::implementations;
using namespace getit::domain::models;

VariablesTransformation::VariablesTransformation(std::list<std::shared_ptr<models::Variable>> variables):
    variables(std::move(variables))
{

}

std::shared_ptr<Request> VariablesTransformation::transform(std::shared_ptr<Request> request)
{
    if (request == nullptr || variables.empty())
        return request;

    for (const auto& variable : variables) {
        request = transformUri(request, variable);
        request = transformHeaders(request, variable);
        request = transformBody(request, variable);
    }

    return request;
}

std::shared_ptr<Request> VariablesTransformation::transformUri(std::shared_ptr<Request> request, const std::shared_ptr<Variable>& variable)
{
    request->setUri(variable->apply(request->getUri()));
    return request;
}

std::shared_ptr<Request> VariablesTransformation::transformHeaders(std::shared_ptr<Request> request, const std::shared_ptr<Variable>& variable)
{
    std::map<std::string, std::string> headers;

    for (const auto& header : request->getHeaders()) {
        headers.insert(transformPair(header, variable));
    }

    request->setHeaders(headers);
    return request;
}

std::shared_ptr<Request> VariablesTransformation::transformBody(const std::shared_ptr<Request>& request, const std::shared_ptr<Variable>& variable)
{
    if (std::dynamic_pointer_cast<FormDataRequestBody>(request->getBody())) {
        request->setBody(transformFormdataBody(std::dynamic_pointer_cast<FormDataRequestBody>(request->getBody()), variable));
    } else if (std::dynamic_pointer_cast<RawRequestBody>(request->getBody())) {
        request->setBody(transformRawRequestBody(std::dynamic_pointer_cast<RawRequestBody>(request->getBody()), variable));
    }

    return request;
}

std::shared_ptr<FormDataRequestBody> VariablesTransformation::transformFormdataBody(std::shared_ptr<FormDataRequestBody> body, const std::shared_ptr<Variable>& variable)
{
    std::map<std::string, std::string> elements;
    std::map<std::string, std::string> files;

    for (const auto& element : body->getElements()) {
        elements.insert(transformPair(element, variable));
    }

    for (const auto& file : body->getFiles()) {
        files.insert(transformPair(file, variable));
    }

    body->setElements(elements);
    body->setFiles(files);

    return body;
}

std::shared_ptr<RawRequestBody> VariablesTransformation::transformRawRequestBody(std::shared_ptr<RawRequestBody> body, const std::shared_ptr<Variable>& variable)
{
    body->setContentType(variable->apply(body->getContentType()));
    body->setBody(variable->apply(body->getBody()));

    return body;
}

std::pair<std::string, std::string> VariablesTransformation::transformPair(const std::pair<std::string, std::string>& pair, const std::shared_ptr<Variable>& variable)
{
    return std::make_pair(
        variable->apply(pair.first),
        variable->apply(pair.second)
    );
}