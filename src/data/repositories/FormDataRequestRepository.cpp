#include "data/repositories/FormDataRequestRepository.hpp"

using namespace getit::data::repositories;

FormDataRequestRepository::FormDataRequestRepository(std::shared_ptr<domain::contracts::RequestFactory> factory):
    factory(std::move(factory))
{

}

void FormDataRequestRepository::saveRequest(const std::string& filePath, std::shared_ptr<domain::models::Request> request)
{
    const auto& requestBody = std::dynamic_pointer_cast<getit::domain::implementations::FormDataRequestBody>(request->getBody());
    auto jsonObject = nlohmann::json::object();

    jsonObject[METHOD_NAME] = request->getMethod();
    jsonObject[URI_NAME] = request->getUri();

    jsonObject[FORM_DATA_BODY_TYPE_NAME] = nlohmann::json::object();
    jsonObject[FORM_DATA_BODY_TYPE_NAME][BOUNDARY_NAME] = requestBody->getBoundary();
    jsonObject[FORM_DATA_BODY_TYPE_NAME][ELEMENTS_ARRAY_NAME] = nlohmann::json::array();
    jsonObject[FORM_DATA_BODY_TYPE_NAME][FILES_ARRAY_NAME] = nlohmann::json::array();

    for (const auto& [key, value] : requestBody->getElements()) {
        auto element = nlohmann::json::object();
        element[KEY_NAME] = key;
        element[ELEMENT_VALUE_NAME] = value;
        jsonObject[FORM_DATA_BODY_TYPE_NAME][ELEMENTS_ARRAY_NAME].push_back(element);
    }

    for (const auto& [key, path] : requestBody->getFiles()) {
        auto file = nlohmann::json::object();
        file[KEY_NAME] = key;
        file[FILE_PATH_NAME] = path;
        jsonObject[FORM_DATA_BODY_TYPE_NAME][FILES_ARRAY_NAME].push_back(file);
    }

    std::ofstream output(filePath);
    output << std::setw(4) << jsonObject << std::endl;
    output.close();
}

std::shared_ptr<getit::domain::models::Request> FormDataRequestRepository::loadRequest(const std::string& filePath)
{
    auto jsonObject = nlohmann::json::object();

    std::ifstream input(filePath);
    input >> jsonObject;
    input.close();

    const auto& method = jsonObject[METHOD_NAME];
    const auto& uri = jsonObject[URI_NAME];
    const auto& boundary = jsonObject[FORM_DATA_BODY_TYPE_NAME][BOUNDARY_NAME];

    std::map<std::string, std::string> elements;
    std::map<std::string, std::string> files;

    for (auto obj : jsonObject[FORM_DATA_BODY_TYPE_NAME][ELEMENTS_ARRAY_NAME]) {
        elements.emplace(obj[KEY_NAME], obj[ELEMENT_VALUE_NAME]);
    }

    for (auto obj : jsonObject[FORM_DATA_BODY_TYPE_NAME][FILES_ARRAY_NAME]) {
        files.emplace(obj[KEY_NAME], obj[FILE_PATH_NAME]);
    }

    return this->factory->getRequest(method, uri, elements, files, boundary);
}