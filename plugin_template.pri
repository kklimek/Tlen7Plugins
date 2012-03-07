TEMPLATE=lib

CONFIG += plugin no_plugin_name_prefix
CONFIG += release
CONFIG -= debug debug_and_release

QT -= gui
QT += xml

QMAKE_EXTENSION_SHLIB=o2x

lrelease.commands = lrelease *.pro

QMAKE_EXTRA_TARGETS += lrelease
PRE_TARGETDEPS += lrelease

DESTDIR=../bin/

INCLUDEPATH += ../sdk/include/
INCLUDEPATH += ../include/

win32 {

}

unix:!macx {

}

macx {
	isEmpty(TLEN_LIBS_PATH) {
		TLEN_LIBS_PATH=/Applications/Tlen.app/Contents/Frameworks/
	}

	CONFIG += x86
	CONFIG -= x86_64
	LIBS += -L$${TLEN_LIBS_PATH} -ltlen_plugin -ltlen_core -ltlen_data
}
