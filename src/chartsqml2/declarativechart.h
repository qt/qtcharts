/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

#ifndef DECLARATIVECHART_H
#define DECLARATIVECHART_H

#include <QtCore/QtGlobal>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickPaintedItem>
#include <QtWidgets/QGraphicsScene>
#include <QtCore/QMutex>

#include <QtCharts/QChart>
#include <QtCore/QLocale>

QT_CHARTS_BEGIN_NAMESPACE

class DeclarativeMargins;
class Domain;
class DeclarativeAxes;

class DeclarativeChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(Theme theme READ theme WRITE setTheme)
    Q_PROPERTY(Animation animationOptions READ animationOptions WRITE setAnimationOptions)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QFont titleFont READ titleFont WRITE setTitleFont)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)
    Q_PROPERTY(QLegend *legend READ legend CONSTANT)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(bool dropShadowEnabled READ dropShadowEnabled WRITE setDropShadowEnabled NOTIFY dropShadowEnabledChanged)
    Q_PROPERTY(qreal backgroundRoundness READ backgroundRoundness WRITE setBackgroundRoundness NOTIFY backgroundRoundnessChanged REVISION 3)
    Q_PROPERTY(qreal topMargin READ topMargin)
    Q_PROPERTY(qreal bottomMargin READ bottomMargin)
    Q_PROPERTY(qreal leftMargin READ leftMargin)
    Q_PROPERTY(qreal rightMargin READ rightMargin)
    Q_PROPERTY(DeclarativeMargins *minimumMargins READ minimumMargins NOTIFY minimumMarginsChanged REVISION 1)
    Q_PROPERTY(DeclarativeMargins *margins READ margins NOTIFY marginsChanged REVISION 2)
    Q_PROPERTY(QRectF plotArea READ plotArea NOTIFY plotAreaChanged REVISION 1)
    Q_PROPERTY(QColor plotAreaColor READ plotAreaColor WRITE setPlotAreaColor NOTIFY plotAreaColorChanged REVISION 3)
    Q_PROPERTY(QQmlListProperty<QAbstractAxis> axes READ axes REVISION 2)
    Q_PROPERTY(bool localizeNumbers READ localizeNumbers WRITE setLocalizeNumbers NOTIFY localizeNumbersChanged REVISION 4)
    Q_PROPERTY(QLocale locale READ locale WRITE setLocale NOTIFY localeChanged REVISION 4)
    Q_ENUMS(Animation)
    Q_ENUMS(Theme)
    Q_ENUMS(SeriesType)

public:
    // duplicating enums from QChart to make the QML api namings 1-to-1 with the C++ api
    enum Theme {
        ChartThemeLight = 0,
        ChartThemeBlueCerulean,
        ChartThemeDark,
        ChartThemeBrownSand,
        ChartThemeBlueNcs,
        ChartThemeHighContrast,
        ChartThemeBlueIcy,
        ChartThemeQt
    };

    enum Animation {
        NoAnimation = 0x0,
        GridAxisAnimations = 0x1,
        SeriesAnimations = 0x2,
        AllAnimations = 0x3
    };

    enum SeriesType {
        SeriesTypeLine,
        SeriesTypeArea,
        SeriesTypeBar,
        SeriesTypeStackedBar,
        SeriesTypePercentBar,
        SeriesTypeBoxPlot,
        SeriesTypePie,
        SeriesTypeScatter,
        SeriesTypeSpline,
        SeriesTypeHorizontalBar,
        SeriesTypeHorizontalStackedBar,
        SeriesTypeHorizontalPercentBar
    };

public:
    DeclarativeChart(QQuickItem *parent = 0);
    ~DeclarativeChart();

public: // From parent classes
    void childEvent(QChildEvent *event);
    void componentComplete();
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void paint(QPainter *painter);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void hoverMoveEvent(QHoverEvent *event);
private Q_SLOTS:
    void handleAntialiasingChanged(bool enable);
    void sceneChanged(QList<QRectF> region);
    void renderScene();

