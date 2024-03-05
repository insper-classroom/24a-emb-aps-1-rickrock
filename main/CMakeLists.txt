add_executable(main main.c helpers/game.c helpers/sound.c helpers/config.c)

# pull in common dependencies
target_link_libraries(main pico_stdlib)

# specify where to find header files
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/helpers)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)
