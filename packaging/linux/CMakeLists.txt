cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# Download latest release tarball
set(TARBALL "v${CMAKE_PROJECT_VERSION}.tar.gz")
set(TARBALL_URL "https://github.com/bartkessels/${CMAKE_PROJECT_NAME}/archive/refs/tags/${TARBALL}")
execute_process(COMMAND wget ${TARBALL_URL})

# Calculate hash
file(SHA256 ${TARBALL} TARBALL_HASH)

# Generate the getit.yml file
file(READ ${CMAKE_BINARY_DIR}/packaging/linux/getit-template.yml TEMPLATE)

string(REPLACE "{binary-name}" "${CMAKE_PROJECT_NAME}" TEMPLATE "${TEMPLATE}")
string(REPLACE "{tarball-url}" "${TARBALL_URL}" TEMPLATE "${TEMPLATE}")
string(REPLACE "{tarball-hash}" "${TARBALL_HASH}" TEMPLATE "${TEMPLATE}")

file(WRITE ${CMAKE_BINARY_DIR}/packaging/linux/getit.yml ${TEMPLATE})