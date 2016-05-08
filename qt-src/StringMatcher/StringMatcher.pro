TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    nfa.cpp \
    symbol.cpp \
    transition.cpp \
    state.cpp \
    dfa.cpp \
    utils.cpp \
    matcher.cpp \
    unittest.cpp

HEADERS += \
    nfa.h \
    symbol.h \
    transition.h \
    state.h \
    dfa.h \
    utils.h \
    matcher.h \
    unittest.h \
    console_color.h
