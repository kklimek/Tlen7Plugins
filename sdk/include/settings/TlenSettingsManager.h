#ifndef _TLEN_SETTINGS_MANAGER_H_
#define _TLEN_SETTINGS_MANAGER_H_

#include <QString>

#include <core/export.h>

class TlenField;
class TlenSettingsManagerPrivate;
class TlenApplication;

/**
 * Służy do odczytywania i zapisywania ustawień programu, a także zwraca sciężki do katalogów
 * pobierania, ustawień, skórek.
 * \sa TlenPlugin::setPluginPref() - do zapisywania ustawień wtyczki
 * \sa TlenPlugin::getPluginPref() - do odczytywania ustawień wtyczki
 */
class __tlen_settings__ TlenSettingsManager
{
	public:
		static TlenSettingsManager *getInstance();

		/**
		 * Zwraca katalog z profilami
		 * @return katalog z profilami
		 */
		QString getProfilesDir() const;
		/**
		 * Zwraca katalog aktualnego profilu
		 * @return katalog aktualnego profilu
		 */
		QString getCurrentProfileDir() const;
		/**
		 * Zwraca katalog z plikami danych programu
		 * @return katalog z plikami danych programu
		 */
		QString getTlenDataDir() const;
		/**
		 * Zwraca katalog z ustawieniami
		 * @return katalog z ustawieniami
		 */
		QString getSettingsDir() const;
		/**
		 * Zwraca katalog z pluginami
		 * @return katalog z pluginami
		 */
		QString getPluginsDir() const;
		/**
		 * Zwraca katalog z kontami
		 * @return katalog z kontami
		 */
		QString getAccountsDir() const;
		/**
		 * Zwraca katalog cache
		 * @return katalog cache
		 */
		QString getCacheDir() const;
		/**
		 * Zwraca katalog pobierania
		 * @return katalog pobierania
		 */
		QString getDownloadDir() const;
		/**
		 * Zwraca katalog z aktualnym motywem emotikon
		 * @return katalog z aktualnym motywem emotikon
		 */
		QString getCurrentEmoticonsDir() const;
		/**
		 * Zwraca katalog z aktualnym motywem głównym
		 * @return katalog z aktualnym motywem głównym
		 */
		QString getCurrentThemeDir() const;
		/**
		 * Zwraca katalog z aktualnym stylem rozmowy
		 * @return katalog z aktualnym stylem rozmowy
		 */
		QString getCurrentChatThemeDir() const;
		/**
		 * Zwraca katalog z aktualnym motywem listy kontaktów
		 * @return katalog z aktualnym motywem listy kontaktów
		 */
		QString getCurrentRosterThemeDir() const;
		/**
		 * Zwraca katalog z aktualnym motywem powiadomień
		 * @return katalog z aktualnym motywem powiadomień
		 */
		QString getCurrentNotifyThemeDir() const;
		/**
		 * Zwraca katalog z aktualnym motywem dymków
		 * @return katalog z aktualnym motywem dymków
		 */
		QString getCurrentToolTipThemeDir() const;
		/**
		 * Zwraca katalog z aktualnym motywem dzwiękowym
		 * @return katalog z aktualnym motywem dzwiękowym
		 */
		QString getCurrentSoundThemeDir() const;
		/**
		 * Zwraca katalog, w którym przechowywane są motywy programu
		 * @return katalog, w którym przechowywane są motywy programu
		 */
		QString getThemesDir() const;
		/**
		 * Zwraca katalog programu
		 * @return katalog programu
		 */
		QString getApplicationDir() const;
		/**
		 * Odczytuje ustawienie programu
		 * @param field odczytywane ustawienie, które jest także domyślnym ustawieniem
		 * jeśli nie było wcześniej zapisane na dysku
		 * @return odczytane ustawienie
		 */
		TlenField readGlobalSetting(const TlenField &field) const;
		/**
		 * Zapisuje ustawienie programu
		 * @param field zapisywane ustawienie
		 */
		void writeGlobalSetting(const TlenField &field);
		/// @cond
		void readThemes();
		/// @endcond
		
	private:
		TlenSettingsManager();
		TlenSettingsManager(const TlenSettingsManager &);
		TlenSettingsManager operator=(const TlenSettingsManager &);
		~TlenSettingsManager();
		TlenSettingsManagerPrivate *d;
		friend class TlenApplication;
};


#define TLEN_SETTINGS_FORMAT QSettings::IniFormat

#endif

