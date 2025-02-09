cmake_minimum_required(VERSION 3.16)

project(MyComputerCareer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP "Generated Files")

find_package(Qt6 6.5 REQUIRED COMPONENTS Widgets Svg Network)

qt_standard_project_setup(REQUIRES 6.5)

file(GLOB_RECURSE PROJECT_SOURCE FILES Source/*.h Source/*.cpp Source/*.c Source/*.hh)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCE})

 qt_add_resources(QRC_FILE Resources.qrc)

qt_add_executable(appMyComputerCareer
    ${PROJECT_SOURCE}
    ${QRC_FILE}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMyComputerCareer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMyComputerCareer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_link_libraries(appMyComputerCareer
    PRIVATE Qt6::Svg Qt6::Widgets Qt6::Network
)

target_include_directories(appMyComputerCareer PUBLIC Source)

include(GNUInstallDirs)
install(TARGETS appMyComputerCareer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
