add_executable(Lab3C lab3.c)
target_include_directories(Lab3C PUBLIC ../LibraryC)
target_link_libraries(Lab3C LibraryC)

add_executable(vector_tests vector_test.c)
target_include_directories(vector_tests PRIVATE ../LibraryC)
target_link_libraries(vector_tests LibraryC)
add_test(NAME MyVectorTests COMMAND vector_tests)

add_executable(queue_tests queue_test.c)
target_include_directories(queue_tests PRIVATE ../LibraryC)
target_link_libraries(queue_tests LibraryC)
add_test(NAME MyQueueTests COMMAND queue_tests)
set_tests_properties(MyVectorTests MyQueueTests PROPERTIES TIMEOUT 10)

add_test(NAME PuzzleExample COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/example.txt)
set_tests_properties(PuzzleExample PROPERTIES
    TIMEOUT 30
    PASS_REGULAR_EXPRESSION "^312456780\n312450786\n310452786\n301452786\n031452786\n431052786\n431502786\n401532786\n410532786\n412530786\n412503786\n412053786\n012453786\n102453786\n120453786\n123450786\n123456780\n$")

add_test(NAME PuzzleSolved COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/solved.txt)
set_tests_properties(PuzzleSolved PROPERTIES
    TIMEOUT 30
    PASS_REGULAR_EXPRESSION "^123456780\n$")

add_test(NAME PuzzleOneMove COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/one_move.txt)
set_tests_properties(PuzzleOneMove PROPERTIES
    TIMEOUT 30
    PASS_REGULAR_EXPRESSION "^123456708\n123456780\n$")

add_test(NAME PuzzleTwoMoves COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/two_moves.txt)
set_tests_properties(PuzzleTwoMoves PROPERTIES
    TIMEOUT 30
    PASS_REGULAR_EXPRESSION "^123456078\n123456708\n123456780\n$")

add_test(NAME PuzzleHard COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/hard.txt)
set_tests_properties(PuzzleHard PROPERTIES
    TIMEOUT 30
    PASS_REGULAR_EXPRESSION "^867254301\n867204351\n807264351\n087264351\n287064351\n287364051\n287364501\n287364510\n287360514\n280367514\n208367514\n268307514\n268037514\n268537014\n268537104\n268537140\n268530147\n260538147\n206538147\n236508147\n236058147\n236158047\n236158407\n236158470\n236150478\n230156478\n203156478\n023156478\n123056478\n123456078\n123456708\n123456780\n$")

add_test(NAME PuzzleImpossible COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/impossible.txt)
set_tests_properties(PuzzleImpossible PROPERTIES
    TIMEOUT 30
    PASS_REGULAR_EXPRESSION "^нет решения\n$")

add_test(NAME PuzzleWhitespace COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/whitespace.txt)
set_tests_properties(PuzzleWhitespace PROPERTIES
    TIMEOUT 30
    PASS_REGULAR_EXPRESSION "^123456708\n123456780\n$")

add_test(NAME PuzzleFail_duplicate COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/duplicate.txt)
set_tests_properties(PuzzleFail_duplicate PROPERTIES WILL_FAIL TRUE TIMEOUT 30)

add_test(NAME PuzzleFail_short COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/short.txt)
set_tests_properties(PuzzleFail_short PROPERTIES WILL_FAIL TRUE TIMEOUT 30)

add_test(NAME PuzzleFail_extra COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/extra.txt)
set_tests_properties(PuzzleFail_extra PROPERTIES WILL_FAIL TRUE TIMEOUT 30)

add_test(NAME PuzzleFail_invalid COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/invalid.txt)
set_tests_properties(PuzzleFail_invalid PROPERTIES WILL_FAIL TRUE TIMEOUT 30)

add_test(NAME PuzzleFail_empty COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/empty.txt)
set_tests_properties(PuzzleFail_empty PROPERTIES WILL_FAIL TRUE TIMEOUT 30)

add_test(NAME PuzzleFail_missing COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/tests/missing.txt)
set_tests_properties(PuzzleFail_missing PROPERTIES WILL_FAIL TRUE TIMEOUT 30)

add_test(NAME PuzzleNoArgument COMMAND Lab3C)
set_tests_properties(PuzzleNoArgument PROPERTIES WILL_FAIL TRUE TIMEOUT 30)
