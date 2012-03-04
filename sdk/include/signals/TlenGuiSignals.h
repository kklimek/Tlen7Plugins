//Sygnały emitowane przez TLEN_PLUGIN_GUI

//Emitowany tuż przed pokazaniem menu kontekstowego.
//Umożliwia dodanie własnych pozycji do menu.
	signalRegister(CONTEXT_MENU_REQUESTED,
			QList<TlenArg::Type>()
			<< TlenArg::Pointer //TlenContextMenu - menu ktore zostanie pokazane
			<< TlenArg::Int //globalna pozycja na osi X
			<< TlenArg::Int //glibalna pozycja na osi Y
			);

//po utworzeniu nowego okna rozmowy
	signalRegister(CHAT_WINDOW_CREATED,
			QList<TlenArg::Type>()
			<< TlenArg::Pointer //TlenChatWindow - okno rozmowy ktore zostalo utworzone
			);
