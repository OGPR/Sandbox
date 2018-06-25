add_executable(mainApp mainApp.c)

target_link_libraries (mainApp LINK_PUBLIC functions X11)
