//Sygnały emitowane przez TLEN_PLUGIN_ROSTER

//dodany kontakt
	signalRegister(CONTACT_ADDED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);
//zmiana danych kontaktu
	signalRegister(CONTACT_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);
//usunięty kontakt
	signalRegister(CONTACT_REMOVED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);
//zmiana prezencji kontaktu
	signalRegister(CONTACT_PRESENCE_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			<< TlenArg::BuddyResource //zasób
			<< TlenArg::Presence //prezencja
			);
//zmiana subskrypcji kontaktu
	signalRegister(CONTACT_SUBSCRIPTION_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);
//zmiana awatara kontaktu	
	signalRegister(CONTACT_AVATAR_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);
//zmiana atrybutu kontaktu			
	signalRegister(CONTACT_ATTRIB_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			<< TlenArg::String //id atrybutu
			);	
//zmiana nazwy kontaktu	
	signalRegister(CONTACT_RENAMED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);
//dodana grupa
	signalRegister(GROUP_ADDED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //grupa
			);	
//usunięta grupa	
	signalRegister(GROUP_REMOVED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //grupa
			);
//kontakt usunięty z grupy	
	signalRegister(GROUP_CHILD_REMOVED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //grupa
			<< TlenArg::Buddy //kontakt
			);
//kontakt dodany do grup
	signalRegister(GROUP_CHILD_ADDED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //grupa
			<< TlenArg::Buddy //kontakt
			);
//zmiana nazwy grupy
	signalRegister(GROUP_RENAMED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //grupa
			);
//dodany kontakt specjalny		
	signalRegister(CUSTOM_ADDED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);				
//dodany kontakt tymczasowy
	signalRegister(TEMPORARY_ADDED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);
//usunięty kontakt tymczasowy	
	signalRegister(TEMPORARY_REMOVED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);
//usunięty kontakt specjalny	
	signalRegister(CUSTOM_REMOVED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);	
//zmieniony kontakt specjalny		
	signalRegister(CUSTOM_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //kontakt
			);	
//utworzony metakontakt
	signalRegister(META_ADDED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //metakontakt
			);
//zmieniony metakontakt	
	signalRegister(META_CHANGED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //metakontakt
			);
//usuniety kontakt z metakontaktu	
	signalRegister(META_CHILD_REMOVED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //metakontakt
			<< TlenArg::Buddy //kontakt
			);
//dodany kontakt do metakontaktu	
	signalRegister(META_CHILD_ADDED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //metakontakt
			<< TlenArg::Buddy //kontakt
			);
//metakontakt usuniety	
	signalRegister(META_REMOVED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //metakontakt
			);
//metakontakt rozwiniety	
	signalRegister(META_EXPANDED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //metakontakt
			);
//zmiana nazwy metakontaktu	
	signalRegister(META_RENAMED,
			QList<TlenArg::Type>()
			<< TlenArg::Buddy //metakontakt
			);