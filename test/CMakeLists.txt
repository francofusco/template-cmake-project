# add one test
add_executable(test_foo test_foo.cpp)
# link GTest and pthread
target_link_libraries(test_foo
  ${PROJECT_NAME}
  ${GTEST_LIBRARIES}
  pthread
)
# make the test runnable by ctest
gtest_discover_tests(test_foo)


# add a second test, it uses "fixtures"
add_executable(test_fixture test_fixture.cpp)
# link GTest and pthread
target_link_libraries(test_fixture
  ${PROJECT_NAME}
  ${GTEST_LIBRARIES}
  pthread
)
# make the test runnable by ctest
gtest_discover_tests(test_fixture)
