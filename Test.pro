TEMPLATE     = vcapp
TARGET       = testcarte
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += MonInterface.h switches.h centralwidget.h VisiTest.h vecteur.h leds.h
SOURCES     += Test.cpp MonInterface.cpp
INCLUDEPATH += ../fixedpog
LIBS	      += ../fixedpog/VisiTest.lib
QT += widgets
