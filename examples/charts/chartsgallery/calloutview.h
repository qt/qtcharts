// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CALLOUTVIEW_H
#define CALLOUTVIEW_H

#include <QGraphicsView>

QT_FORWARD_DECLARE_CLASS(QChart)
QT_FORWARD_DECLARE_CLASS(QGraphicsScene)
QT_FORWARD_DECLARE_CLASS(QGraphicsSimpleTextItem)
QT_FORWARD_DECLARE_CLASS(QGraphicsView)
QT_FORWARD_DECLARE_CLASS(QMouseEvent)
QT_FORWARD_DECLARE_CLASS(QResizeEvent)

class Callout;

class CalloutView : public QGraphicsView
{
    Q_OBJECT
public:
    CalloutView(QWidget *parent = nullptr);
    ~CalloutView();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);

private:
    QGraphicsSimpleTextItem *m_coordX = nullptr;
    QGraphicsSimpleTextItem *m_coordY = nullptr;
    QChart *m_chart = nullptr;
    Callout *m_tooltip = nullptr;
    QList<Callout *> m_callouts;
};

#endif
