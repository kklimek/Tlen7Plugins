//Sygnały emitowane przez TLEN_PLUGIN_CORE 
	
//Zainicjalizowaniu programu 
	d->signalRegister(d->core, APP_INITIALIZED, 
			QList<TlenArg::Type>());
	
//Wyłączanie programu
	d->signalRegister(d->core, APP_QUITTING, 
			QList<TlenArg::Type>());
	
//Konto włączone 
	d->signalRegister(d->core, ACC_ENABLED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //wskaźnik do konta
			);
//Konto wyłączone 
	d->signalRegister(d->core, ACC_DISABLED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //wskaźnik do konta
			);
//Konto usunięte 
	d->signalRegister(d->core, ACC_REMOVED, 
			QList<TlenArg::Type>()
			<< TlenArg::String //id konta
			<< TlenArg::String //id protokołu
			);
//Plugin załadowany 
	d->signalRegister(d->core, PLUGIN_LOADED,
			QList<TlenArg::Type>()
			<< TlenArg::String //nazwa pluginu
			<< TlenArg::ServiceList //lista dostarczanych usług
			<< TlenArg::StringList //lista sygnałów
			);
//Plugin wyładowany 	
	d->signalRegister(d->core, PLUGIN_UNLOADED,
			QList<TlenArg::Type>()
			<< TlenArg::String //nazwa pluginu
			<< TlenArg::ServiceList //lista dostarczanych usług
			<< TlenArg::StringList //lista sygnałów
			);
//Protokół załadowany 	
	d->signalRegister(d->core, LOADED_PROTOCOL,
			QList<TlenArg::Type>()
			<< TlenArg::String //id protokołu
			<< TlenArg::Plugin //wskażnik do wtyczki protokołu
			);
//Protokół wyładowany 	
	d->signalRegister(d->core, UNLOADED_PROTOCOL,
			QList<TlenArg::Type>()
			<< TlenArg::String //nazwa protokołu
			<< TlenArg::String //id protokołu
			);
//Emitowany tuż przed wysłaniem wiadomości	
	d->signalRegister(d->core, MSG_ABOUT_TO_SEND,
			QList<TlenArg::Type>()
			<< TlenArg::Account
			<< TlenArg::String //id kontaktu
			<< TlenArg::String //treść wiadomości
			<< TlenArg::String //zasób
			);
//Wiadomość od użytkownika przeczytana 						
	d->signalRegister(d->core, MSG_READ,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt	
			);	
//Wysyłany przy wysyłaniu powiadomienia 			
	d->signalRegister(d->core, POST_NOTIFICATION,
			QList<TlenArg::Type>()
			<< TlenArg::String //typ powiadomienia: INFO_NOTIFY, ERROR_NOTIFY, EMAIL_NOTIFY, ALERT_SENT_NOTIFY, ALERT_RECEIVED_NOTIFY
			<< TlenArg::String //tytuł
			<< TlenArg::String //treść
			<< TlenArg::String //ścieżka do ikonki
			<< TlenArg::String //ścieżka do ikonki grupowania
			<< TlenArg::PluginAction //akcja która ma zostać wywołana
			<< TlenArg::ArgList //parametry akcji
			);
