PROJECT(hermes)
cmake_minimum_required(VERSION 2.8)
INCLUDE(../config.cmake)

set(euryale_include_dir ../euryale/src/org/cracs)

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
	#ADD_DEFINITIONS(-g)
	SET(LIBRARY_OUTPUT_PATH ${hermes_BINARY_DIR}/Debug)
	SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Debug)
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Release")
	ADD_DEFINITIONS(-O3)
	SET(LIBRARY_OUTPUT_PATH ${hermes_BINARY_DIR}/Release)
	SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Release)
ELSE(CMAKE_BUILD_TYPE STREQUAL "Release")
#	ADD_DEFINITIONS(-g)
	SET(LIBRARY_OUTPUT_PATH ${hermes_BINARY_DIR}/Debug)
	SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Debug)
ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")

set(hermes_base src/edu/cmu)

#HERMES BASE
AUX_SOURCE_DIRECTORY(${hermes_base}/hermes hermes_src)

#DETECTION
AUX_SOURCE_DIRECTORY(${hermes_base}/hermes/runtime hermes_src_runtime)


set(hermes_package
#COMMON
${hermes_src}
${hermes_src_runtime}
)

#MESSAGE(STATUS, "######## hermes: "${hermes_src_ft_net_control_packet}" ########")

# set(hermes_superpeer ${hermes_base}/hermes/superpeer/superpeer_main)
# set(hermes_superpeer_plugin_file ${hermes_base}/hermes/superpeer/superpeer_plugin_startup)

# set(hermes_leaf ${hermes_base}/hermes/leaf/leaf_main)
# set(hermes_leaf_plugin_file ${hermes_base}/hermes/leaf/leaf_plugin_startup)

# set(hermes_monitor ${hermes_base}/hermes/monitor/monitor_main)
# set(hermes_monitor_plugin_file ${hermes_base}/hermes/monitor/monitor_plugin_startup)

# set(hermes_sensor ${hermes_base}/hermes/sensor/sensor_main)
# set(hermes_sensor_plugin_file ${hermes_base}/hermes/sensor/sensor_plugin_startup)

set(hermes_include_dir src/edu/cmu/)


# Includes
include_directories(${hermes_include_dir} ${ace_include_dir} ${crypto_include_dir} ${euryale_include_dir})

IF(BUILD_SHARED STREQUAL "TRUE")
	add_library(hermes SHARED ${hermes_package})
        TARGET_LINK_LIBRARIES(hermes euryale ${ace_shared_lib} ${crypto_static_lib} pthread)
        
        add_executable(hermes_test ${hermes_base}/hermes/runtime/clienttest.cpp)
        TARGET_LINK_LIBRARIES(hermes_test hermes euryale ${ace_shared_lib} ${crypto_static_lib} pthread)

ENDIF(BUILD_SHARED STREQUAL "TRUE")


