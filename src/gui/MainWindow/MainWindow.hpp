#pragma once

#include <memory>
#include <QMainWindow>
#include <string>

#include "domain/AfterRequestPipeline.hpp"
#include "domain/BeforeRequestPipeline.hpp"
#include "domain/Request.hpp"
#include "domain/RequestFactory.hpp"
#include "domain/Response.hpp"

#include "gui/widget/MethodWidget/MethodController.hpp"
#include "gui/widget/MethodWidget/MethodView.hpp"

#include "gui/widget/UriWidget/UriController.hpp"
#include "gui/widget/UriWidget/UriView.hpp"

#include "gui/AfterWidgetController.hpp"
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

        void registerUriView(std::shared_ptr<getit::domain::BeforeRequestPipeline> controller, std::shared_ptr<QWidget> view);
        void registerMethodView(std::shared_ptr<getit::domain::BeforeRequestPipeline> controller, std::shared_ptr<QWidget> view);
        void registerInformationView(std::shared_ptr<getit::domain::BeforeRequestPipeline> controller, std::shared_ptr<QWidget> view, std::string name);
        void registerBodyView(std::shared_ptr<getit::domain::BeforeRequestPipeline> controller, std::shared_ptr<QWidget> view);
        void registerResponseHeadersView(std::shared_ptr<getit::domain::AfterRequestPipeline> controller, std::shared_ptr<QWidget> view);
        void registerResponseBodyView(std::shared_ptr<getit::domain::AfterRequestPipeline> controller, std::shared_ptr<QWidget> view);

    private:
        Ui::MainWindow* ui;
        std::shared_ptr<domain::Request> request;
    };
}
