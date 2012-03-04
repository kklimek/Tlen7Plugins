#ifndef __TLEN_PLUGIN_MANAGER_H__
#define __TLEN_PLUGIN_MANAGER_H__

#include <QString>
#include <QStringList>

#include <core/export.h>
#include <data/TlenArg.h>
#include <plugin/TlenPluginLoader.h>

class TlenPluginManagerPrivate;
class TlenPlugin;
class TlenProtocol;

/**
 * Służy do zarządzania pluginami
 */
class __tlen_plugin__ TlenPluginManager {
	
	public:
		static TlenPluginManager *getInstance();		
	
		/**
		 * Zwraca nazwy zarejstrowanych protokołów
		 * @return nazwy protokołów
		 */
		QStringList getRegisteredProtocolNames() const;
		/**
		 * Zwraca zarejestrowane protokoły
		 * @return zarejestrowane protokoły
		 */
		QList<TlenProtocol *> getRegisteredProtocols() const;
		/**
		 * Zwraca nazwy załadowanych pluginów
		 * @return nazwy załadowanych pluginów
		 */
		QStringList getLoadedPluginNames() const;
		/**
		 * Zwraca załadowane pluginy
		 * @return pluginy
		 */
		QList<TlenPlugin *> getLoadedPlugins() const;
		/**
		 * Zwraca pluginy posiadające daną usługę
		 * @param service nazwa serwisu
		 * @return 
		 */
		QList<TlenPlugin *> getPluginsWithService(const QString &service) const;
		/**
		 * Zwraca informacje o wszystkich pluginach, także tych niewłaczonych.
		 * @return informacje o pluginach
		 */
		QList<TlenPluginData *> getPlugins() const;
		/**
		 * Zwraca informacje o dostępnych protokołach, także tych niewłaczonych.
		 * @return 
		 */
		QList<TlenPluginData *> getAvailableProtocols() const;
		/**
		 * Zwraca informacje o pluginie o podanym id
		 * @param pid id
		 * @return informacje o pluginie
		 */
		TlenPluginData * getPluginInfoById(const QString &pid) const;	
		/**
		 * Zwraca plugin o podanej nazwie
		 * @param name nazwa pluginu
		 * @return plugin
		 */
		TlenPlugin *getPluginByName(const QString &name);
		/**
		 * Zwraca plugin protokołu o podanej nazwie
		 * @param name nazwa protokołu
		 * @return plugin obsługujący dany protokół
		 */
		TlenProtocol *getProtocolByName(const QString &name);

	private:
		TlenPluginManager();
		TlenPluginManager(const TlenPluginManager&);
		TlenPluginManager operator=(const TlenPluginManager &);
		~TlenPluginManager();
		static TlenPluginManager *instance;
		TlenPluginManagerPrivate *d;
		friend class TlenApplication;		
};

#endif
