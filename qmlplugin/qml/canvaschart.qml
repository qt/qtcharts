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

import QtQuick 2.0

Canvas {
    id: canvas
    width: 200
    height: 200
    smooth:true
    renderTarget:Canvas.Image
    renderInThread:false

    onWidthChanged: requestPaint()
    onHeightChanged: requestPaint()

    onPaint: {
        var ctx = canvas.getContext('2d')
        ctx.reset()
        ctx.clearRect(0, 0, canvas.width, canvas.height)
        ctx.strokeStyle = "red"
        ctx.lineWidth = 1
        ctx.moveTo(10, 10)
        ctx.lineTo(10, canvas.height-10)
        ctx.lineTo(canvas.width-10, canvas.height-10)
        ctx.text("Axis x", canvas.width / 2, canvas.height)
        ctx.text("Insert chart here", canvas.width / 2, canvas.height / 2)
        ctx.stroke();
    }
}


