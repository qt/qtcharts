/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef WINDOW_H_
#define WINDOW_H_
#include "model.h"
#include <QMainWindow>
#include <QChartGlobal>
#include <QHash>
#include <QComboBox>

class QCheckBox;
class QGraphicsRectItem;
class QGraphicsScene;
class QGraphicsWidget;
class View;

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QChart;
QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE


class Window: public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private Q_SLOTS:
    void updateUI();
private:
    QComboBox* createThemeBox();
    QComboBox* createAnimationBox();
    QComboBox* createLegendBox();
    void connectSignals();
    void createProxyWidgets();
    void comboBoxFocused(QComboBox *combox);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QGraphicsScene* m_scene;
    View* m_view;
    QHash<QString, QGraphicsProxyWidget*> m_widgetHash;
    QList<QChart*> m_chartList;
    DataTable m_dataTable;

    QGraphicsWidget *m_form;
    QComboBox *m_themeComboBox;
    QCheckBox *m_antialiasCheckBox;
    QComboBox *m_animatedComboBox;
    QComboBox *m_legendComboBox;
    QCheckBox *m_openGLCheckBox;
    QCheckBox *m_zoomCheckBox;
    QCheckBox *m_scrollCheckBox;
    QPoint m_origin;
    QGraphicsRectItem* m_rubberBand;

    bool m_isScrolling;
    bool m_isZooming;
    bool m_scroll;
    bool m_zoom;

    friend class ComboBox;
};

class ComboBox: public QComboBox
{
public:
    ComboBox(Window* window,QWidget *parent = 0):QComboBox(parent),m_window(window)
    {}

protected:
    void focusInEvent(QFocusEvent *e)
    {
        QComboBox::focusInEvent(e);
        m_window->comboBoxFocused(this);
    }
private:
    Window* m_window;
};

#endif
