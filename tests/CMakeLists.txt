add_executable(test_geocoding
    test_geocoding.cpp
)

target_link_libraries(test_geocoding
    PRIVATE
        Qt6::Core
        Qt6::Test
        Qt6::Network
        geocoding
)

target_include_directories(test_geocoding
    PUBLIC
        ${CMAKE_SOURCE_DIR}/libs
)

enable_testing()
add_test(NAME test_geocoding COMMAND test_geocoding)
