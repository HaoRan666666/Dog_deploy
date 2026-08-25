AUX_SOURCE_DIRECTORY(. SOURCE_LIST_LINGZU_MOTORS)
add_library(lingzu_motors
        STATIC
        ${SOURCE_LIST_LINGZU_MOTORS}
)
target_include_directories(lingzu_motors PUBLIC ./ ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(lingzu_motors PUBLIC ${PUBLIC_DEPENDENCIES} motors_can)
