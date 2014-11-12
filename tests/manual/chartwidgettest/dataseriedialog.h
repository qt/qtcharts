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

#ifndef DATASERIEDIALOG_H
#define DATASERIEDIALOG_H

#include <QtWidgets/QDialog>

class QGroupBox;
class QCheckBox;

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
