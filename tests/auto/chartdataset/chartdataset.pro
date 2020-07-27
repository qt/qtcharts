!include( ../auto.pri ) {
    error( "Couldn't find the auto.pri file!" )
}

QT += charts-private core-private

SOURCES += tst_chartdataset.cpp
