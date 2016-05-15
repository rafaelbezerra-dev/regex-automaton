TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../parser/inorder_exp.cpp \
    ../../parser/main.cpp \
    ../../parser/regex_library.cpp \
    ../../parser/shungting_yard.cpp

HEADERS += \
    ../../parser/inorder_exp.hpp \
    ../../parser/regex_library.hpp \
    ../../parser/shungting_yard.hpp
