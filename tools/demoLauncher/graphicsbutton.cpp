/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
