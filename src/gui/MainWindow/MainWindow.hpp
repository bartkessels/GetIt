#pragma once

#include <boost/format.hpp>
#include <memory>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "domain/Request.hpp"
#include "domain/RequestFactory.hpp"
#include "domain/Response.hpp"

#include "gui/widget/BodyWidget/BodyWidget.hpp"
#include "gui/widget/RequestInfoWidget/RequestInfoWidget.hpp"

// New imports for pipelines:

#include "gui/widget/MethodWidget/MethodController.hpp"
#include "gui/widget/MethodWidget/MethodView.hpp"

#include "gui/widget/UriWidget/UriController.hpp"
#include "gui/widget/UriWidget/UriView.hpp"

#include "gui/BeforeWidgetController.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace getit::gui
{
    class MainWindow: public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(const std::shared_ptr<getit::domain::RequestFactory>& factory, QWidget* parent = nullptr);
        ~MainWindow() override;

        void registerView(std::shared_ptr<getit::gui::BeforeWidgetController> controller, std::shared_ptr<QWidget> view);
        // void registerView(std::shared_ptr<getit::gui::BeforeWidgetController> controller, std:;shared_ptr<QWidget> view);

    private:
        std::shared_ptr<domain::Request> request;
        void connectSignals();
        void connectSendSlot();

        Ui::MainWindow* ui;
        std::shared_ptr<widget::RequestInfoWidget> requestInfoWidget;
        std::shared_ptr<widget::BodyWidget> bodyWidget;

    private slots:
        void setResponse(getit::domain::Response* response);

    signals:
        void requestSent(getit::domain::Response* response);
    };
}