cmake_minimum_required(VERSION 3.14)

project(gallery-core LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Sql)

add_library(gallery-core SHARED
  gallery-core_global.h
  album.cpp
  album.h
  picture.h picture.cpp
  database_manager.h database_manager.cpp
  album_dao.h album_dao.cpp
)

target_link_libraries(gallery-core PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt6::Sql
)

target_compile_definitions(gallery-core PRIVATE GALLERYCORE_LIBRARY)
