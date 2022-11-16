#
# Packaging
# https://cmake.org/cmake/help/latest/module/CPack.html
#

set( CPACK_PACKAGE_NAME ${PROJECT_NAME} )
set( CPACK_PACKAGE_VENDOR "gabrielkim13" )
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Build complex rules, serialize them as JSON, and execute them in C++" )
set( CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/gabrielkim13/json-logic-cpp" )
set( CPACK_PACKAGE_CONTACT      "https://github.com/gabrielkim13/json-logic-cpp" )
set( CPACK_PACKAGE_VERSION ${JSONLOGICCPP_THIS_MODULE_VERSION} ) 
set( CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME} )
get_filename_component( json_logic_cpp_root_dir ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY )
set( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" )
set( CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md" )

set( CPACK_COMPONENT_Library_DISPLAY_NAME "json_logic_cpp Library" )
set( CPACK_COMPONENT_Library_DESCRIPTION "The json_logic_cpp binary library." )
set( CPACK_COMPONENT_Library_REQUIRED 1 )
set( CPACK_COMPONENT_Devel_DISPLAY_NAME "json_logic_cpp Development Files" )
set( CPACK_COMPONENT_Devel_DESCRIPTION "Development files for compiling against json_logic_cpp." )
set( CPACK_COMPONENT_Devel_REQUIRED 1 )

if( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )

    if ( "${CPACK_PACKAGE_ARCHITECTURE}" STREQUAL "" )
        # Note: the architecture should default to the local architecture, but it
        # in fact comes up empty.  We call `uname -m` to ask the kernel instead.
        EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE )
    endif()

    set( CPACK_INCLUDE_TOPLEVEL_DIRECTORY 1 )
    set( CPACK_PACKAGE_RELEASE 1 )


    # RPM - https://cmake.org/cmake/help/latest/cpack_gen/rpm.html
    set( CPACK_RPM_PACKAGE_RELEASE ${CPACK_PACKAGE_RELEASE} )
    set( CPACK_RPM_PACKAGE_ARCHITECTURE ${CPACK_PACKAGE_ARCHITECTURE} )
    set( CPACK_RPM_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION_SUMMARY} )
    set( CPACK_RPM_PACKAGE_URL ${CPACK_PACKAGE_HOMEPAGE_URL} )
    set( CPACK_RPM_PACKAGE_LICENSE "MIT" )
    set( CPACK_RPM_COMPONENT_INSTALL 1 )
    set( CPACK_RPM_MAIN_COMPONENT "Library" )
    set( CPACK_RPM_COMPRESSION_TYPE "xz" )
    set( CPACK_RPM_PACKAGE_AUTOPROV 1 )
    set( CPACK_RPM_PACKAGE_NAME "${CPACK_PACKAGE_NAME}" )
    set( CPACK_RPM_FILE_NAME "RPM-DEFAULT" )

    set( CPACK_RPM_Library_PACKAGE_ARCHITECTURE ${CPACK_PACKAGE_ARCHITECTURE} )
    set( CPACK_RPM_Library_PACKAGE_NAME ${CPACK_PACKAGE_NAME} )
    set( CPACK_RPM_Library_FILE_NAME
         "${CPACK_RPM_Library_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}.${CPACK_RPM_Library_PACKAGE_ARCHITECTURE}.rpm" )
    set( CPACK_RPM_Library_PACKAGE_SUMMARY ${CPACK_COMPONENT_Library_DESCRIPTION} )

    set( CPACK_RPM_Devel_PACKAGE_REQUIRES "cmake >= ${CMAKE_MINIMUM_REQUIRED_VERSION},json_logic_cpp >= ${CPACK_PACKAGE_VERSION}" )
    set( CPACK_RPM_Devel_PACKAGE_SUMMARY ${CPACK_COMPONENT_Devel_DESCRIPTION} )
    set( CPACK_RPM_Devel_PACKAGE_ARCHITECTURE "noarch" )  # only contains headers and cmake files
    set( CPACK_RPM_Devel_PACKAGE_NAME "${CPACK_PACKAGE_NAME}-devel" )
    set( CPACK_RPM_Devel_FILE_NAME
         "${CPACK_RPM_Devel_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}.${CPACK_RPM_Devel_PACKAGE_ARCHITECTURE}.rpm" )

    # DEB - https://cmake.org/cmake/help/latest/cpack_gen/deb.html
    set( CPACK_DEBIAN_PACKAGE_NAME "${CPACK_PACKAGE_NAME}-dev" )
    set( CPACK_DEBIAN_PACKAGE_RELEASE ${CPACK_PACKAGE_RELEASE} )
    set( CPACK_DEBIAN_PACKAGE_HOMEPAGE ${CPACK_PACKAGE_HOMEPAGE_URL} )
    set( CPACK_DEB_COMPONENT_INSTALL 1 )
    set( CPACK_DEBIAN_COMPRESSION_TYPE "xz")

    if ( ${CPACK_PACKAGE_ARCHITECTURE} STREQUAL "x86_64" )
        set( CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64" )  # DEB doesn't always use the kernel's arch name
    else()
        set( CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${CPACK_PACKAGE_ARCHITECTURE} )
    endif()

    set( CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT" ) # Use default naming scheme
    
    set( CPACK_DEBIAN_LIBRARY_PACKAGE_NAME ${CPACK_PACKAGE_NAME} )
    set( CPACK_DEBIAN_LIBRARY_PACKAGE_SHLIBDEPS 1 )
    
    set( CPACK_DEBIAN_DEVEL_PACKAGE_DEPENDS "cmake (>= ${CMAKE_MINIMUM_REQUIRED_VERSION}), json_logic_cpp (>= ${CPACK_PACKAGE_VERSION})" )
    set( CPACK_DEBIAN_DEVEL_PACKAGE_NAME "${CPACK_PACKAGE_NAME}-dev" )

elseif( ${CMAKE_HOST_WIN32} )
    set( CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON )
    set( CPACK_NSIS_DISPLAY_NAME ${PROJECT_NAME} )
    set( CPACK_NSIS_PACKAGE_NAME ${PROJECT_NAME} )
    set( CPACK_NSIS_URL_INFO_ABOUT ${CPACK_PACKAGE_HOMEPAGE_URL} )
endif()
