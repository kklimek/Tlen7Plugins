TEMPLATE=lib

CONFIG += plugin no_plugin_name_prefix

QT -= gui
QT += xml

QMAKE_EXTENSION_SHLIB=o2x

DESTDIR=../bin/

INCLUDEPATH += ../sdk/include/
INCLUDEPATH += ../include/

win32 {

}

unix:!macx {

}

macx {
	CONFIG += x86
	CONFIG -= x86_64
	LIBS += -L ../Frameworks/ -ltlen_plugin -ltlen_core -ltlen_data
}

