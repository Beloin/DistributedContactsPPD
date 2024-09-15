add_library(
        libcontact STATIC
)

target_link_libraries(libcontact)

target_include_directories(libcontact PUBLIC ../network)
