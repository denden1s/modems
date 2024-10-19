project(modems)
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*")

add_executable(${PROJECT_NAME} ${SOURCES})
