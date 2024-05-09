cmake_minimum_required(VERSION 3.5)

project(CW2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CW2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        login.h login.cpp login.ui
        departments_insert.h departments_insert.cpp departments_insert.ui
        departments_update.h departments_update.cpp departments_update.ui
                departments.h departments.cpp departments.ui
                supervisors.h supervisors.cpp supervisors.ui
                supervisors_insert.h supervisors_insert.cpp supervisors_insert.ui
                supervisors_update.h supervisors_update.cpp supervisors_update.ui
                students.h students.cpp students.ui
                students_insert.h students_insert.cpp students_insert.ui
                students_update.h students_update.cpp students_update.ui
                researches.h researches.cpp researches.ui
                researches_insert.h researches_insert.cpp researches_insert.ui
                researches_update.h researches_update.cpp researches_update.ui
                students_researches.h students_researches.cpp students_researches.ui
                funding.h funding.cpp funding.ui
                funding_insert.h funding_insert.cpp funding_insert.ui
                funding_update.h funding_update.cpp funding_update.ui
                reports.h reports.cpp reports.ui
                reports_insert.h reports_insert.cpp reports_insert.ui
                reports_update.h reports_update.cpp reports_update.ui

        )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CW2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CW2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CW2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CW2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CW2)
endif()
set_target_properties(CW2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CW2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CW2)
endif()
