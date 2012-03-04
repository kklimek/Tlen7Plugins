#ifndef _TLEN_ACCOUNT_CONNECTION_H_
#define _TLEN_ACCOUNT_CONNECTION_H_

#include <QTime>
#include <QString>

#include <data/TlenField.h>
#include <data/TlenPresence.h>
#include <data/TlenTextFormat.h>
#include <network/TlenSocket.h>

class TlenAccountConnectionPrivate;
class TlenBuddyContact;
class TlenProtocol;

/**
 * \brief Przechowuje wszelkie informacje o koncie i jednocześnie jest jego połączeniem
 *
 * Za pomoca tej klasy możemy zmienić niemal wszystkie ustawienia konta.
 */
class __tlen_plugin__ TlenAccountConnection: public TlenSocket
{
	public:

		/**
		 * @return nazwa wtyczki protokołu
		 */
		QString getProtocolName() const;

		/**
		 * @return wskaznik na protokół konta
		 */
		TlenProtocol *getProtocol() const;

		/**
		 * @return wektor ustawień konta, specyficznych dla protokołu konta
		 */
		QList<TlenField> getAccountSettings() const;
		/**
		 * @return wektor ustawień konta, specyficznych dla protokołu konta w kolejności ich definiowania
		 */
		QList<TlenField> getAccountSettingsInOrder() const;
		
		/**
		 * Zwraca ustawienie konta o podanym id
		 * @param id id
		 * @return wartość ustawienia
		 */
		TlenField getAccountSetting(const QString &id) const;	

		/**
		 * Ustawia opcje konta
		 */
		void setAccountSettings(const QList<TlenField> &fields);
		
		/**
		 * Ustawia opcje konta
		 * @param id  id ustawienia
		 * @param f wartość ustawienia
		 */
		void setAccountSetting(const QString &id, const TlenField &f);

		/**
		 * @return alias konta
		 */
		QString getAlias() const;

		/**
		 * Zmienia obecny alias konta `newalias`
		 * @param newalias - nowy alias konta
		 */
		void setAlias(const QString &newalias);

		/**
		 * @return identyfikator konta
		 */
		QString getUid() const;

		/**
		 * @return identyfikator konta wraz z zasobem
		 */
		QString getUidWithResource() const;
	
		/**
		 * @return hasło konta
		 */
		QString getPassword() const;
		
		/**
		 * Ustawia hasło na podane
		 * @param password  hasło
		 */
		void setPassword(const QString &password);

		/**
		 * Wysyła wiadomość za pośrednictwem protokołu
		 * @param buddyid - identyfikator kontaktu, do którego wysyłamy wiadomość
		 * @param msg - treść wiadomości
		 * @param res - zasób do którego wysyłana jest wiadomść
		 */
		void sendMessage(const QString &buddyid, const QString &msg, const QString &resource, const QString & subject = QString());

		/**
		 * Wysyła wiadomość konferencyjną
		 * @param confId id konferencji
		 * @param msg treść wiadomości
		 * @param params formatowanie
		 */
		void sendConferenceMessage(const QString &confId, const QString &msg, const QList<TlenTextFormat>& params);
		
		/**
		 * Wysyła prywatną wiadomość konferencyjną
		 * @param confId id konferencji
		 * @param buddyId id kontaktu
		 * @param msg treść wiadomości
		 * @param params formatowanie
		 */
		void sendPrivateConferenceMessage(const QString &confId,const QString & buddyId, const QString &msg, const QList<TlenTextFormat>& params);
		/**
		 * Wysyła za pośrednictwem protokołu żądanie o pobranie danych publicznych. \n
		 * Pobrane dane publiczne zostaną wyemitowane sygnałem PUBDIR_ACC_DATA_RECEIVED. \n
		 * Jeśli konto nie jest zalogowane ta metoda nic nie robi.
		 */
		void getPubdirInfo();

		/**
		 * Pobiera globalne ustawiena konta czyli
		 *  - TlenField::String alias - nazwa wyświetalna konta
		 *  - TlenField::String password - hasło
		 *  - TlenField::CheckBox pasword/remember - czy zapamiętuje hasło
		 *  - TlenField::CheckBox enabled - czy konto jest właczone
		 *  - TlenField::CheckBox presence/restore - czy przywracać ostatnio uźywana prezencję
		 *  - TlenField::String presence/last/type - typ ostatniej prezencji
		 *  - TlenField::String presence/last/description - stan opisowy ostatniej prezencji
		 *  - TlenField::String presence/default/type - typ domyślnej prezencji
		 *  - TlenField::String presence/default/description - stan opisowy domyślnej prezencji
		 *  @return wektor globalnych ustawien.
		 */
		QList<TlenField> getGlobals() const;

		/**
		 * Zmienia prezencję konta \n
		 * Jeśli konto nie jest zalogowane, to metoda ta najpierw zaloguje konto, a potem zmieni jego prezencję
		 * @param pres - nowa prezencja konta. \n
		 * Jeśli prezencja ma identyfikator nienależący do protokołu, ta metoda nie robi nic.
		 */
		void setPresence(const TlenPresence &pres);
		
