add_executable(test1 test1_main.cpp)
target_link_libraries(test1 ${CImg_LIBRARIES} ${Eigen_LIBS} fingerprint)
