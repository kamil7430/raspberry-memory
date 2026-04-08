add_executable (memory_game memory.c)
install (TARGETS memory_game DESTINATION bin)

target_link_libraries (memory_game periphery) 
