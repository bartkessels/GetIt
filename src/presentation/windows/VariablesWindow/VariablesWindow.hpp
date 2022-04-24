#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class VariablesWindow; }
QT_END_NAMESPACE

namespace getit::presentation::windows
{
    class VariablesWindow : public QDialog
    {
        Q_OBJECT

        public:
            explicit VariablesWindow(QWidget* parent = nullptr);
            ~VariablesWindow();

        private:
            Ui::VariablesWindow* ui;
    };
}