#ifndef __TLEN_MESSAGE_BOX_H__
#define __TLEN_MESSAGE_BOX_H__

#include <QString>
#include <QMessageBox>

#include <core/export.h>
#include <data/TlenPluginAction.h>

class TlenSocket;
class TlenAccountConnection;
class TlenMessageBoxPrivate;

/**
 * Otwieranie okien pytającyh użytkownika o podjęcie decyzji
 */
class __tlen_gui_message_box__ TlenMessageBox
{
	public:
		static void critical(const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton, TlenPluginAction act);
		static void question(const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton, TlenPluginAction act);		
		static void information(const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton, TlenPluginAction act);
		static void warning(const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton, TlenPluginAction act);

		static QMessageBox::StandardButton critical(const QString & title, const QString & text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton);
		static QMessageBox::StandardButton question(const QString & title, const QString & text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton);
		static QMessageBox::StandardButton information(const QString & title, const QString & text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton);
		static QMessageBox::StandardButton warning(const QString & title, const QString & text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton);
				
		static void askForAuthorization(const QString &id, TlenAccountConnection *acc, TlenPluginAction act);	
		static void confirmSslCertificate(TlenSocket *, TlenPluginAction);		

		static void chooseFilesToOpen(TlenPluginAction act, const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString());
		static void chooseFileToOpen(TlenPluginAction act, const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString());
		static void chooseDirectory(TlenPluginAction act, const QString & caption = QString(), const QString & dir = QString());		
		static void chooseFileToSave(TlenPluginAction act, const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString());
		
		
		static QStringList chooseFilesToOpen(const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString());
		static QString chooseFileToOpen(const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString());
		static QString chooseDirectory(const QString & caption = QString(), const QString & dir = QString());		
		static QString chooseFileToSave(const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString());
};



#endif

