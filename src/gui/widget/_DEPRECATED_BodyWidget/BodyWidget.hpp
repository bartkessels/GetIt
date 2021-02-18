#pragma once

#include <memory>
#include <QFileDialog>
#include <QWidget>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "domain/body/FormdataRequestBody.hpp"
#include "domain/body/RawRequestBody.hpp"
#include "domain/Request.hpp"
#include "gui/widget/RequestWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class BodyWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class BodyWidget: public QWidget, public RequestWidget
    {
//        Q_OBJECT

    public:
        explicit BodyWidget(QWidget* parent = nullptr);
        ~BodyWidget() override;

        void addToRequest(std::shared_ptr<domain::Request> request) override;

    private:
        Qt::ItemFlags treeWidgetItemFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
        Ui::BodyWidget* ui;

        void connectSignals();
        static std::string generateBoundary();

    private slots:
        void formdataItemsChanged(QTreeWidgetItem*, int);
    };
}