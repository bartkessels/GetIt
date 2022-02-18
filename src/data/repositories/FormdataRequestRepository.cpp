#include "data/repositories/FormdataRequestRepository.hpp"

using namespace getit::data::repositories;

FormdataRequestRepository::FormdataRequestRepository(std::shared_ptr<domain::contracts::RequestFactory> factory):
    factory(std::move(factory))
{

}

void FormdataRequestRepository::saveRequest(std::string filePath, std::shared_ptr<getit::domain::models::Request> request)
{
    const auto& requestBody = std::dynamic_pointer_cast<getit::domain::implementations::FormdataRequestBody>(request->getBody());
    auto jsonObject = nlohmann::json::object();

    jsonObject[METHOD_NAME] = request->getMethod();
    jsonObject[URI_NAME] = request->getUri();

    jsonObject[BODY_TYPE_NAME] = nlohmann::json::object();
    jsonObject[BODY_TYPE_NAME][BOUNDARY_NAME] = requestBody->getBoundary();
    jsonObject[BODY_TYPE_NAME][ELEMENTS_ARRAY_NAME] = nlohmann::json::array();
    jsonObject[BODY_TYPE_NAME][FILES_ARRAY_NAME] = nlohmann::json::array();

    int elementsIndex = 0;
    int filesIndex = 0;

    for (const auto& [key, value] : requestBody->getElements()) {
        jsonObject[BODY_TYPE_NAME][ELEMENTS_ARRAY_NAME][elementsIndex] = nlohmann::json::object();
        jsonObject[BODY_TYPE_NAME][ELEMENTS_ARRAY_NAME][elementsIndex][KEY_NAME] = key;
        jsonObject[BODY_TYPE_NAME][ELEMENTS_ARRAY_NAME][elementsIndex][ELEMENT_VALUE_NAME] = value;

        elementsIndex++;
    }

    for (const auto& [key, path] : requestBody->getFiles()) {
        jsonObject[BODY_TYPE_NAME][FILES_ARRAY_NAME][filesIndex] = nlohmann::json::object();
        jsonObject[BODY_TYPE_NAME][FILES_ARRAY_NAME][filesIndex][KEY_NAME] = key;
        jsonObject[BODY_TYPE_NAME][FILES_ARRAY_NAME][filesIndex][FILE_PATH_NAME] = path;

        filesIndex++;
    }

    std::ofstream output(filePath);
    output << std::setw(4) << jsonObject << std::endl;
    output.close();
}

std::shared_ptr<getit::domain::models::Request> FormdataRequestRepository::loadRequest(std::string filePath)
{
    auto jsonObject = nlohmann::json::object();

    std::ifstream input(filePath);
    input >> jsonObject;
    input.close();

    const auto& method = jsonObject[METHOD_NAME];
    const auto& uri = jsonObject[URI_NAME];
    const auto& boundary = jsonObject[BOUNDARY_NAME];

    std::map<std::string, std::string> elements;
    std::map<std::string, std::string> files;

    for (auto obj : jsonObject[BODY_TYPE_NAME][ELEMENTS_ARRAY_NAME]) {
        elements.emplace(obj[KEY_NAME], obj[ELEMENT_VALUE_NAME]);
    }

    for (auto obj : jsonObject[BODY_TYPE_NAME][FILES_ARRAY_NAME]) {
        files.emplace(obj[KEY_NAME], obj[FILE_PATH_NAME]);
    }

    return this->factory->getRequest(method, uri, elements, files, boundary);
}