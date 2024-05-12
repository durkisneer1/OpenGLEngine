project(
    'sdldemo', 'c', 'cpp',
    default_options: [
        'default_library=static',
        'c_std=c17',
        'cpp_std=c++17'
    ]
)

subdir('src')
sources += 'external/glad/glad.c'
sources += 'external/stb/std_image.cpp'
sources += 'main.cpp'

executable(
    'app',
    sources: sources,
    include_directories: [
        include_directories('external'),
        include_directories('include')
    ],
    win_subsystem: 'console',
    dependencies: [
        dependency('sdl2'),
        dependency('gl'),
        dependency('glm')
    ]
)
