#pragma once

#include <memory>
#include <QFileDialog>
#include <QMainWindow>

#include "domain/factories/RequestFactory.hpp"
#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"
#include "presentation/tabs/RawRequestTab/RawRequestTabController.hpp"
#include "presentation/tabs/RawRequestTab/RawRequestTabView.hpp"
#include "presentation/tabs/RequestTabView.hpp"

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

        signals:
            // void newTab(std::string tabType);
            // void closeTab(int index);
            // void saveTab(int index);
            // void saveTabAs(int index);

        private:
            void createAndAddNewRawRequestTab();

            std::shared_ptr<domain::factories::RequestFactory> requestFactory;
            Ui::MainWindow* ui;
    };
}