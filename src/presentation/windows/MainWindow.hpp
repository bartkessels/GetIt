#pragma once

#include <exception>
#include <memory>
#include <QFileDialog>
#include <QString>
#include <QThread>
#include <QMainWindow>
#include <QMessageBox>
#include <QUrl>
#include <utility>

#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"

#include "presentation/fragments/BodyFragment/BodyFragmentController.hpp"
#include "presentation/fragments/BodyFragment/BodyFragmentView.hpp"
#include "presentation/fragments/HeadersFragment//HeadersFragmentController.hpp"
#include "presentation/fragments/HeadersFragment/HeadersFragmentView.hpp"
#include "presentation/fragments/ResponseFragment/ResponseFragmentController.hpp"
#include "presentation/fragments/ResponseFragment/ResponseFragmentView.hpp"

#include "presentation/states/Error.hpp"
#include "presentation/states/FileOpened.hpp"
#include "presentation/states/RequestState.hpp"
#include "presentation/states/Sending.hpp"
#include "presentation/states/Sent.hpp"

#include "presentation/windows/IMainWindow.hpp"
#include "presentation/windows/IMainWindowViewModel.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace getit::presentation::windows
{
    class MainWindow: public QMainWindow, public IMainWindow
    {
        Q_OBJECT

        public:
            explicit MainWindow(QWidget* parent = nullptr);
            ~MainWindow() override;

            void setViewModel(std::shared_ptr<IMainWindowViewModel> viewModel) override;
            void updateState(std::shared_ptr<states::RequestState> state) override;

        signals:
            void responseReceived(std::shared_ptr<domain::models::Response> response);
            void errorOccurred(const std::string& errorMessage);

        private:
            Ui::MainWindow* ui;
            std::shared_ptr<IMainWindowViewModel> viewModel;
            std::string saveLocation;

            std::shared_ptr<fragments::BodyFragmentController> bodyController;
            std::shared_ptr<fragments::HeadersFragmentController> headersController;
            std::shared_ptr<fragments::ResponseFragmentController> responseController;

            void setRequest(const std::shared_ptr<domain::models::Request>& request);
            void setResponse(const std::shared_ptr<domain::models::Response>& response);

            void sendRequest();
            void registerControllers();
            void saveRequest();
            void saveRequestAs();
            void openRequest();
            void displayErrorMessage(const std::string& errorMessage);
    };
}