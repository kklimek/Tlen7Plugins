#ifndef __TLEN_MAIN_WINDOW_H__
#define __TLEN_MAIN_WINDOW_H__

#include <QString>

#include <core/export.h>
#include <gui/TlenAction.h>

class TlenMainWindowPrivate;
class TlenMainWindow;

/**
 * Dodawanie akcji do okna glownego
 */
class __tlen_gui_main_window__ TlenMainWindow
{
	public:
	static TlenMainWindow *getInstance();
	/**
	* Dodaje akcje do menu o okreslonej nazwie. Nazwy dostepnych menu sa nazwami
	* zdefiniowanymi w pliku MainWindow.ui
	* @param action dodawana akcja
	* @param action nazwa menu
	*/
	void addMenuAction(const TlenAction &action, const QString &menuId);
	/**
	* Usuwa akcje z menu
	* @param action usuwana akcja
	& @param menuId nazwa menu
	*/
	void removeMenuAction(const TlenAction &action);
	/**
	* Dodaje akcje do toolbaru okna glownego
	* @param action dodawana akcja
	*/
	void addAction(const TlenAction& action);
	/**
	* Usuwa akcje z toolbara glownego
	* @param action usuwana akcja 
	*/
	void removeAction(const TlenAction& action);
	
	private:
	TlenMainWindow();
	static TlenMainWindow *instance;
	TlenMainWindowPrivate *d;
	friend class TlenMainWindowPrivate;
};


#endif
