// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "graphicsbutton.h"
#include <QtGui/QPainter>
#include <QtCore/QProcess>
#include <QtGui/QMouseEvent>

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
