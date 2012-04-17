!include( ../test.pri ) {
 error( "Couldn't find the test.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += qchartview qchart

test_private:{
    SUBDIRS += chartdataset domain
} 
