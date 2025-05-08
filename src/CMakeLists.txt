add_executable(pico_mqtt main.c functions.c lcd.c mqtt_functions.c)
target_include_directories(pico_mqtt PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(pico_mqtt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable USB output for debugging (if needed)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)


# Link required libraries
target_link_libraries(pico_mqtt 
    pico_stdlib
    hardware_gpio
    pico_cyw43_arch_lwip_threadsafe_background # requires headerfile in include folder lwipopts
    hardware_i2c
    pico_lwip_mqtt
)

pico_add_extra_outputs(pico_mqtt)

add_custom_command(
    TARGET pico_mqtt
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/src/pico_mqtt.uf2" # Antag att .uf2 hamnar direkt i build
    	    "${CMAKE_BINARY_DIR}/bin/pico_mqtt.uf2"
    )
