#ifndef _TLEN_PROTOCOL_H_
#define _TLEN_PROTOCOL_H_

#include <QString>

#include <core/export.h>
#include <plugin/TlenPlugin.h>
#include <network/TlenSocket.h>
#include <data/TlenPresence.h>
#include <data/TlenTextFormat.h>

class TlenBuddyContact;
class TlenBuddyTemporary;
class TlenBuddyResourceType;
class TlenSubscriptionType;
class TlenProtocolPrivate;
class TlenAutoBlockerPlugin;
class TlenEditAccountDialog;
class TlenSettingsManagerPrivate;

struct __tlen_plugin__ TlenConferenceUserStatus
{
	enum Status{
		Anonymous=0,
		Registered,
		Owner,
		Admin,
		Member,
		Outcast,
		Superuser,
		BannedGlobaly
	};
};
 
struct __tlen_plugin__ TlenProtocolFeatures
{
	enum Features{
		Conference=1,
		ConferenceEchoMessage=2,
		Chats=4,
		Alerts=8,
		PubdirSearch=16,
		MessageSubject=32,
		ConferenceInvite=64,
		Reserved2=128,
		Reserved3=256,
		Reserved4=512
	}; 
};
 
struct __tlen_plugin__ TlenConferencePrivileges
{
	enum Privileges{
		Invite=1,
		Kick=2,
		KickReason=4,
		KickTime=8,
		TopicDisplay=16,
		TopicChange=32,
		GrantAdmin=64,
		GrantOwner=128,
		RemoveRoom=256,
		ListUsers=512
	}; 
};
 


/**
 * \brief Bazowa klasa wszystkich wtyczek dostarczających usługę protokołu
 *
 * Aby utworzyć wtyczkę dostarczającą protokół należy zadeklarować klasę dziedziczącą z TlenProtocol i zaimplementować wszystkie wymagane
 * metody, także te, które dostarcza TlenPlugin (ponieważ TlenProtocol dziedziczy z TlenPlugin)
 * \code
 * class MojProtokol: public TlenProtocol
 * {
 * 	public:
 * 		MojProtokol();
 *
 * 		bool load();
 * };
 * \endcode
 * 
 * W konstruktorze rejestrujemy typy prezencji, subskrypcji oraz kontaktow. Kolejność dodania prezencji będzie odzwierciedlona w menu zmiany prezencji. Dodatkowo KAŻDY protokół musi dostarczyć po jednej prezencji z flagami
 * TlenPresenceType::Available, TlenPresenceType::Away i TlenPresenceType::Unavailable. Próba dodania więcej niż jednej prezencji z jedną z zarezerwowanych flag przerwie program.
 * \code
 * MojProtokol::MojProtokol
 * {
 * 	addPresenceType(tlen_tr("My presence"), "my_presence_icon.png", 2, TlenPresenceType::Available);
 * 	addPresenceType(tlen_tr("My away presence", "my_away_presence_icon.png", 2, TlenPresenceType::Away);
 * 	addPresenceType(tlen_tr("My Other presence", "my_other_presence_icon.png", 1);
 * 	addPresenceType(tlen_tr("Unavailable presence"), "my_unavailable_presence_icon.png", 0, TlenPresenceType::Unavailable);
 *
 * 	addSubscriptionType(tlen_tr("My subscription"), "moja_subskrypcja_1", 1);
 * 	addSubscriptionType(tlen_tr("Other subscription"), "moja_subskrypcja_2", 0);
 *
 * 	...
 * }
 * \endcode
 *
 * Ważny też jest identyfikator protokołu. Jeśli w programie jest już zarejestrowany protokół o tym samym identyfikatorze, wtedy rejestracja nie uda się.
 */
class __tlen_plugin__ TlenProtocol: public TlenPlugin
{
	public:
		/**
		 * \brief enum ten opisuje czy użytkownik zaczął pisać do innego użytkownika
		 */
		enum TypingNotify {
			TypingStarted, /**< Użytkownik zaczął pisać */
			TypingPaused, /**< Użytkownik przerwał na chwilę pisanie */
			TypingStoped /**< Użytkownik przestał pisać */
		};
			
		enum InfoType {
			Meta,
			Tags,
			ExtraInfo,
			Reserved1,
			Reserved2,
			Reserved3
		};	
			
		TlenProtocol();
	
		virtual ~TlenProtocol();
		
		QStringList getSettingsTags() const;
		void updateProtocolPresenceIcons();
		
