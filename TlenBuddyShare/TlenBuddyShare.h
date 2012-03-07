#ifndef TLENBUDDYSHARE_H
#define TLENBUDDYSHARE_H

#include <plugin/TlenPlugin.h>
#include <PluginInfo.h>

class TlenBuddyShare: public TlenPlugin
{
public:
	QString name() const { return QString::fromLatin1("TlenBuddyShare"); }

	QString friendlyName() const { return QObject::tr("Share buddies"); }

	QString author() const { return AUTHOR; }
	QString web() const { return WEB; }
	QString email() const { return EMAIL; }

	QString icon(int) const { return QString(); }

	QString description() const { return QObject::tr("Send your buddies to your buddies. Easily send your contact list to your friends. Also supports import and export to Tlen 6 XML format file."); }

	int version() const { return TLEN_PLUGIN_VERSION(0,0,1); }

	bool load() { return true; }
	void unload() {}
	QString getLicenseName() { return LICENSE; }
};

#endif // TLENBUDDYSHARE_H

