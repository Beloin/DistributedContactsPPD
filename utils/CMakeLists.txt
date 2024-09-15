add_library(
        utils STATIC
        split.cpp
        split.hpp
)

target_link_libraries(utils
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)
