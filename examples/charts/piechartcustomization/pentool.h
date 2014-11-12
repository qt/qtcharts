/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/
#ifndef PENTOOL_H
#define PENTOOL_H

#include <QtWidgets/QWidget>
#include <QtGui/QPen>

class QPushButton;
class QDoubleSpinBox;
class QComboBox;

class PenTool : public QWidget
{
    Q_OBJECT

public:
    explicit PenTool(QString title, QWidget *parent = 0);
    void setPen(const QPen &pen);
    QPen pen() const;
    QString name();
    static QString name(const QPen &pen);

Q_SIGNALS:
    void changed();

public Q_SLOTS:
    void showColorDialog();
    void updateWidth(double width);
    void updateStyle(int style);
    void updateCapStyle(int index);
    void updateJoinStyle(int index);

private:
    QPen m_pen;
    QPushButton *m_colorButton;
    QDoubleSpinBox *m_widthSpinBox;
    QComboBox *m_styleCombo;
    QComboBox *m_capStyleCombo;
    QComboBox *m_joinStyleCombo;
};

#endif // PENTOOL_H