		/**
		 * Wylogowuje konto
		 */
		void logoutAccount();

		/**
		 * Zmienia prezencje konta
		 * @param presflag flaga prezencji na jaką zmieniamy
		 * @param descr stan opisowy prezencji
		 */
		void setPresence(TlenPresence::Flag presflag, const QString &descr = QString());
		
		/**
		 * Zmienia prezencje konta
		 * @param id id prezencji na jaką zmieniamy
		 * @param descr stan opisowy prezencji
		 */
		void setPresence(const QString &id, const QString &descr = QString());
		
		/**
		 * @return domyślna prezencja konta
		 */
		TlenPresence getDefaultPresence() const;
		
		/**
		 * @return ostatnia prezencja konta przed wylogowaniem
		 */
		TlenPresence getLastPresence() const;
		
		/**
		 * @return obecna prezencja konta
		 */
		TlenPresence getPresence() const;
		
		/**
		 * @return prezencja jaka jest aktualnie ustawiana
		 */
		TlenPresence getDesiredPresence() const;
		
		/** Zwraca jaka ma być ustawiona prezencja konta po jego zalogowaniu.
		 * W zależności od ustawień zwraca domyślną prezencję lub ostatnią
		 * przed wylogowaniem.
		 * @return prezencja
		 */
		TlenPresence getNeededPresence() const;

		/**
		 * Ustala identyfikator sesji konta
		 * @param s - nowy identyfikator sesji
		 */
		void setSID(const QString &s);

		/**
		 * @return identyfikator sesji
		 */
		QString getSID() const;

		/**
		 * Dodaje do konta kontakt
		 * @param contact - dodawany kontakt
		 */
		void addContact(const TlenBuddyContact &contact);

		/**
		 * Ustala czy konto jest włączone
		 * @param e - czy konto ma byc włączone
		 */
		void setEnabled(bool e);

		/**
		 * @return czy konto jest włączone
		 */
		bool isEnabled() const;

		/**
		 * Włącza opcje "presence/last/restore", czyli przywracanie prezencji z ostatniej sesji
		 * @param r - czy przywracać prezencję z ostatniej sesji
		 */
		void setRestoreLastPresence(bool r);

		/**
		 * Włącza przywracanie opisu z ostatniej prezencji
		 * @param r czy przywrócić opis
		 */
		void setRestoreLastDescription(bool r);
		/**
		 * 
		 * @return zwraca czy ma być przywracany ostatni opis
		 */
		bool restoreLastDescription() const;
		
		/**
		 * @return czy przywracać prezencję z ostatniej sesji
		 */
		bool restoreLastPresence() const;

		/**
		 * Włącza opcje "password/remember", czyli czy zapamietywać hasło przy wyjściu z programu
		 * @param r - czy zapamiętywać hasło przy wyjściu z programu
		 */
		void setRememberPassword(bool r);

		/**
		 * @return czy zapamiętywać hasło przy wyjściu z programu
		 */
		bool rememberPassword() const;

		/**
		 * Ustala domyślną prezencje. Domyślna prezencja jest ustalana po starcie programu jeśli opcja "presence/last/restore" jest wyłączona
		 * @param pres - nowa domyślna prezencja.
		 */
		void setDefaultPresence(const TlenPresence &pres);

		/**
		 * @return czy konto jest zalogowane
		 */
		bool isLoggedIn() const;

		/**
		 * Zmienia avatar konta
		 * @param avatarpath - scieżka do pliku z avatarem
		 */
		void setAvatar(const QString &avatarpath);

		/**
		 * Usuwa avatar konta
		 */
		void removeAvatar();

		/**
		 * Pobiera avatar za pomocą protokołu
		 */
		void getAvatar();

		/**
		 * @return ścieżka do obecnego avataru
		 */
		QString getCurrentAvatarPath() const;		
		
		/**
		 * @return czas zalogowania
		 */
		QTime getLoginTime();

		
	private:				
		void disconnected();
		void connected();
		void error(TlenSocket::Error);
		void peerVerifyError(const QList<TlenSocket::SslError> &);
		void readyRead();
		void connectionEncrypted();

		void writeData(const QByteArray &data, qint64 size = -1);
		void writeData(const TlenXmlNode &node);

		TlenAccountConnection(const QString &name, const QString &id, const QString &pass, bool rp, TlenProtocol *const ,const TlenPresence &defaultPresence);
		TlenAccountConnection(const QString &uid, TlenProtocol *);
		TlenAccountConnection();
		TlenAccountConnection(const TlenAccountConnection &);
		~TlenAccountConnection();
		void operator=(const TlenAccountConnection &);

		friend class TlenProtocol;
		friend class TlenPluginManager;
		friend class TlenPluginManagerPrivate;
		friend class TlenAccountManager;

		TlenAccountConnectionPrivate *d;
};






#endif

