cmake_minimum_required(VERSION 3.5)

project(uvsim-qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        ../uvsim.cpp
        ../uvsim.h
        ../uvsimIO.cpp
        ../uvsimIO.h
        ../uvsimArithmetic.cpp
        ../uvsimArithmetic.h
        ../uvsimControl.cpp
        ../uvsimControl.h


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(uvsim-qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        mainwindow.ui
        ../uvsim.cpp ../uvsim.h ../uvsimArithmetic.cpp ../uvsimArithmetic.h ../uvsimControl.cpp ../uvsimControl.h ../uvsimIO.cpp ../uvsimIO.h

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET uvsim-qt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(uvsim-qt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(uvsim-qt
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(uvsim-qt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.uvsim-qt)
endif()
set_target_properties(uvsim-qt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS uvsim-qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(uvsim-qt)
endif()
