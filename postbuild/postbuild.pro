TARGET=dummy
TEMPLATE = lib

include(../common.pri)

mac {
	postbuild.commands = cd ../ && ./tools/mac/deploy $${TLEN_LIBS_PATH} && ./tools/mac/install && cd ./postbuild

	QMAKE_EXTRA_TARGETS += postbuild
	PRE_TARGETDEPS += postbuild
}
