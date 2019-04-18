# CMakeLists to build the 'libmicroservicespp' library


set (LIBRARY_NAME		microservicespp)
set (SUBMODULES_DIR		../gitSubmodules)
set (HEADERS_DIR		include   ${SUBMODULES_DIR}/jsoncpp/include)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY	bin)


include_directories	(${HEADERS_DIR})
file				(GLOB SOURCE_FILES src/*.cpp)
add_library			(core_objs OBJECT ${SOURCE_FILES})


add_library(${LIBRARY_NAME}_static STATIC $<TARGET_OBJECTS:core_objs>)
set_target_properties (${LIBRARY_NAME}_static PROPERTIES OUTPUT_NAME ${LIBRARY_NAME})

add_library(${LIBRARY_NAME}_shared SHARED $<TARGET_OBJECTS:core_objs>)
set_target_properties (${LIBRARY_NAME}_shared PROPERTIES OUTPUT_NAME ${LIBRARY_NAME})



add_subdirectory (tests/dynamicLoader)