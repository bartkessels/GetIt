#include <QApplication>
#include <memory>

#include "domain/RequestFactory.hpp"

#include "gui/MainWindow/MainWindow.hpp"
#include "gui/widget/BodyWidget/FormdataBodyTab/FormdataBodyTabController.hpp"
#include "gui/widget/BodyWidget/FormdataBodyTab/FormdataBodyTabView.hpp"
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
#include "gui/widget/ResponseBodyWidget/RawResponseBodyTab/RawResponseBodyTabController.hpp"
#include "gui/widget/ResponseBodyWidget/RawResponseBodyTab/RawResponseBodyTabView.hpp"
#include "gui/widget/ResponseBodyWidget/ResponseBodyController.hpp"
#include "gui/widget/ResponseBodyWidget/ResponseBodyView.hpp"
#include "gui/widget/ResponseHeadersWidget/ResponseHeadersController.hpp"
#include "gui/widget/ResponseHeadersWidget/ResponseHeadersView.hpp"
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
    const auto& formdataView = std::make_shared<getit::gui::widget::BodyWidget::FormdataBodyTabView>(window);
    const auto& formdataController = std::make_shared<getit::gui::widget::BodyWidget::FormdataBodyTabController>(formdataView);

    const auto& rawBodyView = std::make_shared<getit::gui::widget::BodyWidget::RawBodyTabView>(window);
    const auto& rawBodyController = std::make_shared<getit::gui::widget::BodyWidget::RawBodyTabController>(rawBodyView);

    const auto& bodyView = std::make_shared<getit::gui::widget::BodyView>();
    const auto& bodyController = std::make_shared<getit::gui::widget::BodyController>(bodyView);
    
    bodyController->registerTab(formdataController, formdataView, "Formdata");
    bodyController->registerTab(rawBodyController, rawBodyView, "Raw");

    window->registerBodyView(bodyController, bodyView);
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
    const auto& responseHeadersView = std::make_shared<getit::gui::widget::ResponseHeadersView>(window);
    const auto& responseHeadersController = std::make_shared<getit::gui::widget::ResponseHeadersController>(responseHeadersView);
    window->registerResponseHeadersView(responseHeadersController, responseHeadersView);
}

void registerResponseBodyViews(getit::gui::MainWindow* window)
{
    const auto& rawResponseView = std::make_shared<getit::gui::widget::ResponseBodyWidget::RawResponseBodyTabView>();
    const auto& rawResponseController = std::make_shared<getit::gui::widget::ResponseBodyWidget::RawResponseBodyTabController>(rawResponseView);

    const auto& responseBodyView = std::make_shared<getit::gui::widget::ResponseBodyView>();
    const auto& responseBodyController = std::make_shared<getit::gui::widget::ResponseBodyController>(responseBodyView);

    responseBodyController->registerTab(rawResponseController, rawResponseView, "Raw");

    window->registerResponseBodyView(responseBodyController, responseBodyView);
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
    registerResponseBodyViews(&window);
    
    window.show();

    return QApplication::exec();
}
