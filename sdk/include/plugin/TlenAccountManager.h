#ifndef __TLEN_ACCOUNT_MANAGER_H__
#define __TLEN_ACCOUNT_MANAGER_H__

#include <QString>
#include <data/TlenField.h>
#include <core/export.h>

class TlenProtocol;
class TlenAccountConnection;
class TlenAccountManagerPrivate;
class TlenApplication;
class TlenAccountManager;

/**
 * Informacje o koncie
 */
class __tlen_plugin__ TlenAccountInfo
{
	public:
	
		/**
		 * zwraca id konta
		 * @return id konta
		 */
		QString getId() const;
		/**
		 * zwraca nazwe wyświetlaną konta
		 * @return nazwa wyświetlana konta
		 */
		QString getAlias() const;
		/**
		 * Zwraca protokół konta
		 * @return protokół
		 */
		TlenProtocol *getProtocol() const;
		/**
		 * Zwraca czy konto jest włączone
		 * @return stan konta
		 */
		bool isEnabled() const;

	private:
		TlenAccountInfo(const QString &accid, const QString &accalias, TlenProtocol *protocol);
		TlenAccountInfo();
		void operator=(const TlenAccountInfo &);

		QString accid;
		QString accalias;
		TlenProtocol *protocol;
		friend class TlenAccountManagerPrivate;
		friend class TlenAccountManager;
};


/**
 * Zarządza kontami. Umożliwia odczytywanie, włączanie, wyłaczanie kont.
 */
class __tlen_plugin__ TlenAccountManager
{
	public:		
		static TlenAccountManager *getInstance();
				
		/**
		 * Tworzy konto o podanych parametrach
		 * @param display nazwa wyświetlana
		 * @param uid id
		 * @param pass hasło
		 * @param rememberPass czy hasło ma być zapamiętane
		 * @param protocol protokół
		 * @param defaultPresence domyślna prezencja
		 * @param accSettings ustawienia konta
		 * @return utworzone konto
		 */
		TlenAccountConnection *createAccount(const QString &display, const QString &uid, const QString &pass, bool rememberPass, TlenProtocol *protocol, const TlenPresence &defaultPresence, const QList<TlenField> &accSettings = QList<TlenField>());
		/**
		 * Ładuje konto
		 * @param uid id
		 * @param protoid id protokołu
		 * @return załadowane konto
		 */
		TlenAccountConnection *loadAccount(const QString &uid, const QString &protoid);
		/**
		 * Zwraca konto
		 * @param uid id
		 * @param protoid id protokołu
		 * @return konto
		 */
		TlenAccountConnection *getAccount(const QString &uid, const QString &protoid);
		/**
		 * Włącza konto
		 * @param uid id
		 * @param protoid id protokołu
		 */
		void enableAccount(const QString &uid, const QString &protoid);
		/**
		 * Wyłącza konto
		 * @param uid id
		 * @param protoid id protokołu
		 */
		void disableAccount(const QString &uid, const QString &protoid);
		/**
		 * Usuwa konto
		 * @param uid id
		 * @param protoid id protokołu
		 */
		void removeAccount(const QString &uid, const QString &protoid);
		
		/**
		 * Zwraca informacje o kontach
		 * @param protoid id protokołu, jeśli puste zwraca wszystkie konta
		 * @return informacje o kontach
		 */
		QList<TlenAccountInfo *> getAccountsInfo(const QString &protoid = QString()) const;
		/**
		 * Zwraca informacje o wyłączonych kontach
		 * @return informacje o kontach
		 */
		QList<TlenAccountInfo *> getDisabledAccountsInfo() const;
		/**
		 * Zwraca konta
		 * @return konta
		 */
		QList<TlenAccountConnection *> getAccounts() const;
		/**
		 * Zwraca zalogowane konta
		 * @return zalogowane konta
		 */
		QList<TlenAccountConnection *> getLoggedInAccounts() const;
		/**
		 * Zwraca konta dla danego protokołu
		 * @param  id protokołu
		 * @return konta
		 */
		QList<TlenAccountConnection *> getAccountsForProtocol(const QString &) const;
		/**
		 * Zwraca zalogowane konta dla danego protokołu
		 * @param  id protokołu
		 * @return konta
		 */
		QList<TlenAccountConnection *> getLoggedInAccountsForProtocol(const QString &) const;
		/**
		 * Zwraca czy konto jest włączone
		 * @param uid id
		 * @param protocol id protokołu
		 * @return stan konta
		 */
		bool accountEnabled(const QString &uid, const QString &protocol) const;
		
		/**
		 * @return Zwraca konto główne
		 */
		TlenAccountConnection* getMainAccount() const;
	
	private:
		~TlenAccountManager();
		TlenAccountManager();
		TlenAccountManager(const TlenAccountManager &);
		void operator=(const TlenAccountManager &);
		TlenAccountManagerPrivate *d;
		friend class TlenApplication;
};



#endif

