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
#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include <QtWidgets/QWidget>
#include <QtGui/QBrush>

QT_BEGIN_NAMESPACE
class QPushButton;
class QComboBox;
QT_END_NAMESPACE

class BrushTool : public QWidget
{
    Q_OBJECT

public:
    explicit BrushTool(QString title, QWidget *parent = 0);
    void setBrush(QBrush brush);
    QBrush brush() const;
    QString name();
    static QString name(const QBrush &brush);

Q_SIGNALS:
    void changed();

public Q_SLOTS:
    void showColorDialog();
    void updateStyle();

private:
    QBrush m_brush;
    QPushButton *m_colorButton;
    QComboBox *m_styleCombo;
};

#endif // BRUSHTOOL_H
