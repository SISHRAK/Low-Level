file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(image-transformer ${sources}
        include/enum.h
        include/defines.h)
target_include_directories(image-transformer PRIVATE src include)
