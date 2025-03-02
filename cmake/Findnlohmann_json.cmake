#if( TARGET nlohmann_json )
#  return()
#endif()

if(NOT NLOHMANNJSON_ROOT)
  set(NLOHMANNJSON_ROOT "${CPP_FRAMEWORKS_DIR}/nlohmann_json/json-3.11.3")
endif()

add_library( nlohmann_json INTERFACE )
target_include_directories(
  nlohmann_json
  INTERFACE
    ${NLOHMANNJSON_ROOT}/include
)
target_link_libraries(${PROJECT_NAME} nlohmann_json)