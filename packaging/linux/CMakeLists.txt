cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# Replace variables in prepare release script
execute_process(sed -i 's/{project-name}/${CMAKE_PROJECT_NAME}/' ${CMAKE_BINARY_DIR}/packaging/linux/prepare-release.sh)
execute_process(sed -i 's/{project-version}/${CMAKE_PROJECT_VERSION}/' ${CMAKE_BINARY_DIR}/packaging/prepare-release.sh)
execute_process(sed -i 's/{current-dir}/${CMAKE_BINARY_DIR}/' ${CMAKE_BINARY_DIR}/packaging/prepare-release.sh)

execute_process(${CMAKE_BINARY_DIR}/packaging/prepare-release.sh)
