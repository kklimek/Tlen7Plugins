#ifndef __TLEN_BUDDY_H__
#define __TLEN_BUDDY_H__

#include <QHash>
#include <QString>

#include <core/export.h>
#include <data/TlenPresence.h>
#include <data/TlenBuddyResource.h>

class TlenAccountConnection;
class TlenBuddyGroup;
class TlenBuddyContact;
class TlenBuddyMeta;
class TlenBuddyTemporary;
class TlenBuddyPrivate;
class TlenRosterPrivate;
class TlenArg;
class TlenField;
class TlenSubscriptionType;
class TlenGuiPlugin;


/**
 * Reprezentuje kontakt
 */
class __tlen_data__ TlenBuddy
{
	public:
		enum Type {
			Invalid = 0,
			Group,
			Meta,
			Contact,
			Temporary,
			Custom
		};

		TlenBuddy();

		TlenBuddy(const TlenBuddy &other);

		virtual ~TlenBuddy();

		virtual bool isValid() const;
		int unreadMessages() const;
		void setUnreadMessages(int);
		
		virtual QString getDisplay() const;
		Type getType() const;

		bool operator==(const TlenBuddy &other) const;
		bool operator!=(const TlenBuddy &other) const;
		

		TlenBuddy &operator=(const TlenBuddy &other);

	protected:
		TlenBuddy(const QString &display, Type type);

	private:
		friend class TlenBuddyContact;
		friend class TlenBuddyTemporary;
		friend class TlenBuddyGroup;
		friend class TlenBuddyMeta;
		friend class TlenBuddyCustom;

		friend class TlenRosterPrivate;
		friend class TlenRoster;
		friend class TlenSettingsManagerPrivate;
		friend class TlenArchiveImporter;
	
		friend class TestBuddy;

		friend uint __tlen_data__ qHash(const TlenBuddy &);

		TlenBuddyPrivate *buddyp;
};


__tlen_data__ TlenAccountConnection* buddyAccount(const TlenBuddy &buddy);
__tlen_data__ QString buddyId(const TlenBuddy &buddy);
__tlen_data__ TlenPresence buddyPresence(const TlenBuddy &buddy);
__tlen_data__ QString buddyAvatarPath(const TlenBuddy &buddy);
__tlen_data__ TlenBuddy buddyGroup(const TlenBuddy &buddy);
__tlen_data__ TlenBuddy buddyParent(const TlenBuddy &buddy);
__tlen_data__ uint qHash(const TlenBuddy &);

/**
 * Kontakt specjalnego typu. Dodawany i obsługiwany przez wtyczki samodzielnie, zarządzany przy pomocy TlenPluginRosterHandler
 * @sa TlenPluginRosterHandler
 */
class __tlen_data__ TlenBuddyCustom: public TlenBuddy
{
	public:
		TlenBuddyCustom();
		TlenBuddyCustom(const TlenBuddyCustom &other);
		TlenBuddyCustom(const TlenBuddy &);
		TlenBuddy getParent() const;
		QString getAvatarPath() const;
		QString getPresenceIconPath() const;
		QString getOwnerId() const;
		QString getDescription() const;
		QString getSubType() const;
		QHash< QString, TlenArg > getAttribs() const;
		void setAttribs(const QHash<QString, TlenArg> &attribs);
		
	protected:
		TlenBuddyCustom(const QString &display, const QString &subType, const QString &ownerid, const QHash<QString, TlenArg> &attribs,  const QString &description, const QString &presenceIcon, const QString &avatarIcon);
	
	private:
		friend class TestBuddy;	
		friend class TlenSettingsManagerPrivate;
		friend class TlenRoster;
		friend class TlenRosterPrivate;
		friend class TlenArchiveImporter;
};


/**
 * Kontakt dodany do listy kontaktów
 */

class __tlen_data__ TlenBuddyContact: public TlenBuddy
{
	public:
		TlenBuddyContact();
		TlenBuddyContact(const TlenBuddyContact &);
		TlenBuddyContact(const TlenBuddy &);

		QString getId() const;
		QString getDisplay() const;
		TlenSubscriptionType getSubscription() const;

		QString getAvatarPath() const;
		QString getLocalAvatarPath() const;
		QString getServerAvatarPath() const;
		QStringList getTags() const;

		// moze byc meta, moze byc grupa
		TlenBuddy getParent() const;

		TlenPresence getPresence() const;
		
