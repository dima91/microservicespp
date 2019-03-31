cmake_minimum_required (VERSION 3.5.1)
project (microservicepp)
cmake_policy (SET CMP0015 NEW)


## Macro to add all subdirectory of "curdir" directory
MACRO (SUBDIRLIST result curdir)
	file (GLOB children ${curdir}/*)
	set (dirlist "")
	foreach (child ${children})
		if (IS_DIRECTORY ${child})
			if (EXISTS ${child}/CMakeLists.txt)
				list (APPEND dirlist ${child})
			endif ()
		endif ()
	endforeach ()
	set (${result} ${dirlist})
ENDMACRO ()


# Update all git submodules
execute_process (
    COMMAND bash -c "git submodule update --init --recursive"
)



set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -pedantic -O3 -g3 -std=c++11 -fPIC -ldl")


## Third party packages
subdirlist (submod gitSubmodules)

foreach (dir ${submod})
	message ("Found submodule in: " ${dir})
	add_subdirectory (${dir})
endforeach ()



## Main Packages
add_subdirectory (CORE_PACKAGE)
add_subdirectory (SERVICES_PACKAGE)
