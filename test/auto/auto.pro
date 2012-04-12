!include( ../test.pri ) {
 error( "Couldn't find the test.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += chartdataset domain qchartview qchart
