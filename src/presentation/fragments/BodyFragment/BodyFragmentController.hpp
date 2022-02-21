#pragma once

#include <memory>

#include "domain/models/RequestBody.hpp"
#include "presentation/fragments/BodyFragment/BodyType.hpp"
#include "presentation/fragments/BodyFragment/IBodyFragmentView.hpp"
#include "presentation/fragments/FragmentController.hpp"

namespace getit::presentation::fragments
{
    class BodyFragmentController : public FragmentController<std::shared_ptr<domain::models::RequestBody>>
    {
        public:
            explicit BodyFragmentController(IBodyFragmentView* view);
            ~BodyFragmentController() override;

            std::shared_ptr<domain::models::RequestBody> getContent() override;
            void setContent(std::shared_ptr<domain::models::RequestBody> content) override;

        private:
            IBodyFragmentView* view;
    };
}