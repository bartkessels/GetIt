#include "domain/body/FormdataRequestBody.hpp"

using namespace getit::domain::body;

FormdataRequestBody::FormdataRequestBody(std::string boundary):
    boundary(std::move(boundary))
{

}

void FormdataRequestBody::addElement(const std::string& key, const std::string& value)
{
    this->body.push_back(
        this->buildContentData(key, value)
    );
}

void FormdataRequestBody::addFile(const std::string& key, const std::string& filePath)
{
    std::ifstream inputFileStream(filePath);
    std::string value(
        (std::istreambuf_iterator<char>(inputFileStream)),
        (std::istreambuf_iterator<char>())
    );
    
    this->body.push_back(
        this->buildContentDataFile(key, filePath, value)
    );
}

std::string FormdataRequestBody::getContentType()
{
    boost::format frmt = boost::format(
        "multipart/form-data; boundary=\"%1%\""
    ) % this->boundary;

    return frmt.str();
}

std::string FormdataRequestBody::getBody()
{
    if (this->body.empty()) {
        return "";
    }

    std::string body;

    for (auto const& value: this->body) {
        body += value;
    }

    auto frmt = boost::format(
        "%1%\r\n--%2%--\r\n"
    ) % body % this->boundary;

    return frmt.str();
}

size_t FormdataRequestBody::getSize()
{
    return this->getBody().size();
}

std::string FormdataRequestBody::buildContentData(const std::string& key, const std::string& value)
{
    boost::format frmt = boost::format(
        "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"\r\n\r\n%3%\r\n"
    ) % this->boundary % key % value;

    return frmt.str();
}

std::string FormdataRequestBody::buildContentDataFile(const std::string& key, const std::string& fileName, const std::string& contents)
{
    boost::format frmt = boost::format(
        "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"; filename=\"%3%\"\r\n\r\n%4%\r\n"
    ) % this->boundary % key % fileName % contents;

    return frmt.str();
}
