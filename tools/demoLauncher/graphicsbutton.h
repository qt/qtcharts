// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