		QString getPresenceIcon() const;

		QList<TlenField> getExtraInfo() const;
		TlenArg getAttrib(QString name) const;
		QHash< QString, TlenArg > getAttribs() const;
		void setAttribs(const QHash<QString, TlenArg> &attribs);
		
		
		//bool setFieldValue(const QString &field_id, const TlenArg &value);
		void setFieldValues(const QList<TlenField> &fields);

		TlenAccountConnection *getAccount() const;

		TlenBuddyResource getActiveResource() const;
		QList<TlenBuddyResource> getResources() const;

	protected:
		TlenBuddyContact(TlenAccountConnection *acc, const QString &id, const QString &display, const TlenPresence &pres, const TlenSubscriptionType &subscr);

	private:
		friend class TlenRosterPrivate;;
		friend class TlenRoster;	
		friend class TestBuddy;
		friend class TlenArchiveImporter;
};

/**
 * Kontakt tymczasowy
 */

class __tlen_data__ TlenBuddyTemporary: public TlenBuddy
{
	public:
		TlenBuddyTemporary();
		TlenBuddyTemporary(const TlenBuddyTemporary &);
		TlenBuddyTemporary(const TlenBuddy &);

		QString getId() const;
		TlenAccountConnection *getAccount() const;

		TlenPresence getPresence() const;

		TlenBuddyGroup getGroup() const;

		QList<TlenBuddyResource> getResources() const;

	protected:
		TlenBuddyTemporary(TlenAccountConnection *acc, const QString &id, const TlenPresence &presence, const TlenBuddyGroup &group);

	private:
		friend class TlenRoster;
		friend class TlenGuiPlugin;
	
		friend class TestBuddy;
};

/**
 * Grupa do której przypisane są inne kontakty
 */

class __tlen_data__ TlenBuddyGroup: public TlenBuddy
{
	public:
		TlenBuddyGroup();
		TlenBuddyGroup(const TlenBuddyGroup &other);
		TlenBuddyGroup(const TlenBuddy &other);

		int childCount() const;
		int onlineChildCount() const;

		//void sort();

		TlenBuddy buddyAt(int row) const;

		/**
		 * Sprawdza czy kontakt znajduje się w danej grupie.\n
		 * Jeśli w grupie znajduje się jakiś meta, kontakt lub scalony kontakt i zawiera on
		 * szukany TlenBuddyContact metoda zwraca true
		 * @param contact - szukany kontakt
		 */
		bool containsContact(const TlenBuddyContact &contact) const;

		bool containsMeta(const QString &metaname) const;

		/**
		 * Sprawdza czy TlenBuddy znajduje się bezpośrednio w grupie
		 */
		bool containsBuddy(const TlenBuddy &buddy) const;

		bool isExpanded() const;

	protected:
		// wszystkie operacje dodawania i usuwania musza byc wykonywane za posrednictwem TlenRoster
		TlenBuddyMeta addMeta(const QString &meta);
		bool addBuddy(const TlenBuddy &b);
		int removeBuddy(const TlenBuddy &b);
		TlenBuddy removeAt(int row);
		TlenBuddyGroup(const QString &display);

	private:
		friend class TlenBuddyMeta;
		friend class TlenSettingsManagerPrivate;
		friend class TlenRoster;
		friend class TlenRosterPrivate;
		friend class TlenArchiveImporter;
	
		friend class TestBuddy;
};


class __tlen_data__ TlenBuddyMeta: public TlenBuddy
{
	public:
		TlenBuddyMeta();
		TlenBuddyMeta(const TlenBuddyMeta &other);
		TlenBuddyMeta(const TlenBuddy &);

		int childCount() const;
		int onlineChildCount() const;
		
		TlenBuddyGroup getGroup() const;
		bool containsContact(const TlenBuddyContact &) const;

		bool isExpanded() const;

		TlenBuddyMeta &operator=(const TlenBuddyMeta &other);
		QList<TlenBuddy> getBuddies() const;
		TlenBuddy getCurrentBuddy() const;
		

	protected:
		bool addBuddy(const TlenBuddy &b);
		int removeBuddy(const TlenBuddy &b);
		TlenBuddyMeta(const QString &display);

	private:
		friend class TlenBuddyGroup;	
		friend class TlenSettingsManagerPrivate;
		friend class TlenRoster;
		friend class TlenRosterPrivate;
};







#endif