		virtual int protocolFeatures() const{return 0;}
		virtual int conferencePrivileges(const QString &confId) const {return 0;}
		virtual QStringList predefinedConfigurations() const {return QStringList();}
		virtual QList<TlenField> predefinedConfiguration(const QString &name) const {return QList<TlenField>();}
		virtual QList<TlenField> roomConfiguration() const {return QList<TlenField>();}
		
		
		virtual QString getProtocolUrl() const {return QString();}

		/**
		 * Metoda ta jest wywolywana gdy uzytkownik zechce zalogowoac konto protokolu
		 * lub przy samym starcie programu jesli opcja automatycznego logowania jest wlaczona
		 * @param acc - wskaznik na TlenAccountConnection, zawierajace wszystkie informacje o koncie (w tym prezencje, ktora chcemy miec po zalogowaniu)
		 */
		virtual void loginAccount(TlenAccountConnection *acc) = 0;

		/**
		 * Zmienia prezencje konta
		 * @param acc - wskaznik na TlenAccountConnection, zawierajace wszystkie informacje o koncie
		 * @param presence - nowa prezencja konta
		 */
		virtual void changePresence(TlenAccountConnection *acc, const TlenPresence &presence) = 0;

		/**
		 * Wysyla wiadomosc do uzytkownika (wskaznik na TlenAccountConnection nie jest podawany gdyz zawiera go TlenBuddy)
		 * @param acc - konto, z którego wysyłamy wiadomość
		 * @param bid - identyfikator kontaktu do którego wysyłamy wiadomość
		 * @param msg - wiadomosc sformatowana w postaci HTML
		 * @param resource - zasób kontaktu
		 */
		virtual void sendMessage(TlenAccountConnection *acc, const QString &bid, const QString &msg, const QString &resource, const QString & subject = QString()) = 0;
		
		virtual void sendConferenceMessage(TlenAccountConnection *acc, const QString &confId, const QString &msg,const QList<TlenTextFormat>& params) {}
		virtual void sendPrivateConferenceMessage(TlenAccountConnection *acc, const QString &confId, const QString &buddyId, const QString &msg,  const QList<TlenTextFormat>& params) {}		
		virtual void setConferenceTopic(TlenAccountConnection *acc, const QString &confId, const QString &topic) {}

		/**
		 * Wysyla powiadomienie o tym ze uzytkownik zaczal pisac w oknie rozmowy
		 * @param acc - konto, z którego wysyłamy powiadomienie
		 * @param bid - identyfikator kontaktu do ktorego wysylamy powiadomienie
		 * @param type - typ powiadomienia
		 * @param resource - zasób kontaktu
		 */
		virtual void sendTypingNotify(TlenAccountConnection *acc, const QString &bid, TlenProtocol::TypingNotify type, const QString &resource) {}

		/**
		 * Wysyla alert do rozmowcy
		 * @param acc - konto, z którego wysyłamy alert
		 * @param bid - identyfikator kontaktu do ktorego wysylamy powiadomienie
		 * @param resource - zasób kontaktu
		 */
		virtual void sendAlert(TlenAccountConnection *acc, const QString &bid, const QString &resource) {}
	
		virtual void requestUserVersion(TlenAccountConnection *acc, const QString &bid, const QString &resource) {}

		/**
		 * Ustawia avatar konta
		 * @param acc - konto któremu zmieniamy avatar
		 * @param avatarpath - scieżka do pliku z avatarem
		 */
		virtual void setAccountAvatar(TlenAccountConnection *acc, const QString &avatarpath);

		/**
		 * Pobiera avatar konta.
		 * @param acc - konto którego avatar chcemy pobrać
		 */
		virtual void getAccountAvatar(TlenAccountConnection *acc);

		/**
		 * Usuwa avatar konta
		 * @param acc - konto, któremu uswamy avatar
		 */
		virtual void removeAccountAvatar(TlenAccountConnection *acc) {}

		/**
		 * Aktualziuje dane publiczne konta
		 * @param acc - wskaznik na TlenAccountConnection, zawierajace dane publiczne konta
		 * @param fields - lista pol danych publicznych konta
		 */
		virtual void updateAccountPubdirInfo(TlenAccountConnection *acc, const QList<TlenField> &fields) = 0;

		/**
		 * Pobiera dane publiczne konta
		 * @param acc - wskaznik na TlenAccountConnection
		 * Dane publiczne zostana przekazane sygnalem account_pubdir_received
		 */
		virtual void getAccountPubdirInfo(TlenAccountConnection *acc) = 0;

		/**
		 * Usuwa dane publiczne konta
		 * @param acc - wskaznik na TlenAccountConnection
		 */
		virtual void removeAccountPubdirInfo(TlenAccountConnection *acc) = 0;

