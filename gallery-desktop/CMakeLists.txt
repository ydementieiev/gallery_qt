cmake_minimum_required(VERSION 3.5)

project(gallery-desktop VERSION 0.1 LANGUAGES CXX)

# Set automatic Qt code generation for UI files, meta-object compilation, and resources
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set the required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required Qt components
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

# Define the sources used in the project
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

# Add an executable for the project using Qt-specific setup
qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_SOURCES}
    album_list_widget.h album_list_widget.cpp album_list_widget.ui
    res/resource.qrc
    thumbnail_proxy_model.h thumbnail_proxy_model.cpp)

# Link the executable to necessary Qt modules and the gallery-core library
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
    gallery-core # Ensure gallery-core is being built or available
)

# Set application and bundle properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    WIN32_EXECUTABLE TRUE
)

# Specify install rules
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the Qt executable to ensure all Qt-specific processing is done
qt_finalize_executable(${PROJECT_NAME})
