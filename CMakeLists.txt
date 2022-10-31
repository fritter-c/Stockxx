cmake_minimum_required(VERSION 3.5)

project(ChartOnGraphicsView VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        customchart.cpp
        customchart.h
        customchart.ui
        graphicmanager.cpp
        graphicmanager.h
        pricescalevisual.cpp
        pricescalevisual.h
        GoTView.h
        GoTView.cpp
        timescalevisual.cpp
        timescalevisual.h
        candle.h
        candle.cpp
        customdataserie.cpp
        customdataserie.h
        dailydataserie.cpp
        dailydataserie.h
        customprice.cpp
        customprice.h
        stockxxdatatypes.h
        dailyprice.cpp
        dailyprice.h
        indicatorvisual.cpp
        indicatorvisual.h
        indicatorcalc.cpp
        indicatorcalc.h
        pricevisual.cpp
        pricevisual.h
        pricecalc.cpp
        pricecalc.h
        candlemagnifier.cpp
        candlemagnifier.h
        priceguide.h
        priceguide.cpp
        timeguidevisual.cpp
        timeguidevisual.h
        customstudie.cpp
        customstudie.h
        resistancestudie.cpp
        resistancestudie.h
        linestudie.cpp
        linestudie.h
        stockxxdateutils.h
        resources.qrc

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ChartOnGraphicsView
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ChartOnGraphicsView APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ChartOnGraphicsView SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ChartOnGraphicsView
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ChartOnGraphicsView PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(ChartOnGraphicsView PRIVATE Qt6::OpenGLWidgets)

set_target_properties(ChartOnGraphicsView PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ChartOnGraphicsView
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ChartOnGraphicsView)
endif()
