cmake_minimum_required(VERSION 3.5)

# Set the project name and specify the required C++ standard
project(gallery-core LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic handling of Qt-specific constructs like MOC and UIC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find required Qt packages
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)

# Specify the list of header files
set(HEADER_FILES
    include/gallery-core_global.h
    include/album.h
    include/picture.h
    include/db/database_manager.h
    include/db/dao/album_dao.h
    include/db/dao/picture_dao.h
    include/models/album_model.h
    include/models/picture_model.h
)

# Specify the list of source files
set(SOURCE_FILES
    src/album.cpp
    src/picture.cpp
    src/db/database_manager.cpp
    src/db/dao/album_dao.cpp
    src/db/dao/picture_dao.cpp
    src/models/album_model.cpp
    src/models/picture_model.cpp
)

# Add a library target to the project
add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

# Specify include directories for the target
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Link the target with Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt6::Sql
)

# Define preprocessor macros for the target
target_compile_definitions(${PROJECT_NAME} PRIVATE GALLERYCORE_LIBRARY)
