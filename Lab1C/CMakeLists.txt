#add_executable(Lab1C lab1.c task1.c task2.c)
#target_include_directories(Lab1C PUBLIC ../LibraryC)
#target_link_libraries(Lab1C LibraryC)
add_executable(task1 task1.c lab1.c)  
add_executable(task2 task2.c lab1.c)
target_include_directories(task1 PRIVATE ../LibraryC)
target_include_directories(task2 PRIVATE ../LibraryC)
target_link_libraries(task1 LibraryC)
target_link_libraries(task2 LibraryC)

add_test(NAME Task1_Mixed COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt)
set_tests_properties(Task1_Mixed PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 9.*0: 1.*-: 0")

add_test(NAME Task1_AllPositive COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.txt)
set_tests_properties(Task1_AllPositive PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 5.*0: 0.*-: 0")

add_test(NAME Task1_AllNegative COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test6.txt)
set_tests_properties(Task1_AllNegative PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 0.*0: 0.*-: 6")

add_test(NAME Task2_WithDuplicates COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test7.txt)
set_tests_properties(Task2_WithDuplicates PROPERTIES 
    PASS_REGULAR_EXPRESSION "1 4")

add_test(NAME Task2_NoDuplicates COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test8.txt)
set_tests_properties(Task2_NoDuplicates PROPERTIES 
    PASS_REGULAR_EXPRESSION "^[ \t]*$")