add_executable(mainApp.bin mainApp.c)

target_link_libraries (mainApp LINK_PUBLIC functions X11)
