
set (SUBMODULES_DIR		../../../gitSubmodules)
set (HEADERS_DIR		.  ../../include)


include_directories	(${HEADERS_DIR})


add_library (SharedObject SHARED loadableClass.cpp)
set_target_properties (SharedObject PROPERTIES OUTPUT_NAME loadableClass PREFIX "")


add_executable (DynamicLoaderTest dynamicLoaderTest.cpp)
target_link_libraries (DynamicLoaderTest SharedObject dl)