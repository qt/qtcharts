// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "view.h"
#include <QtWidgets/QGraphicsWidget>
#include <QtGui/QResizeEvent>
#include <QtCore/QDebug>

View::View(QGraphicsScene *scene, QGraphicsWidget *form , QWidget *parent)
    : QGraphicsView(scene, parent),
      m_form(form)
{
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::resizeEvent(QResizeEvent *event)
{
    if (scene())
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    if (m_form)
        m_form->resize(QSizeF(event->size()));
    QGraphicsView::resizeEvent(event);
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    //BugFix somehow view always eats the mouse move event;
    QGraphicsView::mouseMoveEvent(event);
    event->setAccepted(false);
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    //BugFix somehow view always eats the mouse release event;
    event->setAccepted(false);
}
