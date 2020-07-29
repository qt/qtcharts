# Generated from src.pro.

add_subdirectory(charts)
if(TARGET Qt::Quick)
    add_subdirectory(chartsqml2)
endif()
