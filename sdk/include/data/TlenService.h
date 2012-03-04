#ifndef __TLEN_SERVICE_H__
#define __TLEN_SERVICE_H__

#include <QString>

#include <core/export.h>
#include <data/TlenPluginAction.h>


/**
 * Klasa opisująca usługę jaką realizuje plugin
 */
class __tlen_data__ TlenService
{
public:
	TlenService();
	TlenService(const QString &_service, const QString & _display, const QString &icon = QString(),  const QString &_protocol = QString(), const TlenPluginAction &_action = TlenPluginAction());

	bool isValid() const;
	bool operator==(const TlenService &serv) const;

	QString getService() const
	{
		return service;
	}
	
	QString getIcon() const
	{
		return icon;
	}
	
	QString getDisplay() const
	{
		return display;
	}
	
	QString getProtocol() const
	{
		return protocol;
	}
	
	TlenPluginAction getAction() const
	{
		return action;
	}
private:
	QString service;
	QString icon;
	QString display;
	QString protocol;
	TlenPluginAction action;
	
};

#endif

