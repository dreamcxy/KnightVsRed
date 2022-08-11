
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB_RECURSE MODULE_SRC)
add_library(${MODULE_NAME} STATIC ${MODULE_SRC}

        include/logger.h
        include/handler.h
        include/buffer.h
        include/gametime.h
        include/servertemplate.h
        include/servermanager.h
        include/networkmanager.h

        handler.cpp
        logger.cpp
        buffer.cpp
        gametime.cpp
        servertemplate.cpp
        servermanager.cpp
        networkmanager.cpp
        )


