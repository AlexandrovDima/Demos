######################################################################
# Automatically generated by qmake (2.01a) ?? ???. 6 16:18:25 2015
######################################################################

TEMPLATE = app
TARGET = gateCtrl
DEPENDPATH += .

#DEFINES += MARKERS
DEFINES += WIN
DEFINES += QT6

QT += core\
        gui\
        network\
         widgets

CONFIG += qt\
          gui\
		  console \
		  static

HEADERS += \
		visual.h \
			udpV2.h \

SOURCES += \
		visual.cpp \
			 udpV2.cpp \
               main.cpp

FORMS += \
		visual.ui 

unix {
  UI_DIR = temp/.ui
  MOC_DIR = temp/.moc
  OBJECTS_DIR = temp/.obj
  OBJECTS_DIR = temp/.o
}

win32 {
  UI_DIR = temp/ui
  MOC_DIR = temp/moc
  OBJECTS_DIR = temp/obj
  OBJECTS_DIR = temp/o
}