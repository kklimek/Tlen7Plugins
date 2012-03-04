#ifndef __TLEN_ROSTER_H__
#define __TLEN_ROSTER_H__

#include <QHash>
#include <QString>

#include <core/export.h>
#include <data/TlenArg.h>
#include <data/TlenBuddy.h>
#include <data/TlenBuddyResource.h>
#include <data/TlenPresence.h>
#include <data/TlenSubscription.h>
#include <plugin/TlenPlugin.h>

class TlenRosterPrivate;
class TlenApplication;

/**
 * Obsługa listy kontaktów
 */
class __tlen_roster__ TlenRoster: public TlenPlugin
{
	public:
		static TlenRoster *getInstance();

		/**
		 * Dodaje kontakt
		 * @param acc konto
		 * @param id id
		 * @param display nazwa wyświetlana
		 * @param btype typ
		 * @param pres prezencja
		 * @param group grupa
		 * @param meta meta
		 * @param subscr subskrypcja
		 * @return dodany kontakt
		 */
		TlenBuddyContact addContact(TlenAccountConnection *acc, const QString &id, const QString &display, const TlenPresence &pres, const QString &group, const QString &meta = QString(), const TlenSubscriptionType &subscr = TlenSubscriptionType());
		/**
		 * Dpodaje kontakt tymczasowy
		 * @param acc konto
		 * @param id id
		 * @param pres prezencja
		 * @return dodany kontakt
		 */
		TlenBuddyTemporary addTemporaryContact(TlenAccountConnection *acc, const QString &id, const TlenPresence &pres);
		/**
		 * Dodaje grupę
		 * @param name nazwa
		 * @return dodana grupa
		 */
		TlenBuddyGroup addGroup(const QString &name);
		/**
		 * Dodaje kontakt specjalny
		 * @param name nazwa
		 * @param group grupa
		 * @param subType podtyp
		 * @param ownerid id wlaściciela (nazwa pluginu)
		 * @param attribs atrybuty
		 * @param description opis
		 * @param presenceIcon ikona prezencji
		 * @param avatarIcon avatar
		 * @return dodany kontakt
		 */
		TlenBuddyCustom addCustom(const QString &name, const QString &group, const QString &subType, const QString &ownerid,const QHash<QString, TlenArg> &attribs, const QString &description="", const QString &presenceIcon="", const QString &avatarIcon="");
		TlenBuddyMeta addMeta(const QString &name, const QString &group);		

		/**
		 * Zwraca kontakt o podanym ID
		 * @param id id
		 * @param acc konto
		 * @return kontakt
		 */
		TlenBuddy getContactById(const QString &id, TlenAccountConnection *acc) const;
		/**
		 * Zwraca wszystkie kontakty dla danego konta
		 * @param acc konto
		 * @return lista kontaktów
		 */
		QList<TlenBuddy> getBuddiesForAccount(TlenAccountConnection *acc) const;
		/**
		 * Zwraca wsztkie kontakty dla danego konta o podanej nazwie wyświetlanej
		 * @param display nazwa wyświetlana
		 * @param acc Konto, jeśli NULL zwraca dla wszystkich kont
		 * @return lista kont
		 */
		QList<TlenBuddy> getBuddiesWithDisplayName(const QString &display, TlenAccountConnection *acc) const;
			
		/**
		 * Zwraca wszytkie metakontakty
		 * @return lista metakontaktow
		 */
		QList<TlenBuddyMeta> getMetas();
		/**
		 * Zapisuje roster na dysku
		 * @param acc konto
		 */
		void saveRoster(TlenAccountConnection *acc);
		/**
		 * Aktualizuje atrybut dla kontaktu
		 * @param  kontakt
		 * @param name nazwa atrybutu
		 * @param attrib wartośc atrybutu
		 */
		void updateContactAttrib(const TlenBuddyContact &, const QString &name, const TlenArg &attrib);
		/**
		 * Aktualizuje awatar dla kontaktu
		 * @param  kontakt
		 * @param avatarpath ścieżka do awatara
		 */
		void updateContactAvatar(const TlenBuddyContact &, const QString &avatarpath);
		/**
		 * Aktualizuje awatar lokalny do kontaktu
		 * @param  kontakt
		 * @param avatarpath ścieżka do awatara
		 */
		void updateContactLocalAvatar(const TlenBuddyContact &, const QString &avatarpath);
		/**
		 * Usuwa awatar kontaktu
		 * @param  kontakt
		 */
		void removeContactAvatar(const TlenBuddyContact &);
		/**
		 * Aktualizuje prezencję kontaktu
		 * @param  kontakt
		 * @param presence prezencja 
		 * @param resource zasób
		 */
		void updateContactPresence(const TlenBuddyContact &, const TlenPresence &presence, const TlenBuddyResource &resource = TlenBuddyResource());
		/**
		 * Aktualizuje sybskrypcję kontaktu
		 * @param  kontakt
		 * @param  subskrypcja
		 */
		void updateContactSubscription(const TlenBuddyContact &, const TlenSubscriptionType &);
		/**
		 * Czyści zasoby kontaktu
		 * @param  kontakt
		 */
		void clearContactResources(const TlenBuddyContact &);
		/**
		 * Aktualizuj kontakt
		 * @param  kontakt
		 * @param alias nazwa wyświetlana
		 * @param group grupa
		 * @param meta meta
		 * @param extrainfo dodatkowe informacje kontaktu 
		 * @param tags tagi
		 */
		void updateContact(const TlenBuddyContact &, const QString &alias, const QString &group, const QString &meta, const QList<TlenField> &extrainfo, const QStringList &tags = QStringList());
		/**
		 * Usuwa kontakt tymczasowy
		 * @param  kontakt tymczasowy
		 */
		void removeTemporary(const TlenBuddyTemporary &);
		/**
		 * Usuwa kontakt
		 * @param  kontakt
		 */
		void removeContact(const TlenBuddyContact &);
		/**
		 * Usuwa kontakt z rodzica
		 * @param contact kontakt
		 * @param parent rodzic
		 */
		void removeContact(const TlenBuddyContact &contact, const TlenBuddy &parent);
		/**
		 * Usuwa kontakt specjalny
		 * @param  kontakt
		 */
		void removeCustom(const TlenBuddyCustom &);
		
