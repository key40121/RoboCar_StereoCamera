set(OpenCV_DIR /home/build/OpenCVConfig.cmake)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_library(greetings
  SHARED
    feature_extraction.cpp
    camera_calibration.cpp
  )
# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
target_include_directories(greetings
  PUBLIC /mnt/hgfs/Ubuntu/robocar_stereocamera/include
  )
