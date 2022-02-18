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

    const auto& service = std::make_shared<getit::service::implementations::CppRestRequestService>();
    const auto& requestFactory = std::make_shared<getit::domain::factories::RequestFactory>();

    QApplication app(argc, args);
    QApplication::setWindowIcon(icon);
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

    auto window = new getit::presentation::windows::MainWindow(requestFactory);
    window->show();

    return QApplication::exec();
}