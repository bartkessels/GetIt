#include <QApplication>
#include "gui/MainWindow/MainWindow.hpp"

#include "domain/RequestFactory.hpp"

using namespace getit::domain;

int main(int argc, char** argv)
{
    const auto& appName = "GetIt";
    const auto& requestFactory = std::make_shared<getit::domain::RequestFactory>();

    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":icons/main"));
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

    getit::gui::MainWindow window(requestFactory);
    window.show();

    return QApplication::exec();
}
