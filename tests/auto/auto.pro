!include( ../tests.pri ) {
 error( "Couldn't find the tests.pri file!" )
}

TEMPLATE = subdirs
SUBDIRS += qchartview qchart qlineseries qbarset qbarseries qstackedbarseries qpercentbarseries qgroupedbarseries qpieslice qpieseries qpiemodelmapper qsplineseries qscatterseries qxymodelmapper qbarmodelmapper

test_private:{
    SUBDIRS += domain chartdataset
} 
