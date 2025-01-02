// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/charttitle_p.h>
#include <private/chartpresenter_p.h>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtCore/QDebug>
#include <QtGui/QTextDocument>

QT_BEGIN_NAMESPACE

ChartTitle::ChartTitle(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    document()->setDocumentMargin(ChartPresenter::textMargin());
    setAcceptedMouseButtons({});
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
    QRectF truncatedRect;
    if (m_text.isEmpty()) {
        QGraphicsTextItem::setHtml(m_text);
        QGraphicsTextItem::setTextWidth(0.0);
    } else {
        QGraphicsTextItem::setHtml(ChartPresenter::truncatedText(font(), m_text, qreal(0.0),
                                                                 rect.width(), rect.height(),
                                                                 truncatedRect));
        QGraphicsTextItem::setTextWidth(truncatedRect.width());
    }
    setPos(rect.topLeft());
}


QSizeF ChartTitle::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);
    QSizeF sh;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF titleRect = ChartPresenter::textBoundingRect(font(), QStringLiteral("..."));
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

QT_END_NAMESPACE
