add_executable(rooms
    field.cpp
    field_view.cpp
    frame_timer.cpp
    game.cpp
    level.cpp
    main.cpp
    view.cpp
)

target_link_libraries(rooms PRIVATE geometry)

target_link_libraries(rooms PRIVATE SDL2::SDL2)
