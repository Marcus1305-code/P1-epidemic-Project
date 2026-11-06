#igen har kan ses flere function hvor man tilføjer flere c filer til main
#add_library(calculator calculator.c)
#target_link_libraries(calculator m)
#target_include_directories(calculator PUBLIC .)

add_executable(epidemic_model main.c)
#hvis der er andre c filer som skal virke sammen med main brug denne function
