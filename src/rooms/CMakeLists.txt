add_executable(rooms
    field_view.cpp
    frame_timer.cpp
    level.cpp
    main.cpp
    view.cpp
)

target_link_libraries(rooms PRIVATE SDL2::SDL2)