		/**
		 * Wyszukuje w katalogu publicznym wg podanych danych
		 * @param acc - konto, dla którego szukamy
		 * @param data - dane wg kórych szukamy
		 */
		virtual void searchPubdir(TlenAccountConnection *acc, const QList<TlenField> &data, int page = 0){}

		/**
		 * Wyszukuje w katalogu publicznym wg identyfikatora użytkownika
		 * @param acc - konto, dla którego szukamy
		 * @param data - identyfikator którego szukamy
		 */
		virtual void searchPubdir(TlenAccountConnection *acc, const QString &uid){}
		
		virtual void getLastActivity(TlenAccountConnection *acc, const QString &uid){}

		/**
		 * metoda reagujaca na nawizanie polaczenia z serwerem
		 * @param acc - wskaznik na TlenAccountConnection, zawierajace wszystkie informacje o koncie
		 */
		virtual void socketConnected(TlenAccountConnection *acc) = 0;

		/**
		 * metoda reagujaca na rozlaczenie sie z serwerem
		 * @param acc - wskaznik na TlenAccountConnection, zawierajace wszystkie informacje o koncie
		 */
		virtual void socketDisconnected(TlenAccountConnection *acc) = 0;

		/**
		 * metoda reagujaca na wystapienie bledu w probie nawiazania polaczenia z serwerm lub w trkacie jego trwania
		 * @param acc - wskaznik na TlenAccountConnection, zawierajace wszystkie informacje o koncie
		 * @param errype - typ bledu
		 */
		virtual void socketError(TlenAccountConnection *acc, TlenSocket::Error errtype) = 0;

		virtual void peerVerifyError(TlenAccountConnection *acc, const QList<TlenSocket::SslError> &er);
	
		virtual void accountConnectionEncrypted(TlenAccountConnection *acc);
	
		/**
		 * metoda reagujace na dane dostepne w sockecie
		 * @param acc - wskaznik na TlenAccountConnection, zawierajace wszystkie informacje o koncie
		 * @param data - dane wyczytane z socketu konta
		 */
	
		virtual void socketReadyRead(TlenAccountConnection *acc);
	
		virtual void socketReadyRead(TlenAccountConnection *acc, const QByteArray &data);

		/**
		 * utrzymywanie polaczenia z serwerem
		 * @param acc - wskaznik na TlenAccountConnection
		 */
		virtual void ping(TlenAccountConnection *acc) {}

		/**
		 * Czas miedzy pingami w sekundach
		 */
		virtual unsigned pingInterval() const = 0;

		/**
		 * Metoda wywolywana gdy kontakt został aktywowany.\n
		 * Aktywowany kontakt to taki, ktory albo został kliknięty dwa razy, albo został wcisnięty enter w liscie kontaktów gdy był zaznaczony\n
		 * Domyślnie metoda zwraca false. 
		 * Jeśli protokoł chce obsługiwać aktywowane kontakty na swój sposób, należy reimplementować tą metodę i zwrocic true.
		 * @param contact - aktywowany kontakt
		 * \sa temporaryActivated(const TlenBuddyTemporary &)
		 */
		virtual bool contactActivated(const TlenBuddyContact &contact);

		/**
		 * Metoda wywoływana gdy kontakt tymczasowy został aktywowany.\n
		 * Aktywowany kontakt to taki, ktory albo został kliknięty dwa razy, albo został wcisnięty enter w liscie kontaktów gdy był zaznaczony\n
		 * Domyślnie metoda zwraca false. 
		 * Jeśli protokoł chce obsługiwać aktywowane kontakty na swój sposób, należy reimplementować tą metodę i zwrocic true.
		 * @param contact - aktywowany kontakt
		 * \sa contactActivated(const TlenBuddyContact &)
		 */
		virtual bool temporaryActivated(const TlenBuddyTemporary &contact);
		
		/**
		 * @return Lista ustawień protokołu
		 */
		QList<TlenField> getProtocolSettings() const;

		/**
		 * Zmienia ustawienie protokolu
		 * @param id - nazwa pola w ustawieniach
		 * @param value - nowa wartosc pola
		 * @return false jesli pole o nazwie label nie istnieje
		 */
		bool setProtocolPref(const QString &id, const TlenArg &value);

		/**
		 * Zmienia ustawienia protokolu na podstawie listy 
		 * @param fields - wektor zeminionych ustawien
		 */
		void setProtocolPrefs(const QList<TlenField> &fields);

		/**
		 * Pobiera strukture ustawien specyficznych dla konta
		 * @return wektor zawierajacy TlenField opisujacy strukture ustawien konta
		 */
		QList<TlenField> getAccountSettings() const;

