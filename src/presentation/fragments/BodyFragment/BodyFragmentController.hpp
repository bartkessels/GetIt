#pragma once

#include "domain/models/Request.hpp"
#include "presentation/fragments/FragmentController.hpp"
#include "presentation/fragments/FragmentView.hpp"

namespace getit::presenation::fragments
{
    class BodyFragmentController : public FragmentController<domain::models::Request>
    {
        public:
            explicit BodyFragmentController(BodyFragmentView* view);
    };
}