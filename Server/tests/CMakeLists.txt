file(GLOB TEST_SOURCES "*.cpp")
add_executable(ServerTests ${TEST_SOURCES})

target_link_libraries(ServerTests PRIVATE gtest_main Lib ws2_32 gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(ServerTests)

target_include_directories(ServerTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src ${CMAKE_CURRENT_SOURCE_DIR}/../include)