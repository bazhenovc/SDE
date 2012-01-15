
project(winman)

include_directories(include)

find_package(Qt4 REQUIRED)
find_package(X11 REQUIRED)
include(${QT_USE_FILE})
set(QT_USE_QTDBUS TRUE)
add_definitions(-Wall -pipe ${QT_DEFINITIONS})

add_executable(sde-winman source/main.cc source/WMApplication.cc source/XEventLoopThread.cc)
target_link_libraries(sde-winman X11 ${QT_LIBRARIES})
