#ifndef __TLEN_UI_LOADER_H__
#define __TLEN_UI_LOADER_H__

#include <core/export.h>

class QWidget;
class QMainWindow;
class TlenApplication;
class TlenUILoaderPrivate;

/**
 * Ladowanie gui z plikow UI, zapamietuje pozycje okien
 */
class __tlen_ui_generator__ TlenUILoader
{
	
	public:
	
	static TlenUILoader *getInstance();
	/**
	* Laduje plik UI
	* @param name nazwa pliku bez rozszerzenia
	* @param path sciezka ktora zostanie przeszukana. Domyslnie jest to aktualny skorka
	* @return utworzona kontrolka
	*/
	QWidget* loadUI(const QString &name, const QString &path = QString());
	/**
	* Laduje plik UI
	* @param name nazwa pliku bez rozszerzenia
	* @param widget kontrolka, ktora bedzie rodzicem dla ladowanej kontrolki
	* @param path sciezka ktora zostanie przeszukana. Domyslnie jest to aktualny skorka
	* @return utworzona kontrolka
	*/
	QWidget *loadUI(const QString &name, QWidget *widget, const QString& path = QString());
	/**
	* Laduje plik UI
	* @param name nazwa pliku bez rozszerzenia
	* @param widget okno glowne, ktore bedzie rodzicem dla ladowanej kontrolki
	* @return utworzona kontrolka
	*/
	QWidget *loadUI(const QString &name,  QMainWindow *widget);
	/**
	* Wstawia jedna kontrolke wewnatrz innej
	* @param parentWidget kontrolka nadrzedna
	* @param childWidget kontrolka podrzedna
	*/
	static void insertWidget(QWidget *parentWidget,QWidget *childWidget);

	protected:
		
	TlenUILoader();
	~TlenUILoader();
	TlenUILoader(const TlenUILoader &);
	void operator=(const TlenUILoader &);


	private:	
	TlenUILoaderPrivate *d;	
	static TlenUILoader *instance;
	
	friend class TlenApplication;
};

#endif
