add_library(geocoding
    geocoding/geocoding.cpp
    geocoding/geocoding.h
)

target_include_directories(geocoding
    PUBLIC
        geocoding/
)

target_link_libraries(geocoding PRIVATE Qt6::Network)