		void updateCustom(const TlenBuddyCustom &);
		
		/**
		 * Zwraca czy roster jest pusty
		 * @return czy pusty
		 */
		bool isEmpty();
		/**
		 * Sprawdza czy kontakt o danym id dla danego konta istnieje
		 * @param id id kontaktu
		 * @param acc konto
		 * @return czy istnieje
		 */
		bool contactExists(const QString &id, TlenAccountConnection *acc) const;		
		/**
		 * Zmienia nazwę kontaktu
		 * @param b kontakt
		 * @param display nazwa wyświetlana
		 * @return czy się udało
		 */
		bool renameBuddy(const TlenBuddy &b, const QString &display);		
		/**
		 * Zwraca listę grup
		 * @return lista grup
		 */
		QStringList getGroupsNames() const;
		/**
		 * Zmienia grupę dla kontaktu
		 * @param buddy kontakt
		 * @param group nowa grupa
		 */
		void changeGroup(const TlenBuddy& buddy, const QString &group);
		/**
		 * Przesuwa grupę wyżej
		 * @param group grupa
		 */
		void upGroup(const TlenBuddyGroup &group);
		/**
		 * Przesuwa grupę niżej
		 * @param group grupa
		 */
		void downGroup(const TlenBuddyGroup &group);
		
	private:
		TlenRoster();
		~TlenRoster();
				
		///////////////////////////////////////////////////////////////////////////
		// plugin specific
		///////////////////////////////////////////////////////////////////////////
		bool load();
		void unload();
		QString name() const;
		QString icon(int size=0) const;
		QString author() const;
		QString description() const;
		int version() const;
		QString web() const;
		QString email() const;
		///////////////////////////////////////////////////////////////////////////		
				
		TLEN_DECLARE_SLOT(accountEnabled);
		TLEN_DECLARE_SLOT(accountDisabled);
		TLEN_DECLARE_SLOT(pluginLoaded);
		TLEN_DECLARE_SLOT(pluginUnloaded);
		
		friend class TlenProtocol;
		friend class TlenPlugin;
		friend class TlenSettingsManager;
		friend class TlenApplication;
		friend class TlenRosterPrivate;
				
		static TlenRoster *instance;		
		TlenRosterPrivate *d;
};

/**
 * Sygnały
 */

////////////
// Kontakty
////////////
#define CONTACT_ADDED			"contact_added"
#define CONTACT_CHANGED			"contact_changed"
#define CONTACT_REMOVED			"contact_removed"
#define CONTACT_REMOVED_FROM_PARENT	"contact_removed_from_parent"
#define CONTACT_PRESENCE_CHANGED	"contact_presence_changed"
#define CONTACT_SUBSCRIPTION_CHANGED	"contact_sunscription_changed"
#define CONTACT_AVATAR_CHANGED		"contact_avatar_changed"
#define CONTACT_RENAMED			"contact_renamed"
#define CONTACT_ATTRIB_CHANGED		"contact_attrib_changed"

////////////
// Temporary
////////////
#define TEMPORARY_ADDED			"temporary_added"
#define TEMPORARY_REMOVED		"temporary_removed"
#define TEMPORARY_PRESENCE_CHANGED	"temporary_presence_changed"
#define TEMPORARY_CONVERTED_TO_CONTACT	"temporary_converted_to_contact"

////////////
// Grupy
////////////
#define GROUP_ADDED			"group_added"
#define GROUP_REMOVED			"group_removed"
#define GROUP_CHILD_REMOVED		"group_child_removed"
#define GROUP_CHILD_ADDED		"group_child_added"
#define GROUP_COLLAPSED			"group_collapsed"
#define GROUP_RENAMED			"group_renamed"

////////////
// Meta
////////////
#define META_ADDED			"meta_added"
#define META_CHANGED			"meta_changed"
#define META_REMOVED			"meta_removed"
#define META_CHILD_REMOVED		"meta_child_removed"
#define META_CHILD_ADDED		"meta_child_added"
#define META_EXPANDED			"meta_expanded"
#define META_COLLAPSED			"meta_collapsed"
#define META_RENAMED			"meta_renamed"

////////////
// Custom
////////////




#define CUSTOM_CHANGED			"custom_changed"
#define CUSTOM_ADDED			"custom_added"
#define CUSTOM_REMOVED			"custom_removed"
#endif
