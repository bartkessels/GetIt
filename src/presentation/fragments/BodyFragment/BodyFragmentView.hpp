#pragma once

#include <string>
#include <QComboBox>
#include <QFileDialog>
#include <QString>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QWidget>
#include <utility>

#include "domain/implementations/FormdataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"
#include "domain/models/RequestBody.hpp"
#include "presentation/fragments/BodyFragment/BodyType.hpp"
#include "presentation/fragments/BodyFragment/IBodyFragmentView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class BodyFragmentView; }
QT_END_NAMESPACE

namespace getit::presentation::fragments
{
    class BodyFragmentView : public IBodyFragmentView, public QWidget
    {
        public:
            explicit BodyFragmentView(QWidget* parent = nullptr);
            ~BodyFragmentView() override;

            std::shared_ptr<domain::implementations::RawRequestBody> getRawBody() override;
            std::shared_ptr<domain::implementations::FormdataRequestBody> getFormDataBody() override;
            BodyType getBodyType() override;

            void setFormDataBody(const std::shared_ptr<domain::implementations::FormdataRequestBody>& body) override;
            void setRawBody(const std::shared_ptr<domain::implementations::RawRequestBody>& body) override;
            void setBodyType(const BodyType& bodyType) override;

        private:
            Ui::BodyFragmentView* ui;

            const int keyIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags treeItemFlag = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void toggleBody();
            void addDefaultElement();
            void removeSelectedElement();
            void addDefaultFile();
            void removeSelectedFile();

            void addRowToTreeWidget(const std::string& key, const std::string& value, QTreeWidget* widget);
            std::map<std::string, std::string> getRowsFromTreeWidget(QTreeWidget* widget) const;
    };
}