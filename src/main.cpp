#include <QApplication>
#include <memory>

#include "domain/RequestFactory.hpp"

#include "gui/MainWindow/MainWindow.hpp"
#include "gui/widget/BodyWidget/RawBodyTab/RawBodyTabController.hpp"
#include "gui/widget/BodyWidget/RawBodyTab/RawBodyTabView.hpp"
#include "gui/widget/BodyWidget/BodyController.hpp"
#include "gui/widget/BodyWidget/BodyView.hpp"
#include "gui/widget/CookiesWidget/CookiesController.hpp"
#include "gui/widget/CookiesWidget/CookiesView.hpp"
#include "gui/widget/HeadersWidget/HeadersController.hpp"
#include "gui/widget/HeadersWidget/HeadersView.hpp"
#include "gui/widget/MethodWidget/MethodController.hpp"
#include "gui/widget/MethodWidget/MethodView.hpp"
#include "gui/widget/ResponseHeadersWidget/ResponseHeadersController.hpp"
#include "gui/widget/ResponseHeadersWidget/ResponseHeadersView.hpp"
#include "gui/widget/ResponseRawBodyWidget/ResponseRawBodyController.hpp"
#include "gui/widget/ResponseRawBodyWidget/ResponseRawBodyView.hpp"
#include "gui/widget/UriWidget/UriController.hpp"
#include "gui/widget/UriWidget/UriView.hpp"

using namespace getit::domain;

void registerGeneralViews(getit::gui::MainWindow* window)
{    
    const auto& methodView = std::make_shared<getit::gui::widget::MethodView>(window);
    const auto& methodController = std::make_shared<getit::gui::widget::MethodController>(methodView);
    window->registerMethodView(methodController, methodView);

    const auto& uriView = std::make_shared<getit::gui::widget::UriView>(window);
    const auto& uriController = std::make_shared<getit::gui::widget::UriController>(uriView);
    window->registerUriView(uriController, uriView);
}

void registerBodyViews(getit::gui::MainWindow* window)
{
    const auto& rawBodyView = std::make_shared<getit::gui::widget::BodyWidget::RawBodyTabView>(window);
    const auto& rawBodyController = std::make_shared<getit::gui::widget::BodyWidget::RawBodyTabController>(rawBodyView);

    const auto& bodyView = std::make_shared<getit::gui::widget::BodyView>();
    const auto& bodyController = std::make_shared<getit::gui::widget::BodyController>(bodyView);
    bodyController->registerTab(rawBodyController, rawBodyView, "Raw");

    window->registerBodyView(bodyController, bodyView, "Raw Body");
}

void registerInformationViews(getit::gui::MainWindow* window)
{
    const auto& headersView = std::make_shared<getit::gui::widget::HeadersView>(window);
    const auto& headersController = std::make_shared<getit::gui::widget::HeadersController>(headersView);
    window->registerInformationView(headersController, headersView, "Headers");

    const auto& cookiesView = std::make_shared<getit::gui::widget::CookiesView>(window);
    const auto& cookiesController = std::make_shared<getit::gui::widget::CookiesController>(cookiesView);
    window->registerInformationView(cookiesController, cookiesView, "Cookies");
}

void registerAfterRequestViews(getit::gui::MainWindow* window)
{
    const auto& responseHeadersController = std::make_shared<getit::gui::widget::ResponseHeadersController>();
    const auto& responseHeadersView = std::make_shared<getit::gui::widget::ResponseHeadersView>(window);
    window->registerResponseHeadersView(responseHeadersController, responseHeadersView);

    const auto& responseRawBodyController = std::make_shared<getit::gui::widget::ResponseRawBodyController>();
    const auto& responseRawBodyView = std::make_shared<getit::gui::widget::ResponseRawBodyView>(window);
    window->registerResponseBodyView(responseRawBodyController, responseRawBodyView, "Raw Response");
}

int main(int argc, char** argv)
{
    const auto& appName = "GetIt";
    const auto& requestFactory = std::make_shared<getit::domain::RequestFactory>();

    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":icons/main"));
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

    getit::gui::MainWindow window(requestFactory);
    registerGeneralViews(&window);
    registerBodyViews(&window);
    registerInformationViews(&window);
    registerAfterRequestViews(&window);
    
    window.show();

    return QApplication::exec();
}
