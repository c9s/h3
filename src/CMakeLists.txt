include_directories(. ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src /opt/local/include /usr/include)


# add_library(target STATIC | SHARED | MODULE sources…)
add_library(libh3 hash.c header_field.c header_field_list.c mempool.c request_header.c scanner.c)