		/**
		 * Pobiera strukture dodatkowych informacji o kontakcie
		 * @return wektor zawierajacy TlenField opisujacy strukture informacji o kontakcie
		 */
		QList<TlenField> getBuddyExtraInfo() const;

		/**
		 * Pobiera strukture danych publicznych dla konta
		 * @return wektor zawierajacy TlenField opisujacy strukture danych publicznych konta
		 */
		QList<TlenField> getPubdirAccountFields() const;

		/**
		 * Zwraca pola opisujace kolumny wynikow wyszukiwania w katalogu publicznym
		 * @return wektor zawierajacy TlenField opisujace kolumny wynikow wyszukiwania
		 */
		QList<TlenField> getPubdirResultColumns() const;

		/**
		 * @return wektor zawierający TlenField opisujący strukturę podstawowych danych do wyszukiwania
		 */
		QList<TlenField> getPubdirBaseSearchFields() const;

		/**
		 * @return wektor zawierajacy TlenField opisujące strukturę zaawansowanych danych do wyszukiwania
		 */
		QList<TlenField> getPubdirAdvancedSearchFields() const;

		/**
		 * Sprawdza czy typy prezencji z wymaganymi flagami istnieją
		 * @return true jeśli istnieją, w przeciwnym przypadku false
		 */
		bool hasRequiredPresenceTypes() const;
		
		bool hasRequiredPresenceType(TlenPresence::Flag) const;
		
		bool hasRequiredPresenceType(const QString &id) const;

		virtual void writeData(TlenAccountConnection *acc, const QByteArray &data, qint64 size = -1);
		virtual void writeData(TlenAccountConnection *acc, const TlenXmlNode &node);

		bool isXmlProtocol() const;
		
		virtual QString toFullId(const QString& id){return id;}
		virtual QString toShortId(const QString& id){return id;}
		virtual QString validIdMask(){return "[#|A-Z|a-z|0-9|_|\\-|.|@]+";}
		virtual int maxDescriptionLength()=0;
		virtual void launchMail(TlenAccountConnection *acc, const QString &url = QString());
			
		/**
		 * Tworzy prezencje z podaną flagą, lub pustą prezencję, jeśli paramter flag ma wartość TlenPresence::NoFlag
		 * @param flag - flaga prezencji
		 * @param descr - stan opisowy prezencji
		 *
		 * @return utworzona prezencja
		 */
		TlenPresence createPresenceWithFlag(TlenPresence::Flag flag, const QString &descr = QString()) const;

		/**
		 * Tworzy prezencję z podanym id i opisem, lub pustą prezencję, jeśli podany identyfikator nie został zarejestrowany przez protokół
		 * @param id - identyfikator prezencji
		 * @param descr - stan opisowy prezencji
		 *
		 * @return utworzona prezencja
		 */
		TlenPresence createPresenceWithId(const QString &id, const QString &descr = QString()) const;

		QList<TlenPresence> getAllPresences() const;

		/**
		 * Dodaje service dla danego protokolu.
		 * @param service - service
		 */
		void addService(const TlenService &service);
		
		/**
		 * Usuwa service z danego protokolu.
		 * @param service - service
		 */
		void removeService(const TlenService &service);
		
		/**
		 * Zwraca dany service dla protokolu. Jeśli taki nie istnieje zwraca nieprawidłowy.
		 *
		 * @return dany service
		 */
		TlenService getService(const QString &service);
		/**
		 * Zwraca wszystkie service dla danego protokolu.
		 *
		 * @return lista service
		 */
		QList<TlenService> getServices();
		
		bool hasService(const QString &service);
		
		virtual void requestAuthorization(const TlenBuddyContact &buddy);
		
		void imageReceived(TlenAccountConnection *acc, const QString &bid, const QString &image, const QString &timestamp, const QString &res);
		void imageSent(TlenAccountConnection *acc, const QString &bid, const QString &image, const QString &res);
		
