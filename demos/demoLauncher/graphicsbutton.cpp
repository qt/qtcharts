#include "graphicsbutton.h"
#include <QPainter>
#include <QProcess>
#include <QMouseEvent>

GraphicsButton::GraphicsButton(const QString& path,  QDir appFolder, const QString& app, QWidget *parent) :
    QWidget(parent),
    m_path(path),
    m_appFolder(appFolder),
    m_app(app)
{
    m_pixmap = QPixmap(path);
}

void GraphicsButton::mousePressEvent(QMouseEvent * event)
{
    QString program = m_appFolder.absolutePath() + QDir::separator() + m_app;
    QProcess *demoApp = new QProcess(this);
    demoApp->start(program);
    event->accept();
}

void GraphicsButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), m_pixmap);
    QWidget::paintEvent(event);
}
