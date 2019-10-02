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

target_link_libraries(rooms PRIVATE SDL2 SDL2main)

if(MSVC)
    add_custom_command(
        TARGET rooms
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2>" "$<TARGET_FILE_DIR:rooms>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2main>" "$<TARGET_FILE_DIR:rooms>"
    )
endif()