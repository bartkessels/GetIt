#pragma once

#include <memory>
#include <QFileDialog>
#include <QThread>
#include <QMainWindow>
#include <utility>

#include "domain/contracts/RequestFactory.hpp"
#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"

#include "presentation/fragments/BodyFragment/BodyFragmentController.hpp"
#include "presentation/fragments/BodyFragment/BodyFragmentView.hpp"
#include "presentation/fragments/HeadersFragment//HeadersFragmentController.hpp"
#include "presentation/fragments/HeadersFragment/HeadersFragmentView.hpp"
#include "presentation/fragments/ResponseFragment/ResponseFragmentController.hpp"
#include "presentation/fragments/ResponseFragment/ResponseFragmentView.hpp"

#include "service/contracts/RequestServiceFactory.hpp"

using namespace getit::domain::contracts;
using namespace getit::service::contracts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace getit::presentation::windows
{
    class MainWindow: public QMainWindow
    {
        Q_OBJECT

        public:
            explicit MainWindow(std::shared_ptr<RequestFactory> requestFactory, std::shared_ptr<RequestServiceFactory> requestServiceFactory, QWidget* parent = nullptr);
            ~MainWindow() override;

        signals:
            void responseReceived(std::shared_ptr<domain::models::Response> response);

        private:
            std::shared_ptr<RequestFactory> requestFactory;
            std::shared_ptr<RequestServiceFactory> requestServiceFactory;
            Ui::MainWindow* ui;

            std::shared_ptr<fragments::BodyFragmentController> bodyController;
            std::shared_ptr<fragments::HeadersFragmentController> headersController;
            std::shared_ptr<fragments::ResponseFragmentController> responseController;

            void sendRequest();
            void registerControllers();
    };
}