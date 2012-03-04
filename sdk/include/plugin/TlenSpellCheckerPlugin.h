#ifndef __TLEN_SPELL_CHECKER_PLUGIN_H__
#define __TLEN_SPELL_CHECKER_PLUGIN_H__

#include <QString>
#include <QStringList>

#include <core/export.h>
#include <core/util.h>
#include <plugin/TlenPlugin.h>


/**
 * Klasa bazowa dla pluginów realizujących usługę słownika
 */
class __tlen_plugin__ TlenSpellCheckerPlugin :  public TlenPlugin
{
	public:
	virtual bool highlightWord(const QString &word)=0;
	virtual QStringList suggestions(const QString &word)
	{
		return QStringList();
	}
	virtual QList<TlenService> getProvidedServices() const 
	{
		return QList<TlenService>() << TlenService("spell", tlen_tr("spell", "service name"));
	}	
};



#endif
