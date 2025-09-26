add_executable(weather-2
    main.cpp

    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    settingsdialog.h
    settingsdialog.cpp
    settingsdialog.ui
)

target_link_libraries(weather-2 PRIVATE
    Qt6::Widgets
    Qt6::Network
    geocoding
    weather
)

target_include_directories(weather-2
    PUBLIC
        ${CMAKE_SOURCE_DIR}/libs
)