		virtual void startConference(TlenAccountConnection *acc, const QStringList &buddies){}
		virtual void enterConference(TlenAccountConnection *acc, const QString &roomId, const QString &anonymousId=QString()){}
		virtual void leaveConference(TlenAccountConnection *acc, const QString &confId){}
		virtual void inviteToConference(TlenAccountConnection *acc, const QString &confId, const QString &buddyId){}
		virtual void kickFromConference(TlenAccountConnection *acc, const QString &confId, const QString &buddyId, const QString &reason=QString(), int time=0){}
		virtual void conferenceListGroups(TlenAccountConnection *acc, const QString &parent){}
		virtual void conferenceListRooms(TlenAccountConnection *acc, const QString &groups){}
		virtual void createConferenceRoom(TlenAccountConnection *acc, const QString &roomId, const QString &groupId, const QList< TlenField > &conf, const QString &anonymousId=QString()){}
		virtual void listMyRooms(TlenAccountConnection *acc){}
		virtual void listUsers(TlenAccountConnection *acc, const QString &roomId, TlenConferenceUserStatus::Status userType){}
		virtual void deleteMyRoom(TlenAccountConnection *acc, const QString &roomId){}
		virtual void listUsers(TlenAccountConnection *acc, const QString &roomId){}
		virtual void registerNick(TlenAccountConnection *acc, const QString &nick){}
		virtual void unregisterNick(TlenAccountConnection *acc, const QString &nick){}
		virtual void getRegisteredNicks(TlenAccountConnection *acc) {}
		virtual void grantBuddyConference(TlenAccountConnection *acc, const QString &confId, const QString &buddyId, TlenConferenceUserStatus::Status status){}
		
		virtual void exportAdditionalContactsInfo(InfoType type, TlenAccountConnection * acc){}

	protected:
		
		/**
		 * Dodaje kontakt do listy (za pomocą protokołu)
		 * @param buddy - dodawany kontakt
		 */
		virtual void addContact(const TlenBuddyContact &buddy) {}

		/**
		 * Usuwa kontakt z listy (za pomocą protokołu)
		 * @param buddy - usuwany kontakt
		 */
		virtual void removeContact(const TlenBuddyContact &buddy) {}

		/**
		 * Zmienia informacje o kontakcie (za pomocą protokołu)
		 * @param buddy - aktualizowany kontakt
		 */
		virtual void updateContact(const TlenBuddyContact &buddy) {}

		/**
		 * Metoda pomocnicza emitujaca sygnal message_received
		 * @param acc - konto, na które przyszła wiadomość
		 * @param bid - identyfikator kontaktu
		 * @param msg - wiadomosc
		 * @param timestamp - znacznik czasu. Moze byc pusty, wtedy wstawiona zostanie aktualna godzina.\n
		 * Znacznik czasu musi miec format DDMMYYYYhhmmss\n
		 * DD - dzien miesiaca (poprzedzony znakiem 0 jesli zajmuje 1 znak) od 01 do 31\n
		 * MM - miesiac (poprzedzony znakiem 0 jesli zajmuje 1 znak) od 01 do 12\n
		 * YYYY - rok\n
		 * hh - godzina od 00 do 23\n
		 * mm - minuty od 00 do 59\n
		 * ss - sekundy od 00 do 59\n
		 * @param restype - typ zasobu z którego przyszła wiadomość
		 */
		void messageReceived(TlenAccountConnection *acc, const QString &bid, const QString &msg, const QString &timestamp, const QString &res, const QString &subject = QString());

		/**
		 * Metoda pomocnicza emitujaca sygnal message_sent
		 * @param acc - konto, z którego wiadomość została wysłana
		 * @param bid - identyfikator kontaktu
		 * @param msg - wyslana wiadomosc
		 * @param res - zasób kontaktu, do którego wiadomość została wysłana
		 */
		void messageSent(TlenAccountConnection *acc, const QString &bid, const QString &msg, const QString &res);

		/**
		 * Metoda pomocnicza emitujaca sygnal typing_notify_received
		 * @param acc - konto, na które przyszło powiadomienie
		 * @param bid - identyfikator kontaktu
		 * @param type - typ powiadomienia
		 * @param res - zasób kontaktu, z którego przyszło powiadomienie
		 */
		void typingNotifyReceived(TlenAccountConnection *acc, const QString &bid, TlenProtocol::TypingNotify type, const QString &res);

		/**
		 * Metoda pomocnicza emitujaca sygnal "alert_received"
		 * @param acc - konto, na które przyszedł alert
		 * @param bid - identyfikator kontaktu
		 * @param res - zasób kontaktu, z kórego przyszedł alert
		 */
		void alertReceived(TlenAccountConnection *acc, const QString &bid, const QString &res);

		void emailReceived(TlenAccountConnection *acc, const QString &from, const QString &topic, const QString &msg, const QString &url);

		void emailOpened(TlenAccountConnection *acc, const QString &url, const QByteArray &cookie);
		
		/**
		 * Metoda pomocnicza emitujaca sygnal account_logged_in
		 * @param account - wskaznik na polaczenie konta
		 */
		void accountLoggedIn(TlenAccountConnection *acc);

		/**
		 * Metoda pomocnicza emitujaca sygnal account_resource_changed
		 * @param account - wskaznik na polaczenie konta
		 * @param resource - nowy zasob konta
		 */
		void accountResourceChanged(TlenAccountConnection *, const QString &);
	
