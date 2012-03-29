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

#ifndef CHARTGLOBAL_H
#define CHARTGLOBAL_H

#define QTCOMMERCIALCHART_VERSION_STR   "1.0"
#define QTCOMMERCIALCHART_VERSION 0x01

#if defined(QTCOMMERCIALCHART_LIBRARY)
#  define QTCOMMERCIALCHART_EXPORT Q_DECL_EXPORT
#else
#  define QTCOMMERCIALCHART_EXPORT Q_DECL_IMPORT
#endif

#define QTCOMMERCIALCHART_NAMESPACE QtCommercialChart

#ifdef QTCOMMERCIALCHART_NAMESPACE
# define QTCOMMERCIALCHART_BEGIN_NAMESPACE namespace QTCOMMERCIALCHART_NAMESPACE {
# define QTCOMMERCIALCHART_END_NAMESPACE }
# define QTCOMMERCIALCHART_USE_NAMESPACE using namespace QTCOMMERCIALCHART_NAMESPACE;
#else
# define QTCOMMERCIALCHART_BEGIN_NAMESPACE
# define QTCOMMERCIALCHART_END_NAMESPACE
# define QTCOMMERCIALCHART_USE_NAMESPACE
#endif

#define CHART_DEBUG chartDebug(3,__LINE__,__FILE__,__FUNCTION__);

#include <stdarg.h>
#include <QDebug>

/*
static QDebug chartDebug(int numargs,...)
{
       va_list valist;
       va_start(valist,numargs);
       //for( int i = 0 ; i < numargs; i++ )
       int line=va_arg(valist,int);
       char* file=va_arg(valist,char*);
       char* function=va_arg(valist,char*);
       va_end(valist);
       return qDebug()<<QString().append(function).append("(").append(file).append(":%1)").arg(line);
}
*/
#endif
