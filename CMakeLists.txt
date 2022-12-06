cmake_minimum_required(VERSION 3.5)

project(Stockxx VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Network)

set(PROJECT_SOURCES
        resources.qrc

        source/main.cpp
        source/mainwindow.cpp
        source/mainwindow.h
        source/mainwindow.ui
        source/mainwindow.ui
        source/candle.h
        source/candle.cpp
        source/stockxxdatatypes.h
        source/indicatorvisual.cpp
        source/indicatorvisual.h
        source/indicatorcalc.cpp
        source/indicatorcalc.h
        source/pricevisual.cpp
        source/pricevisual.h
        source/pricecalc.cpp
        source/pricecalc.h
        source/stockxxdateutils.h
        source/IndicatorDataTypes.h
        source/indicatormanager.cpp
        source/indicatormanager.h

        source/graphic/customchart.cpp
        source/graphic/customchart.h
        source/graphic/customchart.ui
        source/graphic/graphicmanager.cpp
        source/graphic/graphicmanager.h
        source/graphic/pricescalevisual.cpp
        source/graphic/pricescalevisual.h
        source/graphic/GoTView.h
        source/graphic/GoTView.cpp
        source/graphic/timescalevisual.cpp
        source/graphic/timescalevisual.h    
        source/graphic/candlemagnifier.cpp
        source/graphic/candlemagnifier.h
        source/graphic/priceguide.h
        source/graphic/priceguide.cpp
        source/graphic/timeguidevisual.cpp
        source/graphic/timeguidevisual.h

        source/dataseries/customdataserie.cpp
        source/dataseries/customdataserie.h
        source/dataseries/dailydataserie.cpp
        source/dataseries/dailydataserie.h
        source/dataseries/minutedataserie.cpp
        source/dataseries/minutedataserie.h
        source/dataseries/dataseriemanager.cpp
        source/dataseries/dataseriemanager.h

        source/customprice/customprice.cpp
        source/customprice/customprice.h
        source/customprice/customserie.cpp
        source/customprice/customserie.h
        
        source/studies/customstudie.cpp
        source/studies/customstudie.h
        source/studies/resistancestudie.cpp
        source/studies/resistancestudie.h
        source/studies/linestudie.cpp
        source/studies/linestudie.h      
        source/studies/fibonaccistudie.cpp
        source/studies/fibonaccistudie.h
        source/studies/vertlinestudie.cpp
        source/studies/vertlinestudie.h
        source/studies/channelstudie.cpp
        source/studies/channelstudie.h
        source/studies/freehandstudie.cpp
        source/studies/freehandstudie.h
        source/studies/studieproperties.cpp
        source/studies/studieproperties.h
        source/studies/studieproperties.ui
        
        source/alphaAPI/stockdataapi.cpp
        source/alphaAPI/stockdataapi.h
        source/alphaAPI/symbolsearcher.cpp
        source/alphaAPI/symbolsearcher.h
        source/alphaAPI/symbolsearcher.ui
        source/alphaAPI/symbolseracherapi.cpp
        source/alphaAPI/symbolseracherapi.h
        source/alphaAPI/tickercompleter.cpp
        source/alphaAPI/tickercompleter.h

        source/calc/calcdaemon.cpp
        source/calc/calcdaemon.h

        source/calc/dataseries/customdataseriecalc.cpp
        source/calc/dataseries/customdataseriecalc.h
        source/calc/dataseries/dailydataseriecalc.cpp
        source/calc/dataseries/dailydataseriecalc.h
        source/calc/dataseries/minutedataseriecalc.cpp
        source/calc/dataseries/minutedataseriecalc.h
        
        source/calc/customprice/custompricecalc.cpp 
        source/calc/customprice/custompricecalc.h
        source/calc/customprice/customseriecalc.cpp
        source/calc/customprice/customseriecalc.h

        
        source/calc/indicators/customindicatorcalc.cpp
        source/calc/indicators/customindicatorcalc.h
        source/calc/indicators/customarrayindicatorcalc.cpp
        source/calc/indicators/customarrayindicatorcalc.h
        source/calc/indicators/priceindicatorcalc.cpp
        source/calc/indicators/priceindicatorcalc.h
        source/calc/indicators/movingaveragecalc.cpp
        source/calc/indicators/movingaveragecalc.h

        source/indicators/customindicator.h
        source/indicators/customindicator.cpp
        source/indicators/customarrayindicator.cpp
        source/indicators/customarrayindicator.h
        source/indicators/movingaverage.cpp
        source/indicators/movingaverage.h
        source/indicators/priceindicator.cpp
        source/indicators/priceindicator.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Stockxx
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Stockxx SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Stockxx
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Stockxx PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Stockxx PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(Stockxx PRIVATE Qt6::Network)
target_link_libraries(Stockxx PRIVATE Qt6::Gui)

target_include_directories(Stockxx PRIVATE
    source/

    source/calc
    source/calc/customprice
    source/calc/dataseries
    source/calc/indicators

    source/studies

    source/graphic

    source/customprice

    source/alphaAPI

    source/dataseries

                                                       )
set_target_properties(Stockxx PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS Stockxx
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Stockxx)
endif()
