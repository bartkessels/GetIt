#pragma once

#include <memory>

#include "domain/models/Response.hpp"
#include "presentation/fragments/ResponseFragment/IResponseFragmentView.hpp"
#include "presentation/fragments/FragmentController.hpp"

namespace getit::presentation::fragments
{
    class ResponseFragmentController : public FragmentController<std::shared_ptr<domain::models::Response>>
    {
        public:
            explicit ResponseFragmentController(IResponseFragmentView* view);
            ~ResponseFragmentController() override;

            std::shared_ptr<domain::models::Response> getContent() override;
            void setContent(std::shared_ptr<domain::models::Response> content) override;

        private:
            IResponseFragmentView* view;
    };
}