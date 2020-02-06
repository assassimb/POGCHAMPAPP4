TEMPLATE     = vcapp
TARGET       = testcarte
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += MonInterface.h switches.h centralwidget.h VisiTest.h vecteur.h leds.h macarte.h CommunicationFPGA.h
SOURCES     += Test.cpp MonInterface.cpp
INCLUDEPATH += ../S2APP3
LIBS	      += ../S2APP3/VisiTest.lib CommunicationFPGA.lib
QT += widgets
