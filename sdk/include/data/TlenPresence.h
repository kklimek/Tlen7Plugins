#ifndef _TLEN_PRESENCE_H_
#define _TLEN_PRESENCE_H_

#include <QString>

#include <core/export.h>

class TlenPresenceType;

/**
 * \brief Opisuje prezencję
 *
 * Prezencja składa sie z typu prezencji i stanu opisowego.
 */
class __tlen_data__ TlenPresence
{
	friend class TlenProtocol;

	public:
		/**
		 * \brief opisuje flagę typu prezencji.
		 *
		 * Jeśli protokół nie dostarcza po jednej prezencji z każdą z tych flag, wtedy nie może on zostać poprawnie załadowany.
		 * Tych flag używa menu szybkiego przełączania stanu
		 */
		enum Flag {
			Invalid = 0,		/**< Flaga niezaincjalizowanej prezencji (bez typu) */
			NoFlag,			/**< Domyślna flaga pozostałych prezencji */
			Available,		/**< Stan "dostępny". Nazwa wyświetlana "Available", identyfikator "available", priorytet 10 */
			Away,			/**< Stan "zaraz wracam". Nazwa wyświetlana "Away", identyfikator "away", priorytet 5 */
			Invisible,		/**< Stan "ukryty". Nazwa wyświetlana "Invisible", identyfikator "invisible", priorytet 0 */
			Unavailable		/**< Stan "niedostępny". Nazwa wyświetlana "Unavailable", identyfikator "unavailable", priorytet 0 */
		};

		/**
		 * Domyślny konstruktor. Tworzy prezencję bez typu i bez stanu opisowego
		 */
		TlenPresence();
		TlenPresence(const TlenPresence &);
	
		TlenPresence & operator=(const TlenPresence &other);
	

		bool isValid() const;

		/**
		 * @return stan opisowy prezencji
		 */
		QString getDescription() const;
	
		bool operator==(const TlenPresence &) const;
		bool operator!=(const TlenPresence &) const;
		bool operator<(const TlenPresence &) const;

		unsigned getPriority() const;
		QString getDisplay() const;
		QString getId() const;
		QString getIcon() const;
		Flag getFlag() const;

	private:
		/**
		 * Tworzy prezencję o typie `t` i stanie opisowym `desc`
		 */
		TlenPresence(TlenPresenceType *t, const QString &desc = QString());
		TlenPresenceType *type;
		QString description;
		bool unreadMessage;
};







#endif
