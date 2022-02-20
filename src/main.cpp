#include <QApplication>
#include <memory>
#include <string>

#include "domain/factories/RequestFactory.hpp"
#include "presentation/windows/MainWindow.hpp"
#include "service/implementations/CppRestRequestService.hpp"

#include <iostream>

int main(int argc, char** args)
{
    const auto& appName = "GetIt";
    QIcon icon(":icons/main");

    const auto& requestFactory = std::make_shared<getit::domain::factories::RequestFactory>();
    const auto& requestServiceFactory = std::make_shared<getit::service::factories::RequestServiceFactory>();

    QApplication app(argc, args);
    QApplication::setWindowIcon(icon);
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

    const auto& window = std::make_shared<getit::presentation::windows::MainWindow>(requestFactory, requestServiceFactory);
    window->show();

    return QApplication::exec();
}