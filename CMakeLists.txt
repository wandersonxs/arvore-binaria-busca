cmake_minimum_required(VERSION 4.0)
project(arvore_binaria_busca C)

set(CMAKE_C_STANDARD 11)

add_executable(arvore_binaria_busca
        main.c
        main.h
        BST.c
        BST_pri.h
        BST_pub.h
        )
