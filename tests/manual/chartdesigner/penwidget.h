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

#ifndef PENWIDGET_H
#define PENWIDGET_H

#include <QtWidgets/QWidget>
#include <QtGui/QPen>

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
