// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
