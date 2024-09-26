add_library(
        libcontact STATIC
        Contact.hpp
        ContactsService.hpp
        ContactsService.cpp
)

target_include_directories(libcontact PUBLIC ../network ../utils)

target_link_libraries(libcontact utils network_lib)
