#include "graphicsbutton.h"
#include <QPainter>
#include <QProcess>
#include <QMouseEvent>

GraphicsButton::GraphicsButton(const QString& path,  QDir appFolder, const QString& app, QWidget *parent) :
    QWidget(parent),
    m_path(path),
    m_appFolder(appFolder),
    m_app(app),
    m_demoApp(0)
{
    m_pixmap = QPixmap(path);
}

GraphicsButton::~GraphicsButton()
{
    if (m_demoApp)
        m_demoApp->close();
}

void GraphicsButton::mousePressEvent(QMouseEvent * event)
{
    QString program = m_appFolder.absolutePath() + QDir::separator() + m_app;
    m_demoApp = new QProcess(this);
    m_demoApp->start(program);
    event->accept();
}

void GraphicsButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), m_pixmap);
    QWidget::paintEvent(event);
}
