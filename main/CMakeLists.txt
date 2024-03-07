add_executable(main main.c)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)

# pull in common dependencies and additional i2c hardware support
target_link_libraries(main pico_stdlib hardware_i2c)