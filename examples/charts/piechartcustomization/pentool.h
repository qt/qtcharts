// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#ifndef PENTOOL_H
#define PENTOOL_H

#include <QtWidgets/QWidget>
#include <QtGui/QPen>

QT_BEGIN_NAMESPACE
class QPushButton;
class QDoubleSpinBox;
class QComboBox;
QT_END_NAMESPACE

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
