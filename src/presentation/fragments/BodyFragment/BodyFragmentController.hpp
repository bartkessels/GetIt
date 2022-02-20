#pragma once

#include <memory>

#include "domain/models/RequestBody.hpp"
#include "presentation/fragments/BodyFragment/BodyFragmentView.hpp"
#include "presentation/fragments/FragmentController.hpp"

namespace getit::presentation::fragments
{
    class BodyFragmentController : public FragmentController<std::shared_ptr<domain::models::RequestBody>>
    {
        public:
            explicit BodyFragmentController(BodyFragmentView* view);
            ~BodyFragmentController() override;

            std::shared_ptr<domain::models::RequestBody> getContent() override;
            void setContent(std::shared_ptr<domain::models::RequestBody> content) override;

        private:
            BodyFragmentView* view;
    };
}