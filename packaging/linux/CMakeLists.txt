cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# Download latest tarball
set(TARBALL "v${CMAKE_PROJECT_VERSION}.tar.gz")
set(TARBALL_URL "https://github.com/bartkessels/${CMAKE_PROJECT_NAME}/archive/refs/tags/${TARBALL}")
download_file(${TARBALL_URL})

# Generate hash for tarball
file(SHA256 ${TARBALL} TARBALL_HASH)

# Replace variables in yaml file
execute_process(sed -i 's/{tarball-url}/${TARBALL_URL}/' ${CMAKE_BINARY_DIR}/linux/getit.yml)
execute_process(sed -i 's/{tarball-hash}/${TARBALL_HASH}/' ${CMAKE_BINARY_DIR}/linux/getit.yml)