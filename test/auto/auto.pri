!include( ../test.pri ) {
    error( "Couldn't find the test.pri file!" )
}

CONFIG  += qtestlib
!contains(TARGET, ^tst_.*):TARGET = $$join(TARGET,,"tst_")
