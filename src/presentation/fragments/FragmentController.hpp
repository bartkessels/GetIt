#pragma once

#include <QWidget>

#include "presentation/fragments/FragmentView.hpp"

namespace getit::presentation::fragments
{
    template<class T>
    struct Fragment
    {
        public:
            explicit Fragment(FragmentView* view = nullptr) = default;
            virtual ~Fragment() = default;

            virtual T getContent() = 0;
            virtual void setContent(T content) = 0;
    };
}