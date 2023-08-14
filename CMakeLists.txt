cmake_minimum_required(VERSION 3.5)

project(guess_the_number)

add_executable(guess_the_number
    main.cpp
    args.h
    args.cpp
    game.h
    game.cpp
    storage.h
    storage.cpp
)

add_executable(guess_the_number_test
    main_test.cpp
    args.h
    args.cpp    
    game.h
    game.cpp
    storage.h
    storage.cpp
)

