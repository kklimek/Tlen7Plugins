TARGET = TlenBuddyShare

include(../plugin_template.pri)
include(../common/RosterModel.pri)

SOURCES += TlenBuddyShare.cpp

HEADERS += TlenBuddyShare.h

QT += network gui

RESOURCES += \
	TlenBuddyShare.qrc
TRANSLATIONS += TlenBuddyShare_pl_PL.ts

unix {
	LIBS += -ltlen_xml -ltlen_gui_chat_manager -ltlen_gui_chat_window -ltlen_gui_context_menu -ltlen_roster
}


