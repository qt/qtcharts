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

#ifndef WINDOW_H
#define WINDOW_H
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
class QGraphicsGridLayout;
class Chart;

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QChart;
QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE


class Window: public QMainWindow
{
    Q_OBJECT
    enum State { NoState = 0, ZoomState, ScrollState};
public:
    explicit Window(const QVariantHash& parameters, QWidget *parent = 0);
    ~Window();

private Q_SLOTS:
    void updateUI();
    void handleGeometryChanged();
private:
    QComboBox *createThemeBox();
    QComboBox *createAnimationBox();
    QComboBox *createLegendBox();
    QComboBox *createTempleteBox();
    void connectSignals();
    void createProxyWidgets();
    void comboBoxFocused(QComboBox *combox);
    inline void checkAnimationOptions();
    inline void checkLegend();
    inline void checkOpenGL();
    inline void checkTheme();
    inline void checkState();
    inline void checkTemplate();
    QMenu *createMenu();
    void handleMenu(QChart *chart);
    QAction *createMenuAction(QMenu *menu, const QIcon &icon, const QString &text, const QVariant &data);
    void initializeFromParamaters(const QVariantHash& parameters);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QGraphicsScene *m_scene;
    View *m_view;
    QHash<QString, QGraphicsProxyWidget *> m_widgetHash;
    QHash<QChart *, int> m_chartHash;
    DataTable m_dataTable;

    QGraphicsWidget *m_form;
    QComboBox *m_themeComboBox;
    QCheckBox *m_antialiasCheckBox;
    QComboBox *m_animatedComboBox;
    QComboBox *m_legendComboBox;
    QComboBox *m_templateComboBox;
    QCheckBox *m_openGLCheckBox;
    QCheckBox *m_zoomCheckBox;
    QCheckBox *m_scrollCheckBox;
    QPoint m_origin;
    QGraphicsRectItem *m_rubberBand;
    QGraphicsGridLayout *m_baseLayout;
    QMenu *m_menu;
    State m_state;
    State m_currentState;
    int m_template;

    friend class ComboBox;
};

class ComboBox: public QComboBox
{
public:
    ComboBox(Window *window, QWidget *parent = 0): QComboBox(parent), m_window(window)
    {}

protected:
    void focusInEvent(QFocusEvent *e) {
        QComboBox::focusInEvent(e);
        m_window->comboBoxFocused(this);
    }
private:
    Window *m_window;
};

#endif
