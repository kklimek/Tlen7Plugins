#ifndef __TLEN_CONTEXT_MENU_H__
#define __TLEN_CONTEXT_MENU_H__

#include <core/export.h>
#include <data/TlenArg.h>
#include <gui/TlenAction.h>

/**
 * Reprezentuje menu kontekstowe
 */
class __tlen_gui_context_menu__ TlenContextMenu: public TlenAction
{
	public:
		TlenContextMenu(const QString &id, const QString &caption = QString(), const QString &ico = QString(), const QList<TlenArg> &actiondata = QList<TlenArg>());
		~TlenContextMenu();

		const QString getId() const;

		/**
		 * Dodaje akcje na koncu menu
		 */
		void addAction(TlenAction *);

		/**
		 * Dodaje podmenu na koncu menu
		 */
		void addMenu(TlenContextMenu *);
	
		/**
		 * Tworzy i dodaje akcje na koncu menu
		 * @param caption - tekst akcji
		 * @param icon - sciezka do ikony
		 * @param cb - callback akcji
		 * @return utworzona akcja
		 */
		TlenAction *addAction(const QString &caption, const QString &icon, const TlenPluginAction &, const QList<TlenArg> &actdata = QList<TlenArg>());

		/**
		 * Wstawia akcje na wybrana pozycje
		 * @param pos - pozycja w ktora chcemy wstawic, 0 bedzie zawsze na poczatku, -1 zawsze na koncu. Jesli wartosc pos jest wieksza niz ilosc pozycji w menu, to akcja wstawiona zostaje na koncu
		 */
		void insertAction(int pos, TlenAction *);

		/**
		 * Wstawia podmenu na wybrana pozycje
		 * @param pos - pozycja w ktora chcemy wstawic, 0 bedzie zawsze na poczatku, -1 zawsze na koncu. Jesli wartosc pos jest wieksza niz ilosc pozycji w menu, to akcja wstawiona zostaje na koncu
		 */
		void insertMenu(int pos, TlenContextMenu *);
	
		/**
		 * Tworzy i dodaje akcje na koncu menu
		 * @param pos - pozycja w ktora chcemy wstawic, 0 bedzie zawsze na poczatku, -1 zawsze na koncu. Jesli wartosc pos jest wieksza niz ilosc pozycji w menu, to akcja wstawiona zostaje na koncu
		 * @param caption - tekst akcji
		 * @param icon - sciezka do ikony
		 * @param cb - callback akcji
		 * @return utworzona akcja
		 */
		TlenAction *insertAction(int pos, const QString &caption, const QString &icon, const TlenPluginAction &, const QList<TlenArg> &actdata = QList<TlenArg>());

		QList<TlenAction *> actionList() const;
	
		int actionsCount() const;

		/**
		 * Usuwa akcje we wskazanej pozycji
		 * UWAGA: Metoda asertuje gdy parametr pos jest wiekszy niz ilosc akcji w menu
		 */
		TlenAction *removeAction(int pos);

		/**
		 * Usuwa wskazana  akcje z menu
		 * Jesli akcja nie znajduje sie w menu ta metoda nie robi nic
		 */
		void removeAction(TlenAction *);

		/**
		 * Dodaje separator na koncu menu
		 */
		void addSeparator();

		/**
		 * Dodaje separator we wskazanej pozycji
		 * @param pos - pozycja w ktora chcemy wstawic, 0 bedzie zawsze na poczatku, -1 zawsze na koncu. Jesli wartosc pos jest wieksza niz ilosc pozycji w menu, to akcja wstawiona zostaje na koncu
		*/
		void insertSeparator(int pos);

		bool containsAction(TlenAction *);

		bool isEmpty() const;

		TlenContextMenu * getSubmenu(const QString &id) const;

	private:
		QList<TlenAction *> actions;
		QString id;
};

#endif

