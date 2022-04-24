#include "presentation/windows/VariablesWindow/VariablesWindow.hpp"
#include "./ui_VariablesWindow.h"

using namespace getit::presentation::windows;

VariablesWindow::VariablesWindow(QWidget* parent):
    QDialog(parent),
    ui(new Ui::VariablesWindow())
{
    ui->setupUi(this);
}

VariablesWindow::~VariablesWindow()
{
    delete ui;
}