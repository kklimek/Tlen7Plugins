TARGET=dummy
TEMPLATE = lib

mac {
	postbuild.commands = cd ../ && ./tools/mac/deploy && cd ./postbuild

	QMAKE_EXTRA_TARGETS += postbuild	
	PRE_TARGETDEPS += postbuild
}
