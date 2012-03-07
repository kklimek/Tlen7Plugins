#ifndef TLENBUDDYSHARE_H
#define TLENBUDDYSHARE_H

#include <plugin/TlenPlugin.h>
#include <PluginInfo.h>

class TlenBuddyShare: public TlenPlugin
{
public:
	TlenBuddyShare(): tlenProto(NULL) {}

	QString name() const { return QString::fromLatin1("TlenBuddyShare"); }

	QString friendlyName() const { return QObject::tr("Share buddies"); }

	QString author() const { return AUTHOR; }
	QString web() const { return WEB; }
	QString email() const { return EMAIL; }

	QString icon(int) const { return QString(); }

	QString description() const { return QObject::tr("Send your buddies to your buddies. Easily send your contact list to your friends. Also supports import and export to Tlen 6 XML format file."); }

	int version() const { return TLEN_PLUGIN_VERSION(0,0,1); }

	QString getLicenseName() { return LICENSE; }

	bool load();
	void unload();

	TLEN_DECLARE_SLOT(showContextMenu);
	TLEN_DECLARE_SLOT(protocolLoaded);
	TLEN_DECLARE_SLOT(protocolUnloaded);
	TLEN_DECLARE_SLOT(onXmlNode);
	TLEN_DECLARE_SLOT(chatWindowCreated);

	TLEN_DECLARE_ACTION(sendContacts);

private:
	TlenXmlProtocol * tlenProto;
};

#endif // TLENBUDDYSHARE_H

