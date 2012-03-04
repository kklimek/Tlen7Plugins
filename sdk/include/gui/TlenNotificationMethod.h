#ifndef __TLEN_NOTIFICATION_METHOD_H__
#define __TLEN_NOTIFICATION_METHOD_H__

#include <QList>
#include <QHash>

#include <core/export.h>
#include <data/TlenArg.h>
#include <data/TlenField.h>
#include <plugin/TlenPlugin.h>

class TlenNotification;
class TlenPluginAction;


/**
 * Klasa bazowa do obsługi różnych typów powiadomień
 */
class __tlen_gui_notify__ TlenNotificationMethod
{
	public:
		TlenNotificationMethod();
		virtual ~TlenNotificationMethod();	
		virtual void postNotification(unsigned nid, TlenNotification *, const QString &title, const QString &text, const QString &icon, const QString &groupicon, const QList<TlenField> &config, const TlenPluginAction &action, const QList<TlenArg> &args=QList<TlenArg>())=0;

		virtual QString getId() const = 0;
		virtual QString getActionName() const = 0;
		virtual QString getActionIcon() const = 0;

		QList<TlenField> getNotificationsConfigFields() const { return notificationConfigFields; }
		QList<TlenField> getDefaultNotificationConfig(const QString &notification) const { if(defConfigs.contains(notification)) { return defConfigs[notification]; } return QList<TlenField>() << TlenField(); }

	protected:
		void addNotificationConfigField(const TlenField &f) { notificationConfigFields << f; }
		// jesli modul wymaga jakiegos wlasnego sposobu na rejestrowanie notyfikacji, tak jak np. Growl
		virtual void registerNotification(TlenNotification *) { }
		virtual void registerNotifications(const QList<TlenNotification *> &) { }

		void setDefaultNotificationConfig(const QString &notid, const QList<TlenField> &config);

	private:
		QList<TlenField> notificationConfigFields;
		QHash<QString, QList<TlenField> > defConfigs;
		friend class TlenNotificationModule;
};

#endif