		/**
		 * Metoda pomocnicza emitujaca sygnal account_logged_out
		 * @param account - wskaznik na polaczenie konta
		 */
		void accountLoggedOut(TlenAccountConnection *);
		
		/**
		 * Metoda pomocnicza emitujaca sygnal account_authorization_error, komunikator moze zazadac ponownego wpisania nazwy uzytkownika i/lub hasla
		 * @param account - wskaznik na polaczenie konta
		 */
		void accountAuthorizationError(TlenAccountConnection *);

		/**
		 * Metoda pomocnicza emitujaca sygnal account_presence_changed
		 * @param account - wskaznik na polaczenie konta (prezencja zawarta jest w tym wskazniku)
		 */
		void accountPresenceChanged(TlenAccountConnection *account);


		/**
		 * Metoda pomocnicza emitujaca sygnal pubidr_account_data_received
		 * @param account - wskaznik na polaczenie konta
		 * @param pubinfo - wektor informacji o koncie
		 */
		void accountPubdirInfoReceived(TlenAccountConnection *acc, const QList<TlenField> &pubinfo);

		/**
		 * Metoda pomocnicza emitujaca sygnal pubdir_account_data_edited
		 * @param account - wskaznik na polaczenie konta
		 */
		void accountPubdirInfoEdited(TlenAccountConnection *acc);

		/**
		 * Metoda pomocnicza emitujaca sygnal pubdir_account_data_removed
		 * @param account - wskaznik na polaczenie konta
		 */
		void accountPubdirInfoRemoved(TlenAccountConnection *acc);

		/**
		 * Metoda pomocnicza emitująca sygnał account_avatar_set
		 * @param account - konto
		 * @param avatarpath - scieżka do pliku z avatarem
		 */
		void accountAvatarSet(TlenAccountConnection *account, const QString &avatarpath);

		/**
		 * Metoda pomocnicza emitująca sygnał account_avatar_set_error
		 * @param account - konto
		 * @param errorstring - treść komunikatu o błędzie
		 */
		void accountAvatarSetError(TlenAccountConnection *account, const QString &errorstring);

		/**
		 * Metoda pomocnicza emitująca sygnał account_avatar_removed
		 * @param account - konto
		 */
		void accountAvatarRemoved(TlenAccountConnection *account);

		/**
		 * Metoda pomocnicza emitująca sygnał account_avatar_received
		 * @param account - konto
		 * @param avatarpath - sciezka do pobranego avataru
		 */
		void accountAvatarReceived(TlenAccountConnection *account, const QString &avatarpath);

		/**
		 * Metoda pomocnicza. Emituje sygnal pubdir_search_result_received.
		 * @param acc - wskaznik na polaczenie konta
		 * @param perPage - ilość rekordów na jedną stronę
		 * @param result - wektor TlenArg zawierajacych opis wynikow. Kazdy TlenArg musi byc typu TlenArg::FieldList (za pomoca TlenField opisane sa wyniki), oraz dodatkowo pierwszy element listy TlenField musi byc typu TlenField::LineEdit, i miec identyfikator "id"
		 * @param more - czy dostępne więcej wyników
		 */
		void pubdirSearchResultReceived(TlenAccountConnection *acc, int perPage, const QList<TlenArg> &result, bool more);

		void lastActivityReceived(TlenAccountConnection *acc, const QString &bid, int secs);

		/**
		 * dodaje pole ustawien protokolu
		 * @param type - typ pola
		 * @param label - nazwa pola (powinna byc umieszczona w tlen_tr jesli w przyszlosci mamy zamiar tlumaczyc na inne jezyki)
		 * @param value - domyslna wartosc pola
		 */
		void addProtocolSettingsField(const TlenField &f);

		/**
		 * dodaje pole ustawien konta
		 * @param type - typ pola
		 * @param label - nazwa pola (powinna byc umieszczona w tlen_tr jesli w przyszlosci mamy zamiar tlumaczyc na inne jezyki)
		 * @param value - domyslna wartosc pola
		 */
		void addAccountSettingsField(const TlenField &f);

		/**
		 * dodaje pole dodatkowych informacji o koncie
		 * @param f - dodawane pole
		 */
		// XXX: domyslna wartosc parametru!
		void addBuddyExtraInfoField( const TlenField &f);

		/**
		 * dodaje pole informacji publicznych o koncie
		 * @param field - pole
		 */
		void addPubdirAccountField(const TlenField &field);

