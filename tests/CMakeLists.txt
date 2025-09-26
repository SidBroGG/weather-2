function(add_qt_test name)
    add_executable(${name} ${name}.cpp)

    target_link_libraries(${name}
        PRIVATE
            Qt6::Core
            Qt6::Test
            Qt6::Network
            ${ARGN}
    )

    target_include_directories(${name}
        PUBLIC
            ${CMAKE_SOURCE_DIR}/libs
    )

    add_test(NAME ${name} COMMAND ${name})
endfunction()

enable_testing()

add_qt_test(test_geocoding geocoding)
add_qt_test(test_weather   weather)

