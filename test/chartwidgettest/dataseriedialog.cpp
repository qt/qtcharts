#include "dataseriedialog.h"
#include <QDialogButtonBox>
#include <QAbstractButton>
#include <QDebug>

DataSerieDialog::DataSerieDialog(QWidget *parent) :
    QDialog(parent)
{
    QDialogButtonBox *addSeriesBox = new QDialogButtonBox(Qt::Vertical, this);
    addSeriesBox->addButton("Line", QDialogButtonBox::AcceptRole);
    addSeriesBox->addButton("Area", QDialogButtonBox::AcceptRole);
    addSeriesBox->addButton("Bar", QDialogButtonBox::AcceptRole);
    addSeriesBox->addButton("Pie", QDialogButtonBox::AcceptRole);
    addSeriesBox->addButton("Scatter", QDialogButtonBox::AcceptRole);
    addSeriesBox->addButton("Spline", QDialogButtonBox::AcceptRole);
    connect(addSeriesBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(addSeries(QAbstractButton *)));
    this->setFixedSize(addSeriesBox->sizeHint());
}

void DataSerieDialog::addSeries(QAbstractButton *button)
{
    addSeries(button->text().toAscii());
    accept();
}
