#ifndef _TLEN_SUBSCRIPTION_H_
#define _TLEN_SUBSCRIPTION_H_

#include <QString>
#include <core/export.h>

/**
 * \brief Opisuje typ subksrypcji specyficzny dla danego protokołu
 *
 * Typ subskrypcji przechowuje jego nazwę wyświetlaną, identyfikator oraz priorytet wg którego kontakty będą sortowane na liście kontaktów.
 */
class __tlen_data__ TlenSubscriptionType
{
	public:
		/**
		 * Tworzy typ subskrypcji o nazwie wyświetlanej `disp`, identyfikatorze `id` i priorytecie `prior`
		 * @param disp - nazwa wyświetlana
		 * @param id - identyfikator
		 * @param prior - priorytet subskrypcji
		 */
		TlenSubscriptionType(const QString &disp = QString(), const QString &id = QString(), unsigned prior = 0, const QString &icon = QString());

		/**
		 * @return identyfikator subskrypcji
		 */
		QString getId() const;

		/**
		 * @return nazwa wyświetlana subskrypcji
		 */
		QString getDisplay() const;

		/**
		 * @return priorytet subskrypcji
		 */
		unsigned getPriority() const;

		/**
		 * Sprawdza czy typ subskrypcji jest nieprawidłowy. Nieprawidłowy typ subskrypcji ma pustą nazwę wyświetlaną lub identyfikator.
		 * @return true jeśli typ subskrypcji jest nieprawidłowy.
		 */
		bool isValid() const;
		
		QString getIcon() const;
		
		bool operator==(const TlenSubscriptionType &type) const;
		bool operator!=(const TlenSubscriptionType &type) const;

	private:
		QString display;
		QString id;
		unsigned priority;
		QString icon;
};



#endif
