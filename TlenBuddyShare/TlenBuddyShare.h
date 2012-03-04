#ifndef TLENBUDDYSHARE_H
#define TLENBUDDYSHARE_H

#include <plugin/TlenPlugin.h>
#include <PluginInfo.h>

class TlenBuddyShare: public TlenPlugin
{
public:
	QString name() const { return QString::fromLatin1("TlenBuddyShare"); }
	QString author() const { return AUTHOR; }
	QString web() const { return WEB; }
	QString email() const { return EMAIL; }

	QString icon(int) const { return QString(); }

	QString description() const { return QObject::tr("Easily export and import buddies. Uses Tlen 6 contact list xml format."); }

	int version() const { return TLEN_PLUGIN_VERSION(0,0,1); }

	bool load() { return true; }
	void unload() {}
};

#endif // TLENBUDDYSHARE_H

