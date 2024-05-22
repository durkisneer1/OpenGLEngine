project(
    'sdldemo', 'c', 'cpp',
    license: 'MIT',
    license_files: 'LICENSE.txt',
    default_options: [
        'default_library=static',
        'c_std=c17',
        'cpp_std=c++17',
        'warning_level=2'
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
