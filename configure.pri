defineTest(qtConfTest_detectRealFloat) {
    contains(QT_COORD_TYPE, float): return(true)
    return(false)
}


