set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)

message(${PROJECT_SOURCE_DIR})
configure_file (
  "${PROJECT_SOURCE_DIR}/src/Utils/Version/Version.h.in"
  "${PROJECT_SOURCE_DIR}/src/Utils/Version/Version.h"
  )