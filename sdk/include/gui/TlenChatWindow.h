#ifndef __TLEN_CHAT_WINDOW_H__
#define __TLEN_CHAT_WINDOW_H__

#include <QString>
#include <QDateTime>

#include <core/export.h>
#include <plugin/TlenProtocol.h>

class TlenChatWindowPrivate;
class TlenTabChatWindowPrivate;
class TlenAction;
class TlenGuiPluginHelper;
class TlenGuiPlugin;
class TlenConferenceChatManagerPrivate;

/**
 * Reprezentuje okno rozmowy
 */
class __tlen_gui_chat_window__ TlenChatWindow
{
	public:		
		/**
		 * Określa rodzaj dodawanego tekstu do okna rozmowy
		 */
		enum TextStyle {
			BuddyTextStyle=1, /**< wiadomość od kontaktu */
			OwnerTextStyle=2, /**< wiadomość wysyłana przez nas */
			InfoTextStyle=4,  /**< wiadomość informacyjna */
			ErrorTextStyle=8, /**< wiadomość o błędzie */
			HistoryTextStyle=16, /**< wiadomość wczytana z archiwum */
			HistoryBorderStyle=32, /**< odgraniczenie wiadomości bieżących od archiwalnych */
			PubdirTextStyle=64  /**< informacje z katalogu publicznego */
		};
		
		static QString formatWindowTitle(const TlenBuddy &buddy);

		/**
		 * Pokazuje okno rozmowy
		 */
		void show();		
		/**
		 * Pokazuje zminimalizowane okno rozmowy
		 */
		void showMinimized();
		/**
		 * Przełacza na dane okno przy włączonych zakładkach
		 */
		void switchTab();
		/**
		 * Przesuwa okno na pierwszy plan
		 */
		void bringToFront();
		/**
		 * Chowa okno
		 */
		void hide();
		
		/**
		 * Przeładowuje okno
		 */
		void reload();
		/**
		 * Zwraca czy okno jest widoczne
		 */
		bool isVisible() const;
		/**
		 * Zwraca czy okno jest zamknięte
		 */
		bool isClosed() const;
		/**
		 * Zwraca czy okno ma focus
		 */
		bool hasFocus() const;
		/**
		 * Dodaje akcje do toolbara
		 * @param act akcja
		 * @param groupName nazwa menu do, którego zostanie dodane 
		 * @param actionId id akcji
		 */
		void addToolbarAction(const TlenAction &act, QString groupName, const QString &actionId);
		/**
		 * Usuwa akcje z menu
		 * @param actionId id akcji
		 */
		void removeToolbarAction(const QString &actionId);
		/**
		 * Aktualizuje już dodaną akcje
		 * @param actionId id akcji
		 * @param act nowa akcja podmieniająca starą
		 */
		void updateToolbarAction(const QString &actionId, const TlenAction &act);		
		/**
		 * Dopisuje tekst w oknie rozmowy
		 * @param text tekst
		 * @param timestamp czas
		 * @param style rodzaj tekstu
		 */
		void appendText(const QString &text, TlenChatWindow::TextStyle style, const QString &timestamp=QString());
		/**
		 * Powiadamia o pisaniu
		 * @param type typ powiadomienia
		 */
		void typingNotify(TlenProtocol::TypingNotify type);
		/**
		 * Dodaje wiadomość informacyjną do okna rozmowy
		 * @param msg treść
		 */
		void notifyMessage(const QString &msg);
		/**
		 * Miganie okna rozmowy na pasku zadań
		 * @param msec czas przez jaki ma migać
		 */
		void flashTaskbar(int msec);		
		/**
		 * Zwraca kontakt przypisany do okna rozmowy
		 * @return kontakt
		 */
		TlenBuddy getBuddy() const;		
		/**
		 * Zwraca czas ostatniej odebranej lub wysłanej wiadomości
		 * @return 
		 */
		QDateTime getLastActivity() const;
		/**
		 * Ponownie otwiera ostatnio zamknięte okno rozmowy
		 */
		static void openLastClosed();		
		
	private:
		TlenChatWindow(const TlenBuddy &receipent);
		TlenChatWindow();
		TlenChatWindow(const TlenChatWindow &);
		void operator=(const TlenChatWindow &);
		~TlenChatWindow();
			

		friend class TlenChatManager;
		friend class TlenChatManagerPrivate;
		friend class TlenChatWindowPrivate;
		friend class TlenTabChatWindowPrivate;
		friend class TlenGuiPluginHelper;
		friend class TlenSettingsManagerWindow;
		friend class TlenConferenceChatManagerPrivate;
		friend class TlenGuiPlugin;
		TlenChatWindowPrivate *cwp;
};

#endif

