!include( ../../common.pri ) {
 error( "Couldn't find the common.pri file!" )
}

!include( ../../integrated.pri ) {
 error( "Couldn't find the integrated.pri file !")
}

TEMPLATE = app
CONFIG  += qtestlib
!contains(TARGET, ^tst_.*):TARGET = $$join(TARGET,,"tst_")