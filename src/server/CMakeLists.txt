add_executable(netedit-server load.c main.c)
target_link_libraries(netedit-server LINK_PUBLIC net_common)