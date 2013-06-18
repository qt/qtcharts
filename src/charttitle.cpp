/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "charttitle_p.h"
#include "chartpresenter_p.h"
#include <QFont>
#include <QFontMetrics>
#include <QDebug>
#include <QTextDocument>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartTitle::ChartTitle(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    document()->setDocumentMargin(ChartPresenter::textMargin());
}

ChartTitle::~ChartTitle()
{

}

void ChartTitle::setText(const QString &text)
{
    m_text = text;
}

QString ChartTitle::text() const
{
    return m_text;
}

void ChartTitle::setGeometry(const QRectF &rect)
{
    QRectF dummyRect;
    QGraphicsTextItem::setHtml(ChartPresenter::truncatedText(font(), m_text, qreal(0.0), rect.width(), Qt::Horizontal, dummyRect));
    setPos(rect.topLeft());
}


QSizeF ChartTitle::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);
    QSizeF sh;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF titleRect = ChartPresenter::textBoundingRect(font(), "...");
        sh = QSizeF(titleRect.width(), titleRect.height());
        break;
    }
    case Qt::PreferredSize:
    case Qt::MaximumSize: {
        QRectF titleRect = ChartPresenter::textBoundingRect(font(), m_text);
        sh = QSizeF(titleRect.width(), titleRect.height());
        break;
    }
    case Qt::MinimumDescent: {
        QFontMetrics fn(font());
        sh = QSizeF(0, fn.descent());
        break;
    }
    default:
        break;
    }

    return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
