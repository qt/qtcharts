// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef VIEW_H
#define VIEW_H
#include <QtWidgets/QGraphicsView>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QResizeEvent;
QT_END_NAMESPACE

class View: public QGraphicsView
{
public:
    View(QGraphicsScene *scene, QGraphicsWidget *form , QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QGraphicsWidget *m_form;
};

#endif
