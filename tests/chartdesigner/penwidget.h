/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef PENWIDGET_H
#define PENWIDGET_H

#include <QWidget>
#include <QPen>

class QComboBox;
class QSpinBox;

class PenWidget : public QWidget
{
public:
    explicit PenWidget(QWidget* parent = 0);
    ~PenWidget();

    QPen pen() const { return m_pen; }
private:
    void createContent();
    void createLayout();

private:
    QPen m_pen;
    QComboBox *m_colorComboBox;
    QComboBox *m_lineStyleComboBox;
    QSpinBox *m_widthSpinBox;
};

#endif /* PENWIDGET_H */