		/**
		 * dodaje podstawowe pole do wyszukiwania informacji publicznych
		 * @param field - pole
		 */
		void addPubdirBaseSearchField(const TlenField &field);

		/**
		 * dodajze zaawansowane pole do wyszukiwania informacji publicznych.
		 * @param field - pole
		 */
		void addPubdirAdvancedSearchField(const TlenField &field);

		/**
		 * dodaje kolumne wyniku wyszukiwania
		 * @param field - pole opisujace kolumne.
		 */
		void addPubdirResultColumn(const TlenField &field);

		/**
		 * Tworzy i przypisuje do protokolu oraz do danego typu TlenBuddyContact prezencje
		 * @param display - nazwa wyswietlana prezencji (powinna zostac umieszczona w "tlen_tr()" dla tlumaczen)
		 * @param id - identyfikator prezencji (pole do uzytku wewnetrznego protokolu, np przy zmianie prezencji)
		 * @param icon - nazwa pliku z ikona prezencji
		 * @param priority - priorytet prezencji (uzywany przy sortowaniu listy kontaktow)
		 * @param buddytype - typ buddiego
		 */
		void addPresenceType(const QString &display, const QString &id, const QString &icon, unsigned priority);

		/**
		 * Tworzy i przypisuje do protokołu typ prezencji z podaną flagą.
		 * Prezencji zostaje przypisana nazwa wyświetlana, priorytet oraz identyfikator zgodny z flagą. Próba dodania prezencji z flagą TlenPresenceType::NoFlag przerywa program.
		 * Każdy protokól musi dodać po jednym typie prezencji z flagami: TlenPresenceType::Available, TlenPresenceType::Away, TlenPresenceType::Invisible i TlenPresenceType::Unavailable
		 * @param icon - nazwa pliku z ikoną prezencji
		 * @param presflag - flaga prezencji
		 */
		void addPresenceType(const QString &icon, TlenPresence::Flag presflag);

		/**
		 * Tworzy i przypisuje do protokolu typ subskrypcji
		 * @param display - nazwa wyswietlana subskrypcji (powinna zostac umieszczona w "tlen_tr()" dla tlumaczen)
		 * @param id - identyfikator subskrypcji (pole do uzytku wewnetrznego protokolu, np przy zmianie subskrypcji)
		 * @param priority - priorytet subskrypcji (uzywany do grupowania listy kontaktow po subskrypcji)
		 */
		void addSubscriptionType(const QString &display, const QString &id, unsigned priority, const QString &icon = QString());

		/**
		 * Pobiera typ subskrypcji o podanym id
		 * @param id - id subskrypcji ktora chcemy pobrac
		 * @return - subskrypcja
		 * UWAGA: gdy podamy niepoprawny id metoda asertuje. Metoda ta jest tylko do uzytku wewnetrznego, tak wiec programista musi podac zawsze prawidlowy id
		 */
		TlenSubscriptionType getSubscriptionWithId(const QString &id);


		/**
		 * Dodaje resource
		 * @param name - nazwa resource
		 * @param ico - ikona
		 */
		void addResourceType(const QString &name, const QString &ico = QString());
		
		/**
		 * pobiera resource z listy dodanych resource'ow.
		 * @param name - nazwa resource
		 * @return wskaznik na typ resource, albo NULL jesli resource nie istnieje;
		 */
		TlenBuddyResource createResourceWithId(const QString &id, const TlenPresence &) const;

		/**
		 * Sprawdza czy dany resource zostal dodany
		 * @param name - nazwa resource
		 * @return true jesli istnieje, false gdy nie istnieje
		 */
		bool resourceTypeExists(const QString &name) const;

		bool checkPresence(const TlenPresence &) const;
		
		QString getProtocolPresenceIcon(const QString &icon) const;		
		
		/**
		 * Emituje sygnal po wyslaniu xml node
		 * @param acc - konto
		 * @param node - xml node
		 */
		void xmlNodeSent(TlenAccountConnection *acc, const TlenXmlNode &node);
		
