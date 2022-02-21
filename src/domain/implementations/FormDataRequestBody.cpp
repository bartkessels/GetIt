#include "domain/implementations/FormDataRequestBody.hpp"

using namespace getit::domain::implementations;

FormDataRequestBody::FormDataRequestBody(std::string boundary):
    boundary(std::move(boundary))
{

}

void FormDataRequestBody::addElement(std::string key, std::string value)
{
    this->elements.insert({key, value});
}

void FormDataRequestBody::addFile(std::string key, std::string filePath)
{
    this->files.insert({key, filePath});
}

void FormDataRequestBody::setBoundary(std::string boundary)
{
    this->boundary = boundary;
}

void FormDataRequestBody::setElements(std::map<std::string, std::string> elements)
{
    this->elements = elements;
}

void FormDataRequestBody::setFiles(std::map<std::string, std::string> files)
{
    this->files = files;
}

std::string FormDataRequestBody::getBoundary()
{
    return this->boundary;
}

std::map<std::string, std::string> FormDataRequestBody::getElements()
{
    return this->elements;
}

std::map<std::string, std::string> FormDataRequestBody::getFiles()
{
    return this->files;
}

std::string FormDataRequestBody::getBody()
{
    const auto& elementsBody = this->getElementsBody();
    const auto& filesBody = this->getFilesBody();

    boost::format frmt = boost::format(
        BODY_WITH_BOUNDARY_TEMPLATE
    ) % elementsBody % filesBody % this->boundary;

    return frmt.str();
}

std::string FormDataRequestBody::getContentType()
{
    boost::format frmt = boost::format(
        CONTENT_TYPE_TEMPLATE
    ) % this->boundary;

    return frmt.str();
}

std::string FormDataRequestBody::getElementsBody()
{
    std::string body;

    for (const auto& [key, value] : this->elements) {
        boost::format frmt = boost::format(
            ELEMENT_TEMPLATE
        ) % this->boundary % key % value;

        body += frmt.str();
    }

    return body;
}

std::string FormDataRequestBody::getFilesBody()
{
    std::string body;

    for (const auto& [key, filePath] : this->files) {

        std::ifstream inputFileStream(filePath);
        std::string fileContents(
            (std::istreambuf_iterator<char>(inputFileStream)),
            (std::istreambuf_iterator<char>())
        );
        
        boost::format frmt = boost::format(
            FILE_TEMPLATE
        ) % this->boundary % key % filePath % fileContents;

        body += frmt.str();
    }

    return body;
}