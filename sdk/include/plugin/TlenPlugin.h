#ifndef _TLEN_PLUGIN_H_
#define _TLEN_PLUGIN_H_

#include <QList>
#include <QPair>
#include <QString>

#include <data/TlenArg.h>
#include <data/TlenField.h>
#include <data/TlenPluginAction.h>
#include <data/TlenService.h>
#include <plugin/TlenPluginTypes.h>
#include <plugin/TlenPluginDefines.h>
#include <plugin/TlenPluginRosterHandler.h>

class TlenPlugin;
class TlenPluginLoader;
class TlenFieldWidget;
class TlenPluginPrivate;
class TlenPluginManager;
class TlenApplication;
class QWidget;

/**
 * \brief Klasa bazowa wszystkich wtyczek w Tlenie.
 *
 * Aby stworzyć wtyczkę należy zadeklarować klasę dziedziczącą z TlenPlugin
 * \code
 * class MojaWtyczka: public TlenPlugin
 * {
 * 	public:
 * 		MojaWtyczka();
 * 		bool load();
 * 		void unload();
 * 		...
 * };
 * \endcode
 *
 * Należy także zaimplementować wszystkie wymagane metody (kompilator powie których brakuje). \n
 * \n
 * Po zdefiniowaniu wszystkich metod należy wywołać makro podając nazwę klasy naszej wtyczki
 * \code
 * MojaWtyczka::MojaWtyczka()
 * {
 * 	...
 * }
 *
 * bool MojaWtyczka::load()
 * {
 *	...
 * }
 *
 * void MojaWtyczka::unload()
 * {
 * 	...
 * }
 *
 * TLEN_INIT_PLUGIN(MojaWtyczka)
 * \endcode
 */

class __tlen_plugin__ TlenPlugin
{
	public:
		enum Type {
			Standard = 0,
			Protocol,
			PluginLoader
		};
	
	
		/**
		 * Zwraca typ wtyczki
		 * @return typ wtyczki
		 */
		TlenPlugin::Type getType() const;
	
		/**
		 * Nazwa wtyczki nie powinna byc nigdy tlumaczona (nie powinna byc zawarta w tlen_tr)
		 * @return nazwa wtyczki
		 */
		virtual QString name() const = 0;
		
		/**
		 * Nazwa wtyczki, ktora powinna byc tlumaczona
		 * @return nazwa wtyczki
		 */
		virtual QString friendlyName() const;
		
		/**
		 * Id wtyczki. Składa się z nazwy plugin loadera dla danej wtyczki oraz nazwy wtyczki
		 * @return 
		 */
		QString getPluginId() const;

		/**
		 * @return nazwa pliku z ikonką wtyczki
		 */
		virtual QString icon(int size=0) const = 0;

		/**
		 * @return autor wtyczki
		 */
		virtual QString author() const = 0;

		/**
		 * @return opis wtyczki
		 */
		virtual QString description() const = 0;

		/**
		 * @return wersja wtyczki. Wersję wtyczki należy tworzyć makrem TLEN_PLUGIN_VERSION np. TLEN_PLUGIN_VERSION(1,0,0) odpowiada wersji 1.0.0
		 */
		virtual int version() const = 0;

		/**
		 * @return strona domowa
		 */
		virtual QString web() const = 0;

		/**
		 * @return adres kontaktowy
		 */
		virtual QString email() const = 0;

		/**
		 * Zwraca zbior obslugiwanych uslug, usluga - zbior sygnalow wysylanych przez wtyczke
		 */
		virtual QList<TlenService> getProvidedServices() const;

		/**
		 * Zwraca z jakimi ustawieniami jest powiazana wtyczka w celu umieszczania odpowiednich
		 * powiazan miedzy wtyczkami w oknie ustawien programu.
		 */
		virtual QStringList getSettingsTags() const {return QStringList();}
		
		/**
		 * Zwraca linki powiazane z wtyczka wyswietlane w oknie ustawien wtyczki
		 */
		virtual QList<QPair<QString, QString> > getSettingsLinks() const {return QList<QPair<QString, QString> >();}

		/**
		 * Zwraca frazy dla wyszukiwarki w ustawieniach
		 */
		virtual QStringList getSearchPhrases() const;

		/**
		 * @return nazwa licencji
		 */
		virtual QString getLicenseName();

		/**
		 * @return wektor zawierajacy TlenField opisujace ustawienia wtyczki
		 */
		QList<TlenField> getPluginPrefs() const;

		/** Wtyczki, ktore chca same obslugiwac swoja strone ustwien musza zwracac sciezke do swojego pliku UI
		 * @return nazwa ui ze strona ustawien
		 */
		QString getPluginSettingsUi() const;

		/**
		 * Wtyczka dostaje wskaznik do utworzonej strony ustawien po przejsciu na nia przez uzytkownika
		 * @param wskaznik do okna ustwien wtyczki
		 */
		virtual void setSttingsUi(QWidget *widget) {}

		/**
		 * @param id - id ustawienia
		 * @return TlenField opisujacy ustawienie wtyczki
		 */
		TlenField getPluginPref(const QString &id) const;


		/**
		 * Metoda zmienia wartosc ustawienia
		 * @param id - nazwa pola
		 * @param value - nowa wartosc pola
		 * @retun true jesli pole o nazwie podanej w zmiennej label zostalo znalezione
		 */
		bool setPluginPref(const QString &id, const TlenArg &value, bool update=true);
		
		/**
		 * Metoda zmienia wartosc ustawienia
		 * @param id - nazwa pola
		 * @param value - nowa wartosc pola
		 * @retun true jesli pole o nazwie podanej w zmiennej label zostalo znalezione
		 */
		bool setPluginPref(const QString &id, const QString &selected_id, const QStringList &idList, const QStringList &labelList = QStringList());

		/**
		 * Zmeinia ustawienia wtyczki na podstawie wektoru TlenField
		 * @param fields - wektor zawierajacy TlenFields opisujace nowe ustawienia wtyczki
		 */
		void setPluginPrefs(const QList<TlenField> &fields);

		/**
		 * @return wektor zawierajacy nazwy wtyczek ktore sa wymagane przy ladowaniu wtyczki
		 */
		QStringList getPluginDeps() const;

		/**
		 * @return bezwględna scieżka do cache przeznaczonego dla wtyczki
		 */
		QString getCacheDir() const;

		/**
		 * @return lista zarejestrowanych przez wtyczke sygnałów. Jeśli wtyczka jest niezaładowana, to lista jest pusta.
		 */
		QStringList getRegisteredSignals() const;		
		
		/**
		 * Zapisuje ustawienia wtyczki na dysku
		 */
		void writeSettings();
	
		/**
		 * Zwraca obiekt odpowiedzialny za obsługę specjalnych kontaktów dodawanych przez plugin
		 * do listy kontaktów
		 */
		virtual TlenPluginRosterHandler * getRosterHandler() const
		{
			return NULL;
		}
	
	protected:
	
		TlenPlugin();
		virtual ~TlenPlugin();
	
		/**
		 * Metoda uruchamiająca wtyczkę\n
		 * UWAGA: wtyczka nie musi sama pobierać ustawien, zostaną one załadowane przed wywołaniem tej metody
		 * @return true jeśli udało się załadować poprawnie wtyczkę
		 */
		virtual bool load() = 0;

		/**
		 * Metoda wywoływana przy wyładowywaniu wtyczki
		 * UWAGA: wtyczka nie musi sama zapisywać ustawień, ustawienia zapisywane są od razu po wywołaniu tej metody
		 */
		virtual void unload() = 0;
	
		virtual void pluginPrefsUpdated();
		
		/**
		 * Metoda rejestrujaca sygnal wtyczki
		 * @param signal - nazwa sygnalu
		 * @param args - parametry uzyte przy emitowaniu sygnalu
		 */
		void signalRegister(const QString &signal, const QList<TlenArg::Type> &args);

		/**
		 * metoda wyrejestrowujaca sygnal
		 * @param signal - nazwa sygnalu
		 */
		void signalUnregister(const QString &signal);

		/**
		 * metoda emitujaca sygnal
		 * @param signal - nazwa sygnalu
		 * @param arglist - wektor zawierajacy liste argumentow przekazywanych z sygnalem
		 */
		void signalEmit(const QString &signal, QList<TlenArg> arglist);
		
		/**
		 * podlacza wtyczke do sygnalu podanego nadawcy
		 * @param sender - nazwa nadawcy sygnalu
		 * @param signal - nazwa sygnalu
		 * @param callback - wskaznik na metode wtyczki np. TLEN_SLOT(MojaWtyczka::MojaMetoda)
		 * @return true jesli udalo sie podlaczyc do sygnalu, false jesli nadawca lub sygnal nadawcy nie istnieje
		 * UWAGA: metoda ta zawsze zwraca true jesli polaczenie nastepuje w trakcie ladowania wtyczek
		 */
		bool slotConnect(const QString &sender, const QString &signal, TlenPluginSlot slot);

		/**
		 * odlacza wtyczke od sygnalu
		 * @param sender - nazwa nadawcy sygnalu
		 * @param signal - nazwa sygnalu
		 * @param callback - wskaznik na metode wtyczki np. TLEN_SLOT(MojaWtyczka::MojaMetoda)
		 */
		void slotDisconnect(const QString &sender, const QString &signal, TlenPluginSlot);

		/**
		 * Ustawia plik ui jako strone ustawien
		 * @param ui - nazwa ui
		 * @param receiver - "odbiornik" wiadomosci z ui
		 */
		void setPluginSettingsUi(const QString &ui);

		/**
		 * Updatuje ui ustawien na podstawie TlenField.
		 */
		void updatePluginSettingsUi();

		/**
		 * Dodaje pole ustawien wtyczki
		 * @param field - pole
		 */
		void addPluginSettingsField(const TlenField &field);

		/**
		 * Dodaje nazwe wtyczki do zaleznosci
		 * @param pluginname - nazwa dodawanej do zaleznosci wtyczki
		 */
		void addPluginDependency(const QString &pluginname);

		/**
		 * Puszcza powiadomienie
		 * @param nid id
		 * @param title tytuł
		 * @param text tekst
		 * @param iconpath ikonka
		 * @param groupiconpath ikonka grupowania
		 * @param action akcja
		 * @param args argumenty dla akcji
		 */
		void postNotification(const QString &nid, const QString &title, const QString &text, const QString &iconpath = QString(), const QString &groupiconpath = QString(), const TlenPluginAction &action = TlenPluginAction(), const QList<TlenArg> &args=QList<TlenArg>());

		
	private:
	
		friend class TlenPluginLoader;
		friend class TlenProtocol;
		friend class TlenPluginManagerPrivate;
		friend class TlenPluginManager;
		friend class TlenApplication;
		TlenPluginPrivate * pluginPrivate;
};


#ifdef _WIN32
#	ifdef __cplusplus
#		define TLEN_EXPORT extern "C" __declspec(dllexport)
#	else
#		define TLEN_EXPORT __declspec(dllexport)
#	endif
#else
#	ifdef __cplusplus
#		define TLEN_EXPORT extern "C"
#	else
#		define TLEN_EXPORT
#	endif
#endif

#define TLEN_PLUGIN_VERSION(maj,min,rev) ((maj<<16)+(min<<8)+rev)

#define TLEN_PLUGIN_CORE "__TlenPluginCore"
#define TLEN_PLUGIN_GUI "__TlenPluginGui"
#define TLEN_PLUGIN_ROSTER "__TlenPluginRoster"

#define TLEN_API_VERSION 3

#define TLEN_INIT_PLUGIN(ClassName) static ClassName plugin_handle; \
	TLEN_EXPORT TlenPlugin *get_plugin_handle() { return &plugin_handle; } \
	TLEN_EXPORT int get_api_version() { return TLEN_API_VERSION; }	
	

#endif // _TLEN_PLUGIN_H_
