# Build Test List
add_executable(testList
  testList.cpp
  list.hpp)
target_link_libraries(testList
  ${GLFW_LIBRARIES})
