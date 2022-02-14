cmake_minimum_required(VERSION 3.5.0)
project(rqt_hmclad_gui)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rqt_gui
  rqt_gui_cpp
  std_msgs
  ackermann_msgs
)

find_package(Qt5Widgets REQUIRED)

find_package(Qt5 ${rviz_QT_VERSION} EXACT REQUIRED Core Widgets)


catkin_python_setup()

catkin_package(
# INCLUDE_DIRS ${rqt_hmclad_gui_INCLUDE_DIRECTORIES}
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rqt_gui rqt_gui_cpp std_msgs
#  DEPENDS system_lib
)

set(rqt_hmclad_gui_SRCS
  src/rqt_hmclad_gui.cpp
  src/drive_widget.cpp  
)

set(rqt_hmclad_gui_HDRS
  # include/rqt_hmclad_gui/rqt_hmclad_gui.h  
  include/rqt_hmclad_gui.h  
  include/drive_widget.h  
)



set(rqt_hmclad_gui_UIS
  src/rqt_hmclad_gui.ui
)

qt5_wrap_cpp(rqt_hmclad_gui_MOCS ${rqt_hmclad_gui_HDRS})
qt5_wrap_ui(rqt_hmclad_gui_UIS_H ${rqt_hmclad_gui_UIS})

include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}/..
  ${catkin_INCLUDE_DIRS}  
)

add_library(${PROJECT_NAME}
  ${rqt_hmclad_gui_SRCS}   
  ${rqt_hmclad_gui_MOCS}
  ${rqt_hmclad_gui_UIS_H}  
)
file(GLOB QWT_INCLUDE_DIR "/usr/include/qwt")
include_directories(include ${catkin_INCLUDE_DIRS} ${QWT_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  Qt5::Widgets  
  ${QT_LIBRARIES}
  -lpthread
)
