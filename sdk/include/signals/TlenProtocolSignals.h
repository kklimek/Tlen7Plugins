//Sygnały emitowane przez wtyczki protokołów 
	
//otrzymano wiadomość 
	protocol->signalRegister(MESSAGE_RECEIVED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id kontaktu
			<< TlenArg::String //tresc
			<< TlenArg::String //czas
			<< TlenArg::String //zasób
			<< TlenArg::String //temat
			);
//wysyłana wiadomość 	
	protocol->signalRegister(MESSAGE_SENT,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id kontaktu
			<< TlenArg::String //tresc
			<< TlenArg::String //zasób
			);
//powiadomienie o pisaniu 	
	protocol->signalRegister(TYPING_NOTIFY,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id kontaktu
			<< TlenArg::Int //typ powiadomienia TlenPlugin::TypingNotify
			<< TlenArg::String //zasób
			);
//otrzymano alert 	
	protocol->signalRegister(ALERT_RECEIVED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id kontaktu
			<< TlenArg::String //zasób
			);
//zalogowano konto 	
	protocol->signalRegister(ACC_LOGGED_IN,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			);			
//wylogowano konto 	
	protocol->signalRegister(ACC_LOGGED_OUT,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			);			
			
//zmieniono zasób konta 	
	protocol->signalRegister(ACC_RESOURCE_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //zasób
			);	
			
//bład autoryzacji 	
	protocol->signalRegister(ACC_AUTHORIZATION_ERROR,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			);
//zmiana prezencji 	
	protocol->signalRegister(ACC_PRESENCE_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			);
//ustawiono awatar 
	protocol->signalRegister(ACC_AVATAR_SET,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			);
//otrzymanow awatar 	
	protocol->signalRegister(ACC_AVATAR_RECEIVED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			);			
//błąd ustawiania awatar 	
	protocol->signalRegister(ACC_AVATAR_SET_ERROR,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //opis błedu
			);
//usunięto awatar 		
	protocol->signalRegister(ACC_AVATAR_REMOVED,
			QList<TlenArg::Type>()
			<< TlenArg::Account
			);
//pobrano dane z katalogu publicznego 		
	protocol->signalRegister(PUBDIR_ACC_DATA_RECEIVED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::FieldList //zawartość katalogu publicznego
					);
//usunięto dane z katalogu publicznego 		
	protocol->signalRegister(PUBDIR_ACC_DATA_REMOVED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			);
//zmieniono dane w katalogu publicznym 		
	protocol->signalRegister(PUBDIR_ACC_DATA_EDITED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			);
//wynik wyszukiwania w katalogu publicznym 	
	protocol->signalRegister(PUBDIR_SEARCH_RESULT_RECEIVED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::Int //ile wyników
			<< TlenArg::FieldList //otrzymane dane
			<< TlenArg::Bool	//true jeśli są kolejne dane
			);
//otrzymano informacje o ostatniej aktywnosci kontaktu	
	protocol->signalRegister(LAST_ACTIVITY_RECEIVED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id kontaktu
			<< TlenArg::Int //sekundy od ostatniej aktywnosci/bycia online
			);			
//rozpoczecie konferencji
	protocol->signalRegister(CONF_STARTED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::String //nick
			<< TlenArg::String //nazwa pokoju
			<< TlenArg::String //grupa do ktorej nalezy pokoj
			<< TlenArg::StringList //osoby w pokoju
		);
//otrzymanie wiadomosci konferencyjnej
	protocol->signalRegister(CONF_MESSAGE_RECEIVED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::String //id rozmowcy
			<< TlenArg::String //wiadomosc
			<< TlenArg::String //timestamp
			<< TlenArg::TextFormatList //formatowanie wiadomosci
			);
//wyslanie wiadomosci konferencyjnej				
	protocol->signalRegister(CONF_MESSAGE_SENT,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::String //wiadomosc
			);
//zmiana tematu czatu				
	protocol->signalRegister(CONF_TOPIC_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::String //nowy temat
			);			
//dolaczenie nowej osoby do czatu	
	protocol->signalRegister(CONF_BUDDY_JOINED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::String //nazwa osoby
			<< TlenArg::Int // status osoby TlenConferenceUserStatus::Status
			<< TlenArg::String //id osoby
			);	
//opuszczenie przez osobe do czatu							
	protocol->signalRegister(CONF_BUDDY_LEFT,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::String //nazwa osoby
			<< TlenArg::String //id osoby
			);
//zmiana statusu osoby na czacie					
	protocol->signalRegister(CONF_BUDDY_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::String //id osoby
			<< TlenArg::Int //nowy status osoby TlenConferenceUserStatus::Status
			);
//zmiana uprawnien uzytkownika na czacie			
	protocol->signalRegister(CONF_PRIVILEGES_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::Int //nowe uprawnienia TlenConferencePrivileges::Privileges
			);	
						
//otrzymanie listy uzytkownikow czatu						
	protocol->signalRegister(CONF_RECEIVED_USER_LIST,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::Int //jaki typ osob pobrano TlenConferenceUserStatus::Status
			<< TlenArg::ArgList //QList<TlenArg> id, nick, wygasa, powod, czas, admin
			);	
//otrzymano liste pokoi		
	protocol->signalRegister(CONF_RECEIVED_ROOMS,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::ArgList //QList<TlenArg> pokoje: id, nazwa, flagi, liczba osob w pokoju
			//poszczegolne bity we flagach oznaczaja:  pokoj publiczny, pokoj anonimowy,
			//pokoj staly, pokoj tylko dla czlonkow, pokoj administrowany, pokoj moderowany, pokoj zdefiniowany przez o2 
			);
//otrzymano grupe pokoi						
	protocol->signalRegister(CONF_RECEIVED_GROUPS,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id czatu
			<< TlenArg::ArgList //QList<TlenArg> id, nazwa, flagi
			);
//otrzymano liste utworzonych przez nas pokoi	
	protocol->signalRegister(CONF_RECEIVED_MY_ROOMS,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::ArgList ////QList<TlenArg>: id, nazwa
			);					
//otrzymano liste zarejestrowanych nickow			
	protocol->signalRegister(CONF_RECEIVED_NICKS,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::StringList //lista nickow
			);				
//otrzymano zaproszenie do konferencji				
	protocol->signalRegister(CONF_INVITED,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //id konferencji
			);						
						
//przyjscie nowego maila na skrzynke		
	protocol->signalRegister(NEW_MAIL,
			QList<TlenArg::Type>()
			<< TlenArg::Account //konto
			<< TlenArg::String //od kogo
			<< TlenArg::String //temat
			<< TlenArg::String //wiadomosc
			<< TlenArg::String //url
			);	
		
						
	if(protocol->isXmlProtocol()) {
//otrzymano xml node 	
		protocol->signalRegister(XML_PROTOCOL_ON_NODE,
			   QList<TlenArg::Type>()
			   << TlenArg::Account //konto
			   << TlenArg::XmlNode //xml node
			   );
		protocol->signalRegister(XML_PROTOCOL_NODE_SENT,
			   QList<TlenArg::Type>()
			   << TlenArg::Account //konto
			   << TlenArg::XmlNode //xml node
			   );   	
			   	
			   	
	}
