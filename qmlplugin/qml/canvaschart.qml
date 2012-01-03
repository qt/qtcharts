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


