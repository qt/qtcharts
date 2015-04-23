/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H

#include <QWidget>
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
