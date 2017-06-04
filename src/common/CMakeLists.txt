add_library(net_common str.c text.c net.c commands.c)
target_include_directories(net_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})