ADD_EXECUTABLE(gion_sample
  sample.cc)

TARGET_LINK_LIBRARIES(gion_sample gion)

INSTALL(TARGETS gion_sample DESTINATION bin)
