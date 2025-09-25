add_library(geocoding
    geocoding/geocoding.cpp
    geocoding/geocoding.h
)

target_include_directories(geocoding
    PUBLIC
        geocoding/
)

add_library(weather
    weather/weather.cpp
    weather/weather.h
)

target_include_directories(weather
    PUBLIC
        weather/
)

target_link_libraries(geocoding PRIVATE Qt6::Network)
target_link_libraries(weather PRIVATE Qt6::Network)
