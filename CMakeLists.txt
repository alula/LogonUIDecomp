project(LogonUI)

add_executable(LogonUI WIN32
    main.cpp
)

target_link_libraries(LogonUI
    ${CMAKE_CURRENT_SOURCE_DIR}/LogonUI.res
)

set_target_properties(LogonUI PROPERTIES OUTPUT_NAME LogonUI)
