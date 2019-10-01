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

add_custom_command(
    TARGET rooms
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "$<TARGET_FILE:rooms>"
        "${PROJECT_BINARY_DIR}/$<TARGET_FILE_NAME:rooms>"
)