		void conferenceStarted(TlenAccountConnection *acc, const QString &id,const QString &chatNick, const QString &chatName, const QString &chatGroup, const QStringList &buddies);
		void conferenceMessageReceived(TlenAccountConnection *acc, const QString &id, const QString &bid, const QString &msg, const QString &timestamp = QString(), const QList<TlenTextFormat>& formats=QList<TlenTextFormat>());
		void conferenceMessageSent(TlenAccountConnection *acc, const QString &confId, const QString &msg);
		void conferenceTopicChanged(TlenAccountConnection *acc, const QString &confId, const QString &topic);
		void conferenceBuddyJoined(TlenAccountConnection *acc, const QString &confId, const QString &buddyId, TlenConferenceUserStatus::Status status=TlenConferenceUserStatus::Anonymous, const QString &uid="");
		void conferenceBuddyLeft(TlenAccountConnection *acc, const QString &confId, const QString &buddyId, const QString &uid="");
		void conferenceBuddyChanged(TlenAccountConnection *acc, const QString &confId, const QString &buddyId, TlenConferenceUserStatus::Status status);
		void conferencePrivilegesChanged(TlenAccountConnection *acc, const QString &confId, int privileges);
		void conferenceReceivedGroups(TlenAccountConnection *acc, const QString &parent, const QList<TlenArg>& groups);
		void conferenceReceivedRooms(TlenAccountConnection *acc, const QString &parent, const QList<TlenArg>& rooms);
		void conferenceReceivedMyRooms(TlenAccountConnection *acc, const QList<TlenArg>& rooms);
		void conferenceReceivedMyNicks(TlenAccountConnection *acc, const QStringList& nicks);
		void conferenceListedUsers(TlenAccountConnection *acc, const QString & confId, TlenConferenceUserStatus::Status status, const QList<TlenArg>& users);
		void conferenceInvited(TlenAccountConnection *acc, const QString &confId);
		
	private:		
	
		friend class TlenAccountConnection;
		friend class TlenAccountConnectionPrivate;
		friend class TlenXmlProtocol;
		friend class TlenRoster;
		friend class TlenRosterPrivate;
		friend class TlenAutoBlockerPlugin;
		friend class TlenEditAccountDialog;
		friend class TlenSettingsManagerPrivate;

		TlenProtocolPrivate *d;
};

/**
 * Sygnaly dotyczace wiadomosci i notyfikacji
 */
#define MESSAGE_RECEIVED "message_received"
#define MESSAGE_SENT "message_sent"
#define TYPING_NOTIFY "typing_notify"
#define ALERT_RECEIVED "alert_received"

/**
 * Sygnaly dotyczace konferencji
 */
#define CONF_STARTED "conference_started"
#define CONF_MESSAGE_RECEIVED "conference_message_received"
#define CONF_MESSAGE_SENT "conference_message_sent"
#define CONF_TOPIC_CHANGED "conference_topic_changed"
#define CONF_BUDDY_JOINED "conference_buddy_joined"
#define CONF_BUDDY_LEFT "conference_buddy_left"
#define CONF_BUDDY_CHANGED "conference_buddy_changed"
#define CONF_PRIVILEGES_CHANGED "conference_privileges_changed"
#define CONF_RECEIVED_ROOMS "conference_received_rooms"
#define CONF_RECEIVED_GROUPS "conference_received_groups"
#define CONF_RECEIVED_MY_ROOMS "conference_received_my_rooms"
#define CONF_RECEIVED_NICKS "conference_received_my_nicks"
#define CONF_RECEIVED_USER_LIST "conference_received_user_list"
#define CONF_INVITED "conference_invited"

/**
 * Sygnaly dotyczace zmian stanu konta
 */
#define ACC_LOGGED_IN "account_logged_in"
#define ACC_LOGGED_OUT "account_logged_out"
#define ACC_RESOURCE_CHANGED "account_resource_changed"
#define ACC_AUTHORIZATION_ERROR "account_authorization_error"
#define ACC_PRESENCE_CHANGED "account_presence_changed"
#define ACC_AVATAR_SET "account_avatar_set"
#define ACC_AVATAR_RECEIVED "account_avatar_received"
#define ACC_AVATAR_SET_ERROR "account_avatar_set_error"
#define ACC_AVATAR_REMOVED "account_avatar_removed"

/**
 * Sygnaly dotyczace operacji na katalogu publicznym
 */
#define PUBDIR_ACC_DATA_RECEIVED "pubdir_account_data_received"
#define PUBDIR_ACC_DATA_REMOVED "pubdir_account_data_removed"
#define PUBDIR_ACC_DATA_EDITED "pubdir_account_data_edited"
#define PUBDIR_SEARCH_RESULT_RECEIVED "pubdir_search_result_received"

/**
 * Tylko dla protokołu xml
 */


#define XML_PROTOCOL_ON_NODE "xml_protocol_on_node"
#define XML_PROTOCOL_NODE_SENT "xml_protocol_node_sent"

/**
 * Inne
 */


#define USER_VERSION_CHECKED "user_version_checked"
#define NEW_MAIL "new_mail_sig"
#define OPEN_MAIL "open_mail_sig"
#define P2P_REQUEST_ADDRESS "p2p_request_address"
#define LAST_ACTIVITY_RECEIVED "last_activity_received"

#endif

