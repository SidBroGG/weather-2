find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(weather-2
    main.cpp

    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    settingsdialog.h
    settingsdialog.cpp
    settingsdialog.ui
)

target_link_libraries(weather-2 PRIVATE Qt6::Widgets)