public:
    void setTheme(DeclarativeChart::Theme theme);
    DeclarativeChart::Theme theme();
    void setAnimationOptions(DeclarativeChart::Animation animations);
    DeclarativeChart::Animation animationOptions();
    void setTitle(QString title);
    QString title();
    QLegend *legend();
    QFont titleFont() const;
    void setTitleFont(const QFont &font);
    void setTitleColor(QColor color);
    QColor titleColor();
    void setBackgroundColor(QColor color);
    QColor backgroundColor();
    Q_REVISION(3) void setPlotAreaColor(QColor color);
    Q_REVISION(3) QColor plotAreaColor();
    Q_REVISION(4) void setLocalizeNumbers(bool localize);
    Q_REVISION(4) bool localizeNumbers() const;
    Q_REVISION(4) void setLocale(const QLocale &locale);
    Q_REVISION(4) QLocale locale() const;

    int count();
    void setDropShadowEnabled(bool enabled);
    bool dropShadowEnabled();
    Q_REVISION(3) qreal backgroundRoundness() const;
    Q_REVISION(3) void setBackgroundRoundness(qreal diameter);

    // Margins & plotArea
    qreal topMargin();
    qreal bottomMargin();
    qreal leftMargin();
    qreal rightMargin();
    DeclarativeMargins *minimumMargins() { return m_margins; }
    Q_REVISION(2) DeclarativeMargins *margins() { return m_margins; }
    QRectF plotArea() { return m_chart->plotArea(); }

    // Axis handling
    QAbstractAxis *defaultAxis(Qt::Orientation orientation, QAbstractSeries *series);
    void initializeAxes(QAbstractSeries *series);
    void doInitializeAxes(QAbstractSeries *series, DeclarativeAxes *axes);
    QQmlListProperty<QAbstractAxis> axes();
    static void axesAppendFunc(QQmlListProperty<QAbstractAxis> *list, QAbstractAxis *element);
    static int axesCountFunc(QQmlListProperty<QAbstractAxis> *list);
    static QAbstractAxis *axesAtFunc(QQmlListProperty<QAbstractAxis> *list, int index);
    static void axesClearFunc(QQmlListProperty<QAbstractAxis> *list);

public:
    Q_INVOKABLE QAbstractSeries *series(int index);
    Q_INVOKABLE QAbstractSeries *series(QString seriesName);
    Q_INVOKABLE QAbstractSeries *createSeries(int type, QString name = "", QAbstractAxis *axisX = 0, QAbstractAxis *axisY = 0);
    Q_INVOKABLE void removeSeries(QAbstractSeries *series);
    Q_INVOKABLE void removeAllSeries() { m_chart->removeAllSeries(); }
    Q_INVOKABLE void setAxisX(QAbstractAxis *axis, QAbstractSeries *series = 0);
    Q_INVOKABLE void setAxisY(QAbstractAxis *axis, QAbstractSeries *series = 0);
    Q_INVOKABLE void createDefaultAxes();
    Q_INVOKABLE QAbstractAxis *axisX(QAbstractSeries *series = 0);
    Q_INVOKABLE QAbstractAxis *axisY(QAbstractSeries *series = 0);
    Q_INVOKABLE void zoom(qreal factor);
    Q_INVOKABLE void scrollLeft(qreal pixels);
    Q_INVOKABLE void scrollRight(qreal pixels);
    Q_INVOKABLE void scrollUp(qreal pixels);
    Q_INVOKABLE void scrollDown(qreal pixels);

Q_SIGNALS:
    void axisLabelsChanged();
    void titleColorChanged(QColor color);
    void backgroundColorChanged();
    void dropShadowEnabledChanged(bool enabled);
    void minimumMarginsChanged();
    Q_REVISION(2) void marginsChanged();
    void plotAreaChanged(QRectF plotArea);
    void seriesAdded(QAbstractSeries *series);
    void seriesRemoved(QAbstractSeries *series);
    Q_REVISION(3) void plotAreaColorChanged();
    Q_REVISION(3) void backgroundRoundnessChanged(qreal diameter);
    Q_REVISION(4) void localizeNumbersChanged();
    Q_REVISION(4) void localeChanged();

private Q_SLOTS:
    void changeMinimumMargins(int top, int bottom, int left, int right);
    void handleAxisXSet(QAbstractAxis *axis);
    void handleAxisYSet(QAbstractAxis *axis);
    void handleAxisXTopSet(QAbstractAxis *axis);
    void handleAxisYRightSet(QAbstractAxis *axis);
    void handleSeriesAdded(QAbstractSeries *series);

protected:
    explicit DeclarativeChart(QChart::ChartType type, QQuickItem *parent);

private:
    void initChart(QChart::ChartType type);
    // Extending QChart with DeclarativeChart is not possible because QObject does not support
    // multi inheritance, so we now have a QChart as a member instead
    QChart *m_chart;
    QGraphicsScene *m_scene;
    QPointF m_mousePressScenePoint;
    QPoint m_mousePressScreenPoint;
    QPointF m_lastMouseMoveScenePoint;
    QPoint m_lastMouseMoveScreenPoint;
    Qt::MouseButton m_mousePressButton;
    Qt::MouseButtons m_mousePressButtons;
    QMutex m_sceneImageLock;
    QImage *m_currentSceneImage;
    bool m_updatePending;
    Qt::HANDLE m_paintThreadId;
    Qt::HANDLE m_guiThreadId;
    DeclarativeMargins *m_margins;
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVECHART_H
