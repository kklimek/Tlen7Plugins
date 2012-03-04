#ifndef __TLEN_PLUGIN_ROSTER_HANDLER_H__
#define __TLEN_PLUGIN_ROSTER_HANDLER_H__

#include <data/TlenPluginAction.h>
#include <data/TlenBuddy.h>

/**
 * Realizuje obsługę specjalnych kontaktów TlenBuddyCustom zarządanych przez plugin
 * @sa TlenBuddyCustom
 */
class TlenPluginRosterHandler
{
public:

	TlenPluginRosterHandler():
	owner(NULL)
	{
		
	}
	
	TlenPluginRosterHandler(TlenPlugin * _owner):
	owner(_owner)
	{
		
	}
	
	virtual ~TlenPluginRosterHandler()
	{
		
	}
	
	virtual TlenPluginAction customBuddyRead() const
	{
		return TlenPluginAction();
	}
	
	virtual TlenPluginAction customBuddyActivated() const
	{
		return TlenPluginAction();
	}
	
	virtual TlenPluginAction customBuddyRemove() const
	{
		return TlenPluginAction();
	}
	
	virtual TlenPluginAction customBuddyRename() const
	{
		return TlenPluginAction();
	}
	
	virtual TlenPluginAction contactActivated() const
	{
		return TlenPluginAction();
	}
	
	virtual TlenPluginAction contactRemove() const
	{
		return TlenPluginAction();
	}
	
	bool isValid() const
	{
		return owner != NULL;
	}

private:
	TlenPlugin * owner;
};

#endif
