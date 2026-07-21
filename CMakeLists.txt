# CMakeList.txt Santiago Isaac  VT     ECE 3574  Jan 28 2026
# CMake project for milestone01, include source and define
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("milestone04")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Test REQUIRED)
find_package(Qt6Core REQUIRED)
find_package(Doxygen REQUIRED)

if (DOXYGEN_FOUND)
doxygen_add_docs(docs ${PROJECT_SOURCE_DIR})
add_custom_target(doxyoutput ALL COMMAND ${DOXYGEN_EXECUTABLE}
                  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMENT "Generating Project Documentation"
                  VERBATIM
                  )
endif()

# Add source to this project's executable.
add_executable (main "main.cpp" 
							"Document.cpp" "Document.hpp"
              "Syllabizer.cpp" "Syllabizer.hpp"
              "Lexicon.hpp" "Lexicon.cpp"
              "DocumentWorker.h" "DocumentWorker.cpp"
)
target_link_libraries(main Qt6::Widgets Qt6::Test Qt6::Core)

add_executable (testproject "ProjectTest.h" "Document.cpp" "Document.hpp" "Syllabizer.cpp" "Syllabizer.hpp" "MainWindow.cpp" "DocumentWindow.cpp" "ProjectTest.cpp" "Lexicon.hpp" "Lexicon.cpp" "DocumentWorker.h" "DocumentWorker.cpp")
target_link_libraries(testproject Qt6::Widgets Qt6::Test Qt6::Core)
add_executable (guimain "guimain.cpp" "MainWindow.cpp" "DocumentWindow.cpp" "Document.cpp" "Syllabizer.cpp" "Lexicon.hpp" "Lexicon.cpp" "DocumentWorker.h" "DocumentWorker.cpp")
target_link_libraries(guimain Qt6::Widgets Qt6::Core)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
  set_property(TARGET testproject PROPERTY CXX_STANDARD 17)
  set_property(TARGET guimain PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
