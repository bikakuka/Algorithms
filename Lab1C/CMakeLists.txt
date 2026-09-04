add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

add_test(NAME Test1_Mixed COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt)
set_tests_properties(Test1_Mixed PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 9.*0: 1.*-: 0.*1")

add_test(NAME Test2_MixedNegative COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.txt)
set_tests_properties(Test2_MixedNegative PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 2.*0: 1.*-: 3.*1 2 3")

add_test(NAME Test3_AllPositive COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.txt)
set_tests_properties(Test3_AllPositive PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 5.*0: 0.*-: 0.*6")

add_test(NAME Test4_ZerosAndNegative COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4.txt)
set_tests_properties(Test4_ZerosAndNegative PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 0.*0: 2.*-: 2.*1")

add_test(NAME Test5_LargeArray COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5.txt)
set_tests_properties(Test5_LargeArray PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 8.*0: 0.*-: 0")

add_test(NAME Test6_AllZeros COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test6.txt)
set_tests_properties(Test6_AllZeros PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 0.*0: 3.*-: 0.*1 4")
    
add_test(NAME Test7_OutOfBoundUp COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test7.txt)
set_tests_properties(Test7_OutOfBoundUp PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 0.*0: 3.*-: 0.*some values are greather than 1000 or lower than 0, please input data in \\[0, 1000\\] interval")

add_test(NAME Test8_OutOfBoundDown COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/tests/test8.txt)
set_tests_properties(Test8_OutOfBoundDown PROPERTIES 
    PASS_REGULAR_EXPRESSION "\\+: 0.*0: 3.*-: 0.*some values are greather than 1000 or lower than 0, please input data in \\[0, 1000\\] interval")