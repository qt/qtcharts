/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef DATASERIEDIALOG_H
#define DATASERIEDIALOG_H

#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE
class QGroupBox;
class QCheckBox;
QT_END_NAMESPACE

class DataSerieDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DataSerieDialog(QWidget *parent = 0);

signals:
    void accepted(QString series, int columnCount, int rowCount, QString dataCharacteristics, bool labelsDefined);

public slots:
    void accept();

private:
    QGroupBox *seriesTypeSelector();
    QGroupBox *columnCountSelector();
    QGroupBox *rowCountSelector();
    QGroupBox *dataCharacteristicsSelector();
    void selectRadio(QGroupBox *groupBox, int defaultSelection);
    QString radioSelection(QGroupBox *groupBox);
    QGroupBox *m_seriesTypeSelector;
    QGroupBox *m_columnCountSelector;
    QGroupBox *m_rowCountSelector;
    QCheckBox *m_labelsSelector;
    QGroupBox *m_dataCharacteristicsSelector;
};

#endif // DATASERIEDIALOG_H
