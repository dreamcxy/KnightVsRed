
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB_RECURSE MODULE_SRC )
add_library(${MODULE_NAME} STATIC ${MODULE_SRC} fileutils.h fileutils.cpp stringutils.cpp stringutils.h bitmap.cpp bitmap.h)
