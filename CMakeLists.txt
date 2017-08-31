cmake_minimum_required( VERSION 2.8 )
project( VDB_Tests )

set( HOUDINI_ROOT "/opt/hfs16.0.633" )

#headers
include_directories( ${HOUDINI_ROOT}/toolkit/include )
#libraries
link_directories( ${HOUDINI_ROOT}/dsolib )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DOPENVDB_3_ABI_COMPATIBLE -std=c++11" )
set( PROJECT_LINK_LIBS tbb Half openvdb_sesi )

#Hello World
add_executable( HelloWorld src/hello_world.cpp )
set_target_properties( HelloWorld PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE )
target_link_libraries( HelloWorld ${PROJECT_LINK_LIBS} )
install( TARGETS HelloWorld DESTINATION ${CMAKE_SOURCE_DIR}/bin )

