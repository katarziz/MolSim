# make doc_doxygen optional if someone does not have / like doxygen

#Check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # create doxygen target
    add_custom_target(doc_doxygen
            COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Doxyfile
            COMMENT "Building HTML Documentation")
else ()
    message(STATUS "Doxygen needs to be installed to generate the doxygen documentation.")
endif (DOXYGEN_FOUND)
