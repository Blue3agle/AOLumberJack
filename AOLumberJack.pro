#-------------------------------------------------
#
# Project created by QtCreator 2016-12-17T19:58:51
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

TARGET = AOLumberJack
TEMPLATE = app

SOURCES += main.cpp\
    MainWindow.cpp \
    t_entity.cpp \
    t_event.cpp \
    t_eventHandler_log.cpp \
    t_logLine.cpp \
    t_parser.cpp \
    qcustomplot.cpp \
    t_entityList.cpp \
    t_eventHandler_damage_taken_agg.cpp \
    t_eventHandler_damage_taken.cpp \
    t_eventHandler_damage_given_agg.cpp \
    t_eventHandler_damage_given.cpp \
    t_eventHandler_hit_type_table.cpp

HEADERS  += \
    MainWindow.h \
    t_entity.h \
    t_event.h \
    t_eventHandler_log.h \
    t_logLine.h \
    t_parser.h \
    qcustomplot.h \
    t_entityList.h \
    t_eventHandler_damage_given.h \
    t_eventHandler_damage_given_agg.h \
    t_eventHandler_damage_taken_agg.h \
    t_eventHandler_damage_taken.h \
    t_eventHandler_hit_type_table.h

FORMS    += mainwindow.ui
