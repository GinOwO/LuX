cmake_minimum_required(VERSION 3.20)

project(Lux VERSION 1.5 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB MAIN_SOURCES "${CMAKE_SOURCE_DIR}/src/main/*")
file(GLOB UI_SOURCES "${CMAKE_SOURCE_DIR}/src/ui/*")
fiLe(GLOB HEADER_SRC "${CMAKE_SOURCE_DIR}/include/*")

set(PROJECT_SOURCES
    main.cpp
    ${HEADER_SRC}
    ${MAIN_SOURCES}
    ${UI_SOURCES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Lux
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()

target_include_directories(Lux PRIVATE
    ${CMAKE_SOURCE_DIR}/include/
)


target_link_libraries(Lux PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

include(GNUInstallDirs)
install(TARGETS Lux
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(WIN32)
    set_property(TARGET Lux PROPERTY WIN32_EXECUTABLE true)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Lux)
endif()
