option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_SHOW_FILES YES)
doxygen_add_docs(docs ${PROJECT_SOURCE_DIR}/src COMMENT "Generate Docs" )

