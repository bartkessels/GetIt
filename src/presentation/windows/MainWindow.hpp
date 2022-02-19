#pragma once

#include <memory>
#include <QFileDialog>
#include <QMainWindow>
#include <utility>

#include "domain/factories/RequestFactory.hpp"
#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"

#include "presentation/fragments/BodyFragment/BodyFragmentController.hpp"
#include "presentation/fragments/BodyFragment/BodyFragmentView.hpp"
#include "presentation/fragments/HeadersFragment//HeadersFragmentController.hpp"
#include "presentation/fragments/HeadersFragment/HeadersFragmentView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace getit::presentation::windows
{
    class MainWindow: public QMainWindow
    {
        public:
            explicit MainWindow(std::shared_ptr<domain::factories::RequestFactory> requestFactory, QWidget* parent = nullptr);
            ~MainWindow() override;

        private:
            void sendRequest();
            void registerControllers();

            std::shared_ptr<domain::factories::RequestFactory> requestFactory;
            Ui::MainWindow* ui;

            std::shared_ptr<fragments::BodyFragmentController> bodyController;
            std::shared_ptr<fragments::HeadersFragmentController> headersController;
    };
}