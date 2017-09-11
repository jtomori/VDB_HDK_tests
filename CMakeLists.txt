cmake_minimum_required( VERSION 2.8 )
project( VDB_Tests )

set( HOUDINI_ROOT "/opt/hfs16.0.633" )

#all targets headers, libs, flags
include_directories( include ${HOUDINI_ROOT}/toolkit/include )
link_directories( ${HOUDINI_ROOT}/dsolib )
set( PROJECT_LINK_LIBS tbb Half openvdb_sesi )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

#OpenVDB flags
set( VDB_COMPILE_FLAGS "-DOPENVDB_3_ABI_COMPATIBLE" )

#HDK flags
set( HDK_COMPILE_FLAGS "-DVERSION=\"16.0.633\" -D_GNU_SOURCE -DLINUX -DAMD64 -m64 -fPIC -DSIZEOF_VOID_P=8 -DFBX_ENABLED=1 -DOPENCL_ENABLED=1 -DOPENVDB_ENABLED=1 -DSESI_LITTLE_ENDIAN -DENABLE_THREADS -DUSE_PTHREADS -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DGCC4 -DGCC3 -Wno-deprecated -Wall -W -Wno-parentheses -Wno-sign-compare -Wno-reorder -Wno-uninitialized -Wunused -Wno-unused-parameter -Wno-unused-local-typedefs -O2 -fno-strict-aliasing" )
set( HDK_COMPILE_FLAGS_PLUGIN  " ${HDK_COMPILE_FLAGS} -DMAKING_DSO" )
set( HDK_LINK_FLAGS "-lpthread -lHoudiniUI -lHoudiniOPZ -lHoudiniOP3 -lHoudiniOP2 -lHoudiniOP1 -lHoudiniSIM -lHoudiniGEO -lHoudiniPRM -lHoudiniUT -lboost_system -L/usr/X11R6/lib64 -L/usr/X11R6/lib -lGLU -lGL -lX11 -lXext -lXi -ldl" )

#--- VDB ---
#Hello World
add_executable( HelloWorld src/hello_world.cpp )
set_target_properties( HelloWorld PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE )
set_target_properties( HelloWorld PROPERTIES COMPILE_FLAGS "${VDB_COMPILE_FLAGS}")
target_link_libraries( HelloWorld ${PROJECT_LINK_LIBS} )
install( TARGETS HelloWorld DESTINATION ${CMAKE_SOURCE_DIR}/bin )

#Create SDF Sphere
add_executable( CreateSDFSphere src/create_sdf_sphere.cpp )
set_target_properties( CreateSDFSphere PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE )
set_target_properties( CreateSDFSphere PROPERTIES COMPILE_FLAGS "${VDB_COMPILE_FLAGS}")
target_link_libraries( CreateSDFSphere ${PROJECT_LINK_LIBS} )
install( TARGETS CreateSDFSphere DESTINATION ${CMAKE_SOURCE_DIR}/bin )

#--- HDK ---
#Geoisosurface (standalone)
add_executable( Geoisosurface src/geoisosurface.cpp )
set_target_properties( Geoisosurface PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE )
set_target_properties( Geoisosurface PROPERTIES COMPILE_FLAGS "${HDK_COMPILE_FLAGS}")
set_target_properties( Geoisosurface PROPERTIES LINK_FLAGS "${HDK_LINK_FLAGS}")
target_link_libraries( Geoisosurface ${PROJECT_LINK_LIBS} )
install( TARGETS Geoisosurface DESTINATION ${CMAKE_SOURCE_DIR}/bin )

#SOP Empty Node (plugin/library)
add_library( SopEmptyNode SHARED src/sop_empty_node.cpp )
set_target_properties( SopEmptyNode PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE )
set_target_properties( SopEmptyNode PROPERTIES COMPILE_FLAGS "${HDK_COMPILE_FLAGS_PLUGIN}")
set_target_properties( SopEmptyNode PROPERTIES LINK_FLAGS "${HDK_LINK_FLAGS}")
target_link_libraries( SopEmptyNode ${PROJECT_LINK_LIBS} )
install( TARGETS SopEmptyNode DESTINATION ${CMAKE_SOURCE_DIR}/lib )

#SOP My First Node - with comments and simplified, based on Ostap's clean up (plugin)
add_library( SopMyFirstNode SHARED src/sop_my_first_node.cpp )
set_target_properties( SopMyFirstNode PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE )
set_target_properties( SopMyFirstNode PROPERTIES COMPILE_FLAGS "${HDK_COMPILE_FLAGS_PLUGIN}")
set_target_properties( SopMyFirstNode PROPERTIES LINK_FLAGS "${HDK_LINK_FLAGS}")
target_link_libraries( SopMyFirstNode ${PROJECT_LINK_LIBS} )
install( TARGETS SopMyFirstNode DESTINATION ${CMAKE_SOURCE_DIR}/lib )
