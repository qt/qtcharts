/****************************************************************************
 **
 ** Copyright (C) 2014 Digia Plc
 ** All rights reserved.
 ** For any questions to Digia, please use contact form at http://qt.digia.com
 **
 ** This file is part of the Qt Enterprise Charts Add-on.
 **
 ** $QT_BEGIN_LICENSE$
 ** Licensees holding valid Qt Enterprise licenses may use this file in
 ** accordance with the Qt Enterprise License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Digia.
 **
 ** If you have questions regarding the use of this file, please use
 ** contact form at http://qt.digia.com
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

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
