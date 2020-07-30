cmake_minimum_required(VERSION 2.8.3)
project(oxford_gps_eth_all)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  sensor_msgs
  nav_msgs
  tf
  message_generation
)

add_message_files(
   FILES
   event_time.msg
   output_all.msg
)

generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
CATKIN_DEPENDS message_runtime 
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_gps_node src/node.cpp)
target_link_libraries(${PROJECT_NAME}_gps_node ${catkin_LIBRARIES})
set_target_properties(${PROJECT_NAME}_gps_node PROPERTIES OUTPUT_NAME gps_node PREFIX "")

install(TARGETS ${PROJECT_NAME}_gps_node
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(DIRECTORY launch
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

#if (CATKIN_ENABLE_TESTING)
#  add_subdirectory(tests)
#endif()
