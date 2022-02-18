#pragma once

#include <string>
#include <QWidget>

#include "presentation/fragments/FragmentView.hpp"

namespace getit::presentation::fragments
{
    class BodyFragmentView : public FragmentView, public QWidget
    {
        public:
            explicit BodyFragmentView(QWidget* parent = nullptr);

            std::string getMethod();
            std::string getUri();
            std::string getContentType();
            std::string getBody();
    };
}