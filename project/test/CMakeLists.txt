add_executable(test1 test1_Part1.cpp )
add_executable(test2 test2_Part2.cpp)
add_executable(test5 test5_Part5.cpp)


target_link_libraries(test1 ${CImg_LIBRARIES} ${Eigen_LIBS} fingerprint)
target_link_libraries(test2 ${CImg_LIBRARIES} ${Eigen_LIBS} fingerprint)
target_link_libraries(test5 ${CImg_LIBRARIES} ${Eigen_LIBS} fingerprint)
