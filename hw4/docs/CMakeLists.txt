option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
set(DOXYGEN_GENERATE_HTML YES)
doxygen_add_docs(docs ${PROJECT_SOURCE_DIR}/src COMMENT "Generate Docs")

