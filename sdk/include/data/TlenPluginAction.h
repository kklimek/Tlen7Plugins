#ifndef __TLEN_NOTIFICATION_ACTION_H__
#define __TLEN_NOTIFICATION_ACTION_H__

#include <core/export.h>
#include <data/TlenArg.h>
#include <plugin/TlenPluginTypes.h>

/**
 * Reprezentuje akcję w pluginie. Jest to obiekt funkcyjny, który może być wywołany
 * np. po odpaleniu odpowiednij pozycji w menu kontektsowym.
 */
class __tlen_data__ TlenPluginAction
{
	friend class TlenPlugin;

	public:
		TlenPluginAction();
		TlenPluginAction(const TlenPlugin *r, TlenPluginActionCallback cb, const QList<TlenArg> &actdata = QList<TlenArg>());
		TlenPluginAction(TlenPlugin *r, TlenPluginActionCallback cb, const QList<TlenArg> &actdata = QList<TlenArg>());
		bool operator==(const TlenPluginAction &other) const;
		void operator()();
		void operator()(QList<TlenArg> &);
		QList<TlenArg> getActionData() const;
		bool isValid() const;

	private:
		TlenPlugin *receiver;
		TlenPluginActionCallback notificationAction;
		QList<TlenArg> actionData;
};

#endif

