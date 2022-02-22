#pragma once

#include <string>
#include <QComboBox>
#include <QFileDialog>
#include <QString>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QWidget>
#include <utility>

#include "domain/implementations/FormDataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"
#include "domain/models/RequestBody.hpp"
#include "presentation/fragments/BodyFragment/BodyType.hpp"
#include "presentation/fragments/BodyFragment/IBodyFragmentView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class BodyFragmentView; }
QT_END_NAMESPACE

namespace getit::presentation::fragments
{
    class BodyFragmentView : public QWidget, public IBodyFragmentView
    {
        Q_OBJECT

        public:
            explicit BodyFragmentView(QWidget* parent = nullptr);
            ~BodyFragmentView() override;

            std::shared_ptr<domain::implementations::RawRequestBody> getRawBody() override;
            std::shared_ptr<domain::implementations::FormDataRequestBody> getFormDataBody() override;
            BodyType getBodyType() override;

            void setFormDataBody(const std::shared_ptr<domain::implementations::FormDataRequestBody>& body) override;
            void setRawBody(const std::shared_ptr<domain::implementations::RawRequestBody>& body) override;
            void setBodyType(const BodyType& bodyType) override;
        
        private slots:
            void toggleBody(int changedIndex);
            void addDefaultElement();
            void addDefaultFile();
            void removeSelectedElement();
            void removeSelectedFile();

        private:
            Ui::BodyFragmentView* ui;

            const int keyIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags treeItemFlag = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void addRowToTreeWidget(const std::string& key, const std::string& value, QTreeWidget* widget);
            std::map<std::string, std::string> getRowsFromTreeWidget(QTreeWidget* widget) const;
    };
}
