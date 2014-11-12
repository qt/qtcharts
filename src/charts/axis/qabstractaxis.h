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

#ifndef QABSTRACTAXIS_H
#define QABSTRACTAXIS_H

#include <QtCharts/QChartGlobal>
#include <QtGui/QPen>
#include <QtGui/QFont>
#include <QtCore/QVariant>

QT_CHARTS_BEGIN_NAMESPACE

class QAbstractAxisPrivate;

class QT_CHARTS_EXPORT QAbstractAxis : public QObject
{
    Q_OBJECT
    //visibility
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    //arrow
    Q_PROPERTY(bool lineVisible READ isLineVisible WRITE setLineVisible NOTIFY lineVisibleChanged)
    Q_PROPERTY(QPen linePen READ linePen WRITE setLinePen NOTIFY linePenChanged)
    Q_PROPERTY(QColor color READ linePenColor WRITE setLinePenColor NOTIFY colorChanged)
    //labels
    Q_PROPERTY(bool labelsVisible READ labelsVisible WRITE setLabelsVisible NOTIFY labelsVisibleChanged)
    Q_PROPERTY(QBrush labelsBrush READ labelsBrush WRITE setLabelsBrush NOTIFY labelsBrushChanged)
    Q_PROPERTY(int labelsAngle READ labelsAngle WRITE setLabelsAngle NOTIFY labelsAngleChanged)
    Q_PROPERTY(QFont labelsFont READ labelsFont WRITE setLabelsFont NOTIFY labelsFontChanged)
    Q_PROPERTY(QColor labelsColor READ labelsColor WRITE setLabelsColor NOTIFY labelsColorChanged)
    //grid
    Q_PROPERTY(bool gridVisible READ isGridLineVisible WRITE setGridLineVisible NOTIFY gridVisibleChanged)
    Q_PROPERTY(QPen gridLinePen READ gridLinePen WRITE setGridLinePen NOTIFY gridLinePenChanged)
    //shades
    Q_PROPERTY(bool shadesVisible READ shadesVisible WRITE setShadesVisible NOTIFY shadesVisibleChanged)
    Q_PROPERTY(QColor shadesColor READ shadesColor WRITE setShadesColor NOTIFY shadesColorChanged)
    Q_PROPERTY(QColor shadesBorderColor READ shadesBorderColor WRITE setShadesBorderColor NOTIFY shadesBorderColorChanged)
    Q_PROPERTY(QPen shadesPen READ shadesPen WRITE setShadesPen NOTIFY shadesPenChanged)
    Q_PROPERTY(QBrush shadesBrush READ shadesBrush WRITE setShadesBrush NOTIFY shadesBrushChanged)
    //title
    Q_PROPERTY(QString titleText READ titleText WRITE setTitleText NOTIFY titleTextChanged)
    Q_PROPERTY(QBrush titleBrush READ titleBrush WRITE setTitleBrush NOTIFY titleBrushChanged)
    Q_PROPERTY(bool titleVisible READ isTitleVisible WRITE setTitleVisible NOTIFY titleVisibleChanged)
    Q_PROPERTY(QFont titleFont READ titleFont WRITE setTitleFont NOTIFY titleFontChanged)
    //orientation
    Q_PROPERTY(Qt::Orientation orientation READ orientation)
    //aligment
    Q_PROPERTY(Qt::Alignment alignment READ alignment)

public:

    enum AxisType {
        AxisTypeNoAxis = 0x0,
        AxisTypeValue = 0x1,
        AxisTypeBarCategory = 0x2,
        AxisTypeCategory = 0x4,
        AxisTypeDateTime = 0x8,
        AxisTypeLogValue = 0x10
    };

    Q_DECLARE_FLAGS(AxisTypes, AxisType)

protected:
    explicit QAbstractAxis(QAbstractAxisPrivate &d, QObject *parent = 0);

public:
    ~QAbstractAxis();

    virtual AxisType type() const = 0;

    //visibility handling
    bool isVisible() const;
    void setVisible(bool visible = true);
    void show();
    void hide();

    //arrow handling
    bool isLineVisible() const;
    void setLineVisible(bool visible = true);
    void setLinePen(const QPen &pen);
    QPen linePen() const;
    void setLinePenColor(QColor color);
    QColor linePenColor() const;

    //grid handling
    bool isGridLineVisible() const;
    void setGridLineVisible(bool visible = true);
    void setGridLinePen(const QPen &pen);
    QPen gridLinePen() const;

    //labels handling
    bool labelsVisible() const;
    void setLabelsVisible(bool visible = true);
    void setLabelsBrush(const QBrush &brush);
    QBrush labelsBrush() const;
    void setLabelsFont(const QFont &font);
    QFont labelsFont() const;
    void setLabelsAngle(int angle);
    int labelsAngle() const;
    void setLabelsColor(QColor color);
    QColor labelsColor() const;

    //title handling
    bool isTitleVisible() const;
    void setTitleVisible(bool visible = true);
    void setTitleBrush(const QBrush &brush);
    QBrush titleBrush() const;
    void setTitleFont(const QFont &font);
    QFont titleFont() const;
    void setTitleText(const QString &title);
    QString titleText() const;

    //shades handling
    bool shadesVisible() const;
    void setShadesVisible(bool visible = true);
    void setShadesPen(const QPen &pen);
    QPen shadesPen() const;
    void setShadesBrush(const QBrush &brush);
    QBrush shadesBrush() const;
    void setShadesColor(QColor color);
    QColor shadesColor() const;
    void setShadesBorderColor(QColor color);
    QColor shadesBorderColor() const;

    Qt::Orientation orientation() const;
    Qt::Alignment alignment() const;

    //range handling
    void setMin(const QVariant &min);
    void setMax(const QVariant &max);
    void setRange(const QVariant &min, const QVariant &max);

Q_SIGNALS:
    void visibleChanged(bool visible);
    void linePenChanged(const QPen &pen);
    void lineVisibleChanged(bool visible);
    void labelsVisibleChanged(bool visible);
    void labelsBrushChanged(const QBrush &brush);
    void labelsFontChanged(const QFont &pen);
    void labelsAngleChanged(int angle);
    void gridLinePenChanged(const QPen &pen);
    void gridVisibleChanged(bool visible);
    void colorChanged(QColor color);
    void labelsColorChanged(QColor color);
    void titleTextChanged(const QString &title);
    void titleBrushChanged(const QBrush &brush);
    void titleVisibleChanged(bool visible);
    void titleFontChanged(const QFont &font);
    void shadesVisibleChanged(bool visible);
    void shadesColorChanged(QColor color);
    void shadesBorderColorChanged(QColor color);
    void shadesPenChanged(const QPen &pen);
    void shadesBrushChanged(const QBrush &brush);

protected:
    QScopedPointer<QAbstractAxisPrivate> d_ptr;
    friend class ChartDataSet;
    friend class ChartPresenter;
    friend class ChartThemeManager;
    friend class AbstractDomain;
    friend class ChartAxisElement;
    friend class XYChart;

private:
    Q_DISABLE_COPY(QAbstractAxis)
};

QT_CHARTS_END_NAMESPACE

#endif // QABSTRACTAXIS_H
