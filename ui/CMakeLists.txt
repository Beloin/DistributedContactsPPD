add_library(
        ui STATIC
        QTContacts.hpp
        QTContacts.cpp
)

target_link_libraries(ui
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        libcontact
)

target_include_directories(ui PUBLIC ../contacts)
