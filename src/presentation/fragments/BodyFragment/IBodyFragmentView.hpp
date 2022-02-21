#pragma once

#include <memory>
#include <string>

#include "domain/implementations/FormDataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"
#include "presentation/fragments/BodyFragment/BodyType.hpp"

namespace getit::presentation::fragments
{
    struct IBodyFragmentView
    {
        public:
            virtual ~IBodyFragmentView() = default;

            virtual std::shared_ptr<domain::implementations::RawRequestBody> getRawBody() = 0;
            virtual std::shared_ptr<domain::implementations::FormDataRequestBody> getFormDataBody() = 0;
            virtual BodyType getBodyType() = 0;

            virtual void setFormDataBody(const std::shared_ptr<domain::implementations::FormDataRequestBody>& body) = 0;
            virtual void setRawBody(const std::shared_ptr<domain::implementations::RawRequestBody>& body) = 0;
            virtual void setBodyType(const BodyType& bodyType) = 0;
    };
}