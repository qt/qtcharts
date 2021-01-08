/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H

#include <QtWidgets/QWidget>
#include <QDir>

class QProcess;

class GraphicsButton : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicsButton(const QString &path, QDir appFolder, const QString &app, QWidget *parent = 0);
    ~GraphicsButton();

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QPixmap m_pixmap;
    QString m_path;
    QDir m_appFolder;
    QString m_app;
    QProcess *m_demoApp;
};

#endif // GRAPHICSBUTTON_H
