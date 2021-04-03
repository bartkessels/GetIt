#include "gui/widget/BodyWidget/RawBodyTab/RawBodyTabView.hpp"
#include "./ui_RawBodyTabView.h"

using namespace getit::gui::widget::BodyWidget;

RawBodyTabView::RawBodyTabView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::RawBodyTabView())
{
    ui->setupUi(this);

    highlighter = new getit::gui::highlighter::Highlighter(
            ui->rawBody->document()
    );

    connect(ui->highlighting, &QComboBox::currentTextChanged,
        [this](const QString& text) {
            if (text.toLower() == "none") {
                this->highlighter->stopHighlighting();
            } else if (text.toLower() == "json") {
                this->highlighter->startHighlighting(
                    getit::highlighter::JsonHighlighterRules::rules
                );
            } else if (text.toLower() == "xml") {
                this->highlighter->startHighlighting(
                    getit::highlighter::XmlHighlighterRules::rules
                );
            }
        });
}

RawBodyTabView::~RawBodyTabView()
{
    delete ui;
    delete highlighter;
}

std::string RawBodyTabView::getContentType()
{
    return ui->contentType->text().toStdString();
}

std::string RawBodyTabView::getBody()
{
    return ui->rawBody->document()->toPlainText().toStdString();
}

void RawBodyTabView::setContentType(std::string contentType)
{
    ui->contentType->setText(QString::fromStdString(contentType));
}

void RawBodyTabView::setBody(std::string body)
{
    ui->rawBody->document()->setPlainText(QString::fromStdString(body));
}