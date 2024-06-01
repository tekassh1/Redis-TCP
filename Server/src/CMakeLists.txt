include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB COMMAND_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/commands/*.cpp)
list(APPEND SOURCE_FILES ${COMMAND_SOURCE_FILES})

add_library(Lib STATIC ${SOURCE_FILES})
target_include_directories(Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(Lib PUBLIC gtest)

add_executable(Server main.cpp)
target_link_libraries(Server PRIVATE Lib ws2_32)