#pragma once

#include <string>
#include <QComboBox>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class BodyFragmentView; }
QT_END_NAMESPACE

namespace getit::presentation::fragments
{
    class BodyFragmentView : public QWidget
    {
        public:
            explicit BodyFragmentView(QWidget* parent = nullptr);
            ~BodyFragmentView() override;

            std::string getContentType();
            std::string getBody();

//            void setContentType(std::string contentType);

        private:
            Ui::BodyFragmentView* ui;

            const int keyIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags treeItemFlag = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void toggleBody();
            void addDefaultElement();
            void addElement(const std::string& element, const std::string& value);
            void removeSelectedElement();
            void addDefaultFile();
            void addFile(const std::string& fileName, const std::string& filePath);
            void removeSelectedFile();

            void addRowToTreeWidget(const std::string& key, const std::string& value, QTreeWidget* widget);
    };
}