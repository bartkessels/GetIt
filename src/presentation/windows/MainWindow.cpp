#include "presentation/windows/MainWindow.hpp"
#include "./ui_MainWindow.h"

#include <iostream>
#include <utility>

using namespace getit::presentation::windows;

MainWindow::MainWindow(std::shared_ptr<getit::domain::factories::RequestFactory> requestFactory, QWidget* parent):
    QMainWindow(parent),
    requestFactory(std::move(std::move(requestFactory))),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    connect(ui->menuItemNewRawRequest, &QAction::triggered,
        this, [this]() {
            this->createAndAddNewRawRequestTab();
        });

    connect(ui->menuItemSave, &QAction::triggered,
        this, [this]() {
            // Retrieve current tab item
//            auto tabItem = this->ui->tabs->getCurrentTab();
            
        });

    connect(ui->tabs, &QTabWidget::tabCloseRequested,
        this, [this](int index) {
            this->ui->tabs->removeTab(index);
        });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createAndAddNewRawRequestTab()
{
    auto tabImplementation = std::make_shared<tabs::RawRequestTabView>();
    auto tab = new tabs::RequestTabView(tabImplementation);
    auto controller = std::make_shared<tabs::RawRequestTabController>(tabImplementation, requestFactory);

    ui->tabs->addTab(tab, "New Raw Request");
}