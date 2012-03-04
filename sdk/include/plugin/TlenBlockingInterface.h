#ifndef __TLEN_BLOCKING_INTERFACE_H__
#define __TLEN_BLOCKING_INTERFACE_H__

#include <QString>

#include <plugin/TlenAccountConnection.h>
#include <core/export.h>

/**
 * Pluginy realizujące usługę blokowania powinny implementować ten interfejs.
 */
class __tlen_plugin__ TlenBlockingInterface
{
	public:
	virtual ~TlenBlockingInterface(){}
	
	/**
	 * Sprawdza czy dany kontakt jest zablokowany
	 * @param acc konto
	 * @param bid id kontaktu
	 * @return czy kontakt jest zablokowny
	 */
	virtual bool isUserBlocked(TlenAccountConnection *acc, const QString &bid) const = 0;
};


#endif
