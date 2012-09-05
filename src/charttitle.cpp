/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "charttitle_p.h"
#include <QFont>
#include <QFontMetrics>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartTitle::ChartTitle(QGraphicsItem* parent):QGraphicsSimpleTextItem(parent)
{

}

ChartTitle::~ChartTitle()
{

}

void ChartTitle::setText(const QString &text)
{
      m_text=text;
}

QString ChartTitle::text() const
{
    return m_text;
}

void ChartTitle::setGeometry(const QRectF &rect)
{
  QFontMetrics fn(font());

  int width = rect.width();

  if (fn.boundingRect(m_text).width() > width)
  {
    QString string = m_text + "...";
    while (fn.boundingRect(string).width() > width && string.length() > 3)
      string.remove(string.length() - 4, 1);
    QGraphicsSimpleTextItem::setText(string);
  }
  else
    QGraphicsSimpleTextItem::setText(m_text);

  setPos(rect.topLeft());
}


QSizeF ChartTitle::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
  Q_UNUSED(constraint);
  QFontMetrics fn (font ());
  QSizeF sh;

  switch(which) {
    case Qt::MinimumSize:
        sh = QSizeF(fn.boundingRect ("...").width(),fn.height());
        break;
    case Qt::PreferredSize:
        sh = QSizeF(fn.boundingRect(m_text).width(),fn.height());
        break;
    case Qt::MaximumSize:
        sh = QSizeF(fn.boundingRect(m_text).width(),fn.height());
        break;
    case Qt::MinimumDescent:
        sh = QSizeF(0, fn.descent ());
        break;
    default:
      break;
  }

  return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
