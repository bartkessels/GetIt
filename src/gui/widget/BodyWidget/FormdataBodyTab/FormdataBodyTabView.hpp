#pragma once

#include <map>
#include <memory>
#include <QFileDialog>
#include <QPushButton>
#include <QString>
#include <QTreeWidgetItem>
#include <string>

#include "gui/widget/BodyWidget/FormdataBodyTab/IFormdataBodyTabView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class FormdataBodyTabView; }
QT_END_NAMESPACE

namespace getit::gui::widget::BodyWidget
{
    class FormdataBodyTabView: public QWidget, public IFormdataBodyTabView
    {
        public:
            explicit FormdataBodyTabView(QWidget* parent = nullptr);
            ~FormdataBodyTabView() override;

            std::map<std::string, std::string> getElements() override;
            std::map<std::string, std::string> getFiles() override;

            void setElements(std::map<std::string, std::string> elements) override;
            void setFiles(std::map<std::string, std::string> files) override;

        private:
            Ui::FormdataBodyTabView* ui;

            const int elementIndex = 0;
            const int fileIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags rowFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void addElement(std::string element, std::string value);
            void addFile(std::string file, std::string value);

            void removeSelectedElement();
            void removeSelectedFile();
    };
}