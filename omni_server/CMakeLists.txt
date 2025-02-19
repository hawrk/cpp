cmake_minimum_required(VERSION 3.10)
project(omni_server)

add_compile_options(-Wall -O2)

set(CMAKE_CXX_STANDARD 17)

set(OTA_SRC_LIST internal/ota/ota_mng_query.cpp
        internal/ota/ota_mng_upgrade.cpp
        internal/ota/ota_mng_rollback.cpp
        internal/ota/ota_app_manager.cpp)

set(COMMON_SRC_LIST common/tc_file.cpp
        common/curl_lib.cpp
        common/crypto_suite.cpp)

set(HANDLER_SRC_LIST handler/omni_handler.cpp
        handler/router.cpp)

set(SRC_LIST ${COMMON_SRC_LIST} ${OTA_SRC_LIST} )


add_executable(hv_demo test/main.cpp ${SRC_LIST})
target_link_libraries(hv_demo PUBLIC hv z archive)
target_link_libraries(hv_demo PUBLIC ssl crypto curl)


add_executable(test_crypto test/test_crypto_suite.cpp ${COMMON_SRC_LIST})
target_link_libraries(test_crypto PUBLIC ssl crypto curl z archive)


add_executable(http_server test/http_server.cpp)
target_link_libraries(http_server PUBLIC hv)

add_executable(tcp_server test/tcp_server.cpp)   
target_link_libraries(tcp_server PUBLIC hv)

add_executable(tcp_client_cxx test/tcp_client_cxx.cpp)
target_link_libraries(tcp_client_cxx PUBLIC hv)

add_executable(test_curl test/test_curl_lib.cpp ${COMMON_SRC_LIST})
target_link_libraries(test_curl PUBLIC ssl crypto curl z archive)

add_executable(test_app_manager test/test_app_manager.cpp ${SRC_LIST})
target_link_libraries(test_app_manager PUBLIC  ssl crypto curl z archive)

add_executable(omni_server omni_server.cpp  ${SRC_LIST} ${HANDLER_SRC_LIST})
target_link_libraries(omni_server PUBLIC hv z archive) 
target_link_libraries(omni_server PUBLIC ssl crypto curl)