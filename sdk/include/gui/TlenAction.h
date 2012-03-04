#ifndef __TLEN_ACTION_H__
#define __TLEN_ACTION_H__

#include <QList>
#include <QString>

#include <core/export.h>
#include <data/TlenArg.h>
#include <data/TlenPluginAction.h>
#include <plugin/TlenPluginTypes.h>

/**
 * Akcja dodawana do menu kontekstowego
 */
class __tlen_gui_context_menu__ TlenAction
{
	public:
		TlenAction(){}
		TlenAction(const QString &caption, const QString &iconpath, const TlenPluginAction &action, const QList<TlenArg> &actdata = QList<TlenArg>());
		virtual ~TlenAction();
	
		bool isEnabled() const;
		bool isMenu() const;
		bool isSeparator() const;
		
		void setLabel(const QString &label);
		void setIcon(const QString &icon);
		void setEnabled(bool enabled);
		void setChecked(bool checked);
		void setShortcut(const QString &shortCut);

		const QString getLabel() const;
		const QString getIcon() const;
		QList<TlenArg> getActionData() const;
		TlenPluginAction getPluginAction() const;
		QString getShortcut() const;
		bool isChecked() const;
		bool operator==(const TlenAction &other) const;
		
	protected:
		bool menu;
		bool separator;
		// jesli actiondata zawiera jakies dane, wtedy one sa przekazywane, zamiast danych z menu
		QList<TlenArg> actiondata;

	private:
		bool enabled;
		bool checked;
		QString caption;
		QString iconpath;
		QString shortCut;
		TlenPluginAction action;
};

class __tlen_gui_context_menu__ TlenActionSeparator: public TlenAction
{
	public:
		TlenActionSeparator();
};


#endif

