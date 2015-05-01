
file (GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.h
    *.cpp
)

add_library (easywinhttp STATIC ${SOURCES})

set_target_properties(easywinhttp PROPERTIES
    PUBLIC_HEADER "easywinhttp/easywinhttp.h"
)

install (TARGETS ${PROJECT_NAME}
    EXPORT easywinhttp-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include COMPONENT dev
)

install (EXPORT easywinhttp-targets
    DESTINATION CMake
    COMPONENT dev
)
