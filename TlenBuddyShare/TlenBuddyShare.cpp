#include <QDebug>
#include <QThread>
#include <QApplication>

#include <data/TlenBuddy.h>

#include <plugin/TlenAccountConnection.h>
#include <plugin/TlenProtocol.h>
#include <plugin/TlenXmlProtocol.h>
#include <plugin/TlenPluginManager.h>

#include <gui/TlenAction.h>
#include <gui/TlenChatManager.h>
#include <gui/TlenChatWindow.h>

#include <roster/TlenRoster.h>

#include "TlenBuddyShare.h"

#define CWACTION QString::fromLatin1("send_contacts")
#define CWMENU QString::fromLatin1("send")

bool TlenBuddyShare::load()
{
	// na przyszłość, może będziemy wspierać więcej protokołów
	bool loaded = slotConnect(TLEN_PLUGIN_CORE, LOADED_PROTOCOL, TLEN_SLOT(TlenBuddyShare::protocolLoaded));
	// j.w.
	loaded &= slotConnect(TLEN_PLUGIN_CORE, UNLOADED_PROTOCOL, TLEN_SLOT(TlenBuddyShare::protocolUnloaded));

	TlenPluginManager *mgr = TlenPluginManager::getInstance();

	// wyciągamy interesujący nas protokół
	foreach(TlenProtocol *proto, mgr->getRegisteredProtocols())
	{
		if(proto->getPluginId() == QLatin1String("Tlen.pl"))
		{
			// tylko protokół tlen
			tlenProto = static_cast<TlenXmlProtocol *>(proto);
			// łapiemy node, żeby parsować swoje rzeczy
			loaded &= slotConnect(tlenProto->getPluginId(), XML_PROTOCOL_ON_NODE, TLEN_SLOT(TlenBuddyShare::onXmlNode));
		}
	}

	// do okien rozmowy też wstawiamy akcję
	loaded &= slotConnect(TLEN_PLUGIN_GUI, CHAT_WINDOW_CREATED, TLEN_SLOT(TlenBuddyShare::chatWindowCreated));

	return loaded;
}

void TlenBuddyShare::unload()
{
	tlenProto = NULL;

	// usuwamy akcje z istniejących okien rozmowy
	foreach(TlenChatWindow *chatWindow, TlenChatManager::getInstance()->getExistingChatWindows())
	{
		chatWindow->removeToolbarAction(CWACTION);
	}
}

// akcja wywoływana z okna rozmowy w celu wybrania kontaktów do wysłania
TLEN_DEFINE_ACTION(TlenBuddyShare, sendContacts)
{
	// musi być wątek gui
	if( QThread::currentThread() != qApp->thread() )
		return;

	// wyciągamy okno
	TlenChatWindow * cw = static_cast<TlenChatWindow *>(args[0].toPointer());

	// kontakt
	TlenBuddy b = cw->getBuddy();

	if(b.getType() == TlenBuddy::Contact)
	{
		TlenBuddyContact contact(b);
		contact.getId();

		TlenAccountConnection * acc = contact.getAccount();

		// wyciągamy lisę kontaktów dla konta. Na razie wspieramy tylko wysyłanie ze swojego konta
		QList<TlenBuddy> blist = TlenRoster::getInstance()->getBuddiesForAccount(acc);

		// otwieramy widget wyboru kontaktów

		// budujemy node xml

		//TlenXmlNode node(QString::fromLatin1("message"));
		//node.setAttribute(QString::fromLatin1("to"), contact.getId());
		//node.setAttribute(QString::fromLatin1("type"), QString::fromLatin1("buddyshare"));
		//budujemy strukturę

		//tlenProto->writeData(acc, node);
	}
}

// slot wołany po utworzeniu okna rozmowy
TLEN_DEFINE_SLOT(TlenBuddyShare, chatWindowCreated)
{
	// nie ma tlenu, nie ma życia
	if( ! tlenProto )
		return;

	// wyciągamy okno
	TlenChatWindow *chatWindow = static_cast<TlenChatWindow *>(args[0].toPointer());

	// kontakt
	TlenBuddy b = chatWindow->getBuddy();

	if(b.getType() == TlenBuddy::Contact)
	{
		TlenBuddyContact contact(b);

		TlenAccountConnection * acc = contact.getAccount();

		// tylko dla kont z protokołu tlen
		if(acc->getProtocol() == tlenProto)
		{
			// tworzymy i dodajemy akcję
			TlenAction action(QObject::tr("Send contacts"), QString(), TlenPluginAction(this, TLEN_ACTION(TlenBuddyShare::sendContacts)));
			chatWindow->addToolbarAction(action, CWMENU, CWACTION);
		}
	}
}

TLEN_DEFINE_SLOT(TlenBuddyShare, onXmlNode)
{
	TlenXmlNode xmlNode = args[1].toXmlNode();
	TlenAccountConnection * acc = args[0].toAccount();
	// node message dla protokołu tlen nas interesuje
	if(acc->getProtocol() == tlenProto && xmlNode.name() == QLatin1String("message"))
	{
		if(xmlNode.getAttribute("type") == QLatin1String("buddyshare"))
		{
			// nasza wiadomość z kontaktami, trzeba sparsować
		}
	}
}

TLEN_DEFINE_SLOT(TlenBuddyShare, protocolLoaded)
{
	qDebug() << args.size();

	foreach(const TlenArg &arg, args)
	{
		qDebug() << arg.getTypeName();
	}

	qDebug() << args[0].toString();
}

TLEN_DEFINE_SLOT(TlenBuddyShare, protocolUnloaded)
{
	qDebug() << args[0].toString() << args[1].toString();
}

TLEN_INIT_PLUGIN(TlenBuddyShare)
