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

#include "widget.h"
#include <QtCore/QDir>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QApplication>
#include "graphicsbutton.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(800, 600);

    m_appFolder = QDir(QApplication::applicationDirPath());
#ifdef Q_OS_MAC
    // The executable is inside an application bundle (a folder) on OSX
    m_appFolder.cdUp();
    m_appFolder.cdUp();
    m_appFolder.cdUp();
#endif

    QDir imageFolder = m_appFolder;
    imageFolder.cdUp();
    imageFolder.cdUp();
    imageFolder.cd("src");
    imageFolder.cd("charts");
    imageFolder.cd("doc");
    imageFolder.cd("images");

    // Create push buttons for starting the executables
    QGridLayout* demosLayout = new QGridLayout;

    GraphicsButton *button = new GraphicsButton(imageFolder.absolutePath() + QDir::separator() + "examples_audio.png", m_appFolder, "audio", this);
    demosLayout->addWidget(button, 0, 0);

    button = new GraphicsButton(imageFolder.absolutePath() + QDir::separator() +"examples_callout.png", m_appFolder, "callout", this);
    demosLayout->addWidget(button, 0, 1);

    button = new GraphicsButton(imageFolder.absolutePath() + QDir::separator() +"demo_chartthemes_blue_cerulean.png", m_appFolder, "chartthemes", this);
    demosLayout->addWidget(button, 0, 2);

    button = new GraphicsButton(imageFolder.absolutePath() + QDir::separator() +"examples_nesteddonuts.png", m_appFolder, "nesteddonuts", this);
    demosLayout->addWidget(button, 1, 0);

    button = new GraphicsButton(imageFolder.absolutePath() + QDir::separator() +"examples_zoomlinechart1.png", m_appFolder, "zoomlinechart", this);
    demosLayout->addWidget(button, 1, 1);

    button = new GraphicsButton(imageFolder.absolutePath() + QDir::separator() +"examples_stackedbarchartdrilldown1.png", m_appFolder, "stackedbarchartdrilldown", this);
    demosLayout->addWidget(button, 1, 2);

    button = new GraphicsButton(imageFolder.absolutePath() + QDir::separator() +"piechart_customization.png", m_appFolder, "piechartcustomization", this);
    demosLayout->addWidget(button, 2, 0);

    button = new GraphicsButton(imageFolder.absolutePath() + QDir::separator() +"examples_datetimeaxis.png", m_appFolder, "datetimeaxis", this);
    demosLayout->addWidget(button, 2, 1);

    button = new GraphicsButton(imageFolder.absolutePath() + QDir::separator() +"examples_donutbreakdown.png", m_appFolder, "donutbreakdown", this);
    demosLayout->addWidget(button, 2, 2);

    setLayout(demosLayout);
}

Widget::~Widget()
{
}
