#ifndef __TLEN_PLUGIN_LOADER_H__
#define __TLEN_PLUGIN_LOADER_H__

#include <plugin/TlenPlugin.h>
#include <plugin/TlenPluginTypes.h>

typedef struct __tlen_plugin__ _TlenProtocolPresenceData {
	QString id;
	QString display;
	QString icon;
} TlenProtocolPresenceData;

typedef struct __tlen_plugin__ _TlenProtocolData {
	QString protocolId;
	QList<TlenField> accountSettings;
	QList<TlenProtocolPresenceData> presence;
	QString validIdMask;
} TlenProtocolData;


// struktura przetrzymujaca opis wtyczki dla np. dialogu wyswietlajacego informacje o wtyczce
// dane te dostepne sa bez ladowania wtyczki

typedef struct __tlen_plugin__ _TlenPluginData {
	_TlenPluginData():
	protocolData(NULL),
	loaded(false)
	{
	}

	~_TlenPluginData()
	{
		delete protocolData;
	}

	QString name;
	QString friendlyName;
	QString author;
	QString descr;
	int version;
	QString www;
	QString email;
	QString fname;
	QStringList deps;
	QString loader;
	QString icon;
	QString mediumIcon;
	QString bigIcon;
	QString license;
	QStringList settingsTags;
	QStringList searchPhrases;
	QList<QPair<QString, QString> > settingsLinks;
	QList<TlenField> settings;
	QList<TlenService> services;
	TlenPlugin::Type type;
	
	TlenProtocolData * protocolData;
	
	bool loaded;
	bool hasUi;
	
} TlenPluginData;

class __tlen_plugin__ TlenPluginLoader: public TlenPlugin
{
public:
	TlenPluginLoader();
	virtual ~TlenPluginLoader();
	virtual QList<TlenPluginData *> getPluginList() const = 0;
	virtual TlenPlugin *pluginLoad(const QString &) const = 0;
	virtual QString getLoaderId() const = 0;
	virtual void pluginUnload(TlenPlugin *) const;
	virtual QStringList defaultPluginList() const {return QStringList();}
	
protected:
	QStringList getPluginsWithExtension(const QString &ext) const;
	LibraryHandle loadLibrary(const QString &path) const;
	LibraryHandle loadLibrary(const char *) const;
	void *getSymbol(LibraryHandle handle, const char *symbol) const;
	bool freeLibrary(LibraryHandle handle) const;
	void setPluginLibraryHandle(TlenPlugin *p, LibraryHandle) const;
	
private:
	friend class TlenPluginManagerPrivate;
};

#endif
