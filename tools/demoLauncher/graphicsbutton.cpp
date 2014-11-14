/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "graphicsbutton.h"
#include <QPainter>
#include <QProcess>
#include <QMouseEvent>

GraphicsButton::GraphicsButton(const QString &path,  QDir appFolder, const QString &app, QWidget *parent) :
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

void GraphicsButton::mousePressEvent(QMouseEvent *event)
{
    QString program = m_appFolder.absolutePath() + QDir::separator() + m_app;
    if (m_demoApp) {
        m_demoApp->close();
        delete m_demoApp;
    }
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
