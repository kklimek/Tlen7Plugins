#ifndef __TLEN_CHAT_MANAGER_H__
#define __TLEN_CHAT_MANAGER_H__

#include <core/export.h>

class TlenChatWindow;
class TlenChatManagerPrivate;
class TlenMainWindowPrivate;
class TlenGuiPlugin;

/**
 * Zarządza oknami rozmów
 */
class __tlen_gui_chat_manager__ TlenChatManager
{
	public:
		static TlenChatManager *getInstance();		

		/**
		 * Tworzy okno rozmowy z danym kontaktem
		 * @param  kontakt
		 * @return utworzone okno rozmowy
		 */
		TlenChatWindow *createChatWindow(const TlenBuddy &);
		/**
		 * Usuwa okno rozmowy
		 * @param  okno rozmowy
		 */
		void removeChatWindow(TlenChatWindow *);
		/**
		 * Zwraca okno rozmowy dla danego kontaktu
		 * @param  kontakt
		 * @return okno rozmowy
		 */
		TlenChatWindow *getChatWindow(const TlenBuddy &);
		/**
		 * Zwraca istniejące okna z rozmowami
		 * @return lista okien z rozmowami
		 */
		QList<TlenChatWindow *> getExistingChatWindows();
		
	private:
		TlenChatManager();
		TlenChatManager(const TlenChatManager &);
		void operator=(const TlenChatManager &);
		~TlenChatManager();
		
		static TlenChatManager *instance;		
		TlenChatManagerPrivate *d;
		friend class TlenMainWindowPrivate;
		friend class TlenGuiPlugin;
};

#endif

