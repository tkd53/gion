SET(GION_VARSRC_PATH "${PROJECT_SOURCE_DIR}/var")

ADD_LIBRARY(gion SHARED
  Conv.cc
)

SET_TARGET_PROPERTIES(gion PROPERTIES
  PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/gion.hh
)

# WordIntStr.sh は無茶苦茶な暫定処理。。。不要な場合はコメントアウトしてください。
ADD_CUSTOM_TARGET(kkcintstr
  COMMAND sh ${GION_VARSRC_PATH}/KkciIntStr.sh ${GION_VARSRC_PATH}/KkciIntStr.text ${PROJECT_SOURCE_DIR}/src/KkciIntStr.h
#  COMMAND sh ${GION_VARSRC_PATH}/WordIntStr.sh ${GION_VARSRC_PATH}/WordIntStr.text ${PROJECT_SOURCE_DIR}/src/WordIntStr.h
)

ADD_DEPENDENCIES(gion kkcintstr)

INSTALL(TARGETS gion
  LIBRARY        DESTINATION lib
  PUBLIC_HEADER  DESTINATION include/gion
)
