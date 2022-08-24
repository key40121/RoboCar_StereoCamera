# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)
# プロジェクト名と使用する言語を設定
project(test_cmake CXX)
# a.outという実行ファイルをmain.cppとhello.cppから作成
add_executable(a.out main.cpp)
set(OpenCV_DIR /home/build/OpenCVConfig.cmake)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(a.out ${OpenCV_LIBS})