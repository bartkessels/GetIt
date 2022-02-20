#include <memory>
#include <QApplication>

#include "domain/factories/RequestFactory.hpp"
#include "presentation/windows/MainWindow.hpp"
#include "service/factories/RequestServiceFactory.hpp"

using namespace getit;

int main(int argc, char** args)
{
    const auto& appName = "GetIt";
    QIcon icon(":icons/main");

    const auto& requestFactory = std::make_shared<domain::factories::RequestFactory>();
    const auto& requestServiceFactory = std::make_shared<service::factories::RequestServiceFactory>();

    QApplication app(argc, args);
    QApplication::setWindowIcon(icon);
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

    const auto& window = std::make_shared<presentation::windows::MainWindow>(requestFactory, requestServiceFactory);
    window->show();

    return QApplication::exec();
}