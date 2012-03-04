#ifndef _TLEN_FIELD_H_
#define _TLEN_FIELD_H_

#include <QStringList>
#include <QString>
#include <QDate>

#include <core/export.h>
#include <data/TlenPluginAction.h>
#include <xml/TlenXmlNode.h>

class TlenArg;
class TlenFieldPrivate;

/**
 * \brief Klasa opisująca pola do interakcji z użytkownikiem.
 *
 * Uwzglednia jaki typ kontrolki ma zostać utworzony. Pozwala ustalić maksymalne, minimalne oraz domyślne wartości
 */
class __tlen_data__ TlenField
{
	public:
		/**
		 * \brief Określa typ TlenField
		 *
		 * TlenField różnych typów mają rożne gettery i settery. Użycie settera lub gettera nieodpowiedniego dla danego typu TlenField kończy się przerwaniem programu.
		 * \sa getType()
		 */
		enum Type {
			None,		/**< Nie przechowuje żadnych danych. Ten typ TlenField jest ignorowany przy budowaniu elementów GUI. */
			ComboBox,	/**< Kontrolka combo box (lista opcji). Przechowuje listę opcji oraz wybrany indeks. */
			CheckBox,	/**< Kontrolka check box. Przechowuje czy box jest zaznaczony czy nie. */
			RadioButton,	/**< Kontrolka radio button. Przechowuje czy box jest zaznaczony. */
			LineEdit,	/**< Kontrolka pojedynczej linii edycji. Przechowuje wpisany tekst. Ma ograniczoną długość wpisywanego tekstu. */
			DirEdit, 	/**< Kontrolka umozliwiajaca wpisanie reczne sciezki albo wybranie katalogu w oknie wyboru katalogu. */
			FileEdit, 	/**< Kontrolka umozliwiajaca wpisanie reczne sciezki albo wybranie pliku w oknie wyboru pliku. */
			SoundEdit, 	/**< Kontrolka umozliwiajaca wybranie pliku dzwiekowego. */
			PasswordEdit,   /**< To samo co LineEdit tylko tekst jest zagwiazdkowany*/
			TextEdit,	/**< Kontrolka wielolinijkowego pola wprowadzania tekstu. Przechowuje wpisany tekst. Tekst ma nieograniczoną długość. */
			SpinBox,	/**< Kontrolka pola wyboru liczby całkowitej. Przechowuje wybraną wartość. Ma ograniczoną wartość graniczną górną i dolną. */
			DoubleSpinBox,	/**< Kontrolka pola wyboru liczby zmiennoprzecinkowej. Przechowuje wybraną wartość. Ma ograniczoną wartość graniczną górną i dolną. */
			Label, 		/**< Kontrolka - label*/
			Image,		/**< Obrazek	*/
			Button,		/**< Przycisk */
			Date,		/**< Kontrolka pola wyboru daty */
		//	ListBox,	/**< Kontrolka listy, z mozliwością ustalenia ilości kolumn, dodawania, edytowania i usuwania elementów. Kolumny opisywane są przez inne TlenField, dzięki czemu można sprecyzować typ wprowadzanych danych */
		};

		/**
		 * Tworzy TlenField typu TlenField::None. Ten TlenField jest ignorowany przy budowaniu elementów GUI.
		 * \sa TlenField(const QString &, const QString &, const QStringList &, int), 
		 * TlenField(const QString &, const QString &, int, int, int), 
		 * TlenField(const QString &, const QString &, double, double, double), 
		 * TlenField(TlenField::Type, const QString &, const QString &, bool),
		 * TlenField(TlenField::Type, const QString &, const QString &, const QString &, int);
		 */
		TlenField();
		
		
		static TlenField date(const QString &label, const QString &id, const QDate &dt, const QString &g = QString());
		
				
		/**
		 * Tworzy TlenField typu TlenField::Image
		 * @param id - identyfikator pola
		 * @param imgData - binarne dane obrazka w formacie jaki QT obsluzy, png, jpeg, itd
		 * @param group - nazwa grupy do której ma nalezec TlenField.
		 */
		static TlenField image(const QString &id, const QByteArray &imgData, const QString &g = QString());

		/**
		 * Tworzy TlenField typu TlenField::Label
		 * @param label - etykieta pola wyswietlana w programie.
		 * @param id - identyfikator pola
		 * @param group - nazwa grupy do której ma nalezec TlenField.
		 */
		static TlenField label(const QString &label, const QString &id, const QString &g = QString());

		/**
		 * Tworzy TlenField typu TlenField::Button
		 * @param label - etykieta pola wyswietlana w programie.
		 * @param id - identyfikator pola
		 * @param action - akcja wykonywana po kliknieciu
		 * @param group - nazwa grupy do której ma nalezec TlenField.
		 */	
		static TlenField button(const QString &label, const QString &id, TlenPluginAction action, const QString &g = QString());

	
		/**
		 * Tworzy TlenField typu TlenField::ComboBox z lista opcji `data` i z wybranym indexem `selected`
		 * @param label - etykieta pola wyświetlana w programie.
		 * @param id - identyfikator pola
		 * @param data - opcje do wyboru w ComboBox
		 * @param selected - domyslnie wybrany indeks
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 * \sa TlenField(),
		 * TlenField(const QString &, const QString &, int, int, int), 
		 * TlenField(const QString &, const QString &, double, double, double), 
		 * TlenField(TlenField::Type, const QString &, const QString &, bool),
		 * TlenField(TlenField::Type, const QString &, const QString &, const QString &, int);
		 */
		static TlenField comboBox(const QString &label, const QString &id, const QStringList &ids, const QStringList &labels=QStringList(), const QString &selectedId=QString(), const QString &group = QString());

		/**
		 * Tworzy TlenField typu TlenField::SpinBox z maksymalna wartościa `max`, minimalna wartościa `min` i wartośćia domyślna `value`
		 * @param label - etykieta pola wyświetlana w programie
		 * @param id - identyfikator pola
		 * @param max - maksymalna mozliwa wartość pola
		 * @param min - minimalna mozliwa wartość pola
		 * @param value - domyślna wartość pola. UWAGA!!! wartość ta musi być większa badz równa wartości min i mniejsza badz rowna wartosci max. Inaczej konstruktor program zostaje przerwany
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 */
		static TlenField spinBox(const QString &label, const QString &id, int max, int min, int value, const QString &group = QString(), const QString &suffix = QString());

		/**
		 * Tworzy TlenField typu TlenField::DoubleSpinBox z maksymalna wartościa `max`, minimalna wartościa `min` i wartośćia domyślna `value`
		 * @param label - etykieta pola wyświetlana w programie
		 * @param id - identyfikator pola
		 * @param max - maksymalna mozliwa wartość pola
		 * @param min - minimalna mozliwa wartość pola
		 * @param value - domyślna wartość pola. UWAGA!!! wartość ta musi być większa badz równa wartości min i mniejsza badz rowna wartosci max. Inaczej konstruktor program zostaje przerwany
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 * \sa TlenField(),
		 * TlenField(const QString &, const QString &, const QStringList &, int),
		 * TlenField(const QString &, const QString &, int, int, int), 
		 * TlenField(TlenField::Type, const QString &, const QString &, bool),
		 * TlenField(TlenField::Type, const QString &, const QString &, const QString &, int);
		 */
		static TlenField doubleSpinBox(const QString &label, const QString &id, double max, double min, double value, const QString &group = QString());

		/**
		 * Tworzy TlenField typu TlenField::RadioButton
		 * @param label - etykieta pola wyświetlana w programie
		 * @param id - identyfikator pola
		 * @param checked - domyślna wartość pola. zaznaczone (true) lub niezaznaczone (fasle)
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 */
		static TlenField radioButton(const QString &label, const QString &id, bool checked, const QString &group = QString(), const QStringList &depends = QStringList());
	
		/**
		 * Tworzy TlenField typu TlenField::CheckBox
		 * @param label - etykieta pola wyświetlana w programie
		 * @param id - identyfikator pola
		 * @param checked - domyślna wartość pola. zaznaczone (true) lub niezaznaczone (fasle)
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 * \sa TlenField(),
		 * TlenField(const QString &, const QString &, const QStringList &, int),
		 * TlenField(const QString &, const QString &, int, int, int), 
		 * TlenField(const QString &, const QString &, double, double, double), 
		 * TlenField(TlenField::Type, const QString &, const QString &, const QString &, int);
		 */
		static TlenField checkBox(const QString &label, const QString &id, bool checked, const QString &group = QString(), const QStringList &depends = QStringList());
	
		/**
		 * Tworzy TlenField typu TlenField::LineEdit
		 * @param label - etykieta pola wyświetlana w programie
		 * @param id - identyfikator pola
		 * @param value - domyślna wartość pola
		 * @param maxlength - maksymalna dlugosc pola. Dotyczy tylko TlenField::LineEdit
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 * \sa TlenField(),
		 * TlenField(const QString &, const QString &, const QStringList &, int),
		 * TlenField(const QString &, const QString &, int, int, int), 
		 * TlenField(const QString &, const QString &, double, double, double), 
		 * TlenField(TlenField::Type, const QString &, const QString &, bool),
		 */
		static TlenField lineEdit(const QString &label, const QString &id, const QString &value, int maxlength = 32767, const QString &group = QString());

		/**
		 * Tworzy TlenField typu TlenField::PasswordEdit
		 * @param label - etykieta pola wyświetlana w programie
		 * @param id - identyfikator pola
		 * @param value - domyślna wartość pola
		 * @param maxlength - maksymalna dlugosc pola. Dotyczy tylko TlenField::LineEdit
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 * \sa TlenField(),
		 * TlenField(const QString &, const QString &, const QStringList &, int),
		 * TlenField(const QString &, const QString &, int, int, int), 
		 * TlenField(const QString &, const QString &, double, double, double), 
		 * TlenField(TlenField::Type, const QString &, const QString &, bool),
		 */
		static TlenField passwordEdit(const QString &label, const QString &id, const QString &value, int maxlength = 32767, const QString &group = QString());

		/**
		 * Tworzy TlenField typu TlenField::TextEdit
		 * @param label - etykieta pola wyświetlana w programie
		 * @param id - identyfikator pola
		 * @param value - domyślna wartość pola
		 * @param maxlength - maksymalna dlugosc pola. Dotyczy tylko TlenField::LineEdit
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 * \sa TlenField(),
		 * TlenField(const QString &, const QString &, const QStringList &, int),
		 * TlenField(const QString &, const QString &, int, int, int), 
		 * TlenField(const QString &, const QString &, double, double, double), 
		 * TlenField(TlenField::Type, const QString &, const QString &, bool),
		 */
		static TlenField textEdit(const QString &label, const QString &id, const QString &value, const QString &group = QString());
		
		/**
		 * Tworzy TlenField typu TlenField::DirEdit
		 * @param label - etykieta pola wyświetlana w programie
		 * @param id - identyfikator pola
		 * @param value - domyślna wartość pola
		 * @param maxlength - maksymalna dlugosc pola. Dotyczy tylko TlenField::LineEdit
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 * \sa TlenField(),
		 * TlenField(const QString &, const QString &, const QStringList &, int),
		 * TlenField(const QString &, const QString &, int, int, int), 
		 * TlenField(const QString &, const QString &, double, double, double), 
		 * TlenField(TlenField::Type, const QString &, const QString &, bool),
		 */
		static TlenField dirEdit(const QString &label, const QString &id, const QString &value, const QString &group = QString());
		
		/**
		 * Tworzy TlenField typu TlenField::SoundEdit
		 * @param label - etykieta pola wyświetlana w programie
		 * @param id - identyfikator pola
		 * @param value - domyślna wartość pola
		 * @param maxlength - maksymalna dlugosc pola. Dotyczy tylko TlenField::LineEdit
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 * \sa TlenField(),
		 * TlenField(const QString &, const QString &, const QStringList &, int),
		 * TlenField(const QString &, const QString &, int, int, int), 
		 * TlenField(const QString &, const QString &, double, double, double), 
		 * TlenField(TlenField::Type, const QString &, const QString &, bool),
		 */
		static TlenField soundEdit(const QString &label, const QString &id, const QString &value, const QString &group = QString());
		
		/**
		 * Tworzy TlenField typu TlenField::FileEdit
		 * @param label - etykieta pola wyświetlana w programie
		 * @param id - identyfikator pola
		 * @param value - domyślna wartość pola
		 * @param maxlength - maksymalna dlugosc pola. Dotyczy tylko TlenField::LineEdit
		 * @param group - nazwa grupy do której ma należeć TlenField.
		 * \sa TlenField(),
		 * TlenField(const QString &, const QString &, const QStringList &, int),
		 * TlenField(const QString &, const QString &, int, int, int), 
		 * TlenField(const QString &, const QString &, double, double, double), 
		 * TlenField(TlenField::Type, const QString &, const QString &, bool),
		 */
		static TlenField fileEdit(const QString &label, const QString &id, const QString &value, const QString &group = QString());
	
		TlenField(const TlenField &other);
		~TlenField();
		TlenField operator=(const TlenField &other);

		/**
		 * @return etykieta pola
		 * \sa getId(), getGroup()
		 */
		QString getLabel() const;

		/**
		 * @return identyfikator pola 
		 * \sa getLabel(), getGroup()
		 */
		QString getId() const;

		/**
		 * @return nazwa grupy
		 * \sa getLabel(), getId()
		 */
		QString getGroup() const;

		/**
		 * @return typ pola
		 * \sa TlenField::Type
		 */
		TlenField::Type getType() const;

		TlenArg getValue() const;
		
		void setExtendedDescription(const QString &);
		QString getExtendedDescription() const;
	
		void setVisible(bool state);
		bool getVisible() const;
		QString getSuffix() const;
		

		/**
		 * Dotyczy tylko pól typu TlenField::LineEdit i TlenField::TextEdit. W innym przypadku program zostaje przerwany
		 * @return tekst pola
		 * \sa setText(), setMaxTextLength(), getMaxTextLength()
		 */
		QString getText() const;


		/**
		 * Dotyczy tylko pól typu TlenField::LineEdit i TlenField::TextEdit. W innym przypadku program zostaje przerwany
		 * Ustala tekst pola.
		 * UWAGA!!! Jeśli póle zostanie utworzone do interakcji z uzytkownikiem, to jakiekolwiek zmiany w nim nie zostana odzwierciedlone
		 * @param text - nowy tekst pola
		 * \sa getText(), setMaxTextLength(), getMaxTextLength() 
		 */
		void setText(const QString &text);
		void setLabel(const QString &text);

		/**
		 * Dotyczy tylko pola typu TlenField::LineEdit. W innym przypadku program zostaje przerwany
		 * Ustala maksymalna dlugosc wartości pola
		 * UWAGA!!! Jeśli póle zostanie utworzone do interakcji z uzytkownikiem, to jakiekolwiek zmiany w nim nie zostana odzwierciedlone
		 * @param len - maksymalna mozliwa dlugosc pola (ilosc znakow)
		 * \sa getText(), setText(), getMaxTextLength()
		 */
		void setMaxTextLength(int len);

		/**
		 * Dotyczy tylko pola typu TlenField::LineEdit. W innym przypadku program zostaje przerwany
		 * @return maksymalna dlugosc wartości pola
		 * \sa getText(), setText(), setMaxTextLength()
		 */
		int getMaxTextLength() const;
		
		int getMaxIntValue() const;
		int getMinIntValue() const;
		
		/**
		 * Dotyczy tylko pola typu TlenField::DoubleSpinBox. W innym przypadku program zostaje przerwany
		 * @return obecnie wskazana wartość pola
		 * \sa setDoubleValue(), setDoubleSpinBoxMax(), getDoubleSpinBoxMax(), setDoubleSpinBoxMin(), getDoubleSpinBoxMin()
		 */
		double getDoubleValue() const;

		/**
		 * Dotyczy tylko pola typu TlenField::DoubleSpinBox. W innym przypadku program zostaje przerwany
		 * UWAGA!!! Jeśli póle zostanie utworzone do interakcji z uzytkownikiem, to jakiekolwiek zmiany w nim nie zostana odzwierciedlone
		 * @param val - nowa wartość pola. Jeśli val jest wieksze niż maksymalna wartość, lub mniejsze niz minimalna wartosc metoda asertuje.
		 * \sa getDoubleValue(), setDoubleSpinBoxMax(), getDoubleSpinBoxMax(), setDoubleSpinBoxMin(), getDoubleSpinBoxMin()
		 */
		void setDoubleValue(double val);

		/**
		 * Dotyczy tylko pola typu TlenField::DoubleSpinBox. W innym przypadku program zostaje przerwany
		 * Ustala maksymalna wartość pola.
		 * UWAGA!!! Jeśli póle zostanie utworzone do interakcji z uzytkownikiem, to jakiekolwiek zmiany w nim nie zostana odzwierciedlone
		 * @param max - nowe mozliwe maksimum pola. Jeśli `max` jest mniejsze od obecnego minimum, metoda asertuje
		 * Jeśli obecna wartość pola jest większa niż nowe maksimum to wartości tej przypisywana jest wartość nowego maksimum
		 * \sa getDoubleValue(), setDoubleValue(), getDoubleSpinBoxMax(), setDoubleSpinBoxMin(), getDoubleSpinBoxMin()
		 */
		void setDoubleSpinBoxMax(double max);

		/**
		 * Dotyczy tylko pola typu TlenField::DoubleSpinBox. W innym przypadku program zostaje przerwany
		 * @return maksymalna mozliwa wartość pola
		 * \sa getDoubleValue(), setDoubleValue(), setDoubleSpinBoxMax(), setDoubleSpinBoxMin(), getDoubleSpinBoxMin()
		 */
		double getDoubleSpinBoxMax() const;

		/**
		 * Dotyczy tylko pola typu TlenField::DoubleSpinBox. W innym przypadku program zostaje przerwany
		 * Ustala minimalna wartość pola
		 * UWAGA!!! Jeśli póle zostanie utworzone do interakcji z uzytkownikiem, to jakiekolwiek zmiany w nim nie zostana odzwierciedlone
		 * @param min - nowe mozliwe minimum pola. Jeśli `min` jest wieksze od obecnego maksimum pola, metoda asertuje.
		 * Jeśli obecna wartość pola jest mniejsza niż nowe minimum to wartości tej przypisywana jest wartość nowego minimum
		 * \sa getDoubleValue(), setDoubleValue(), setDoubleSpinBoxMax(), getDoubleSpinBoxMax(), getDoubleSpinBoxMin()
		 */
		void setDoubleSpinBoxMin(double min);

		/**
		 * Dotyczy tylko pola typu TlenField::DoubleSpinBox. W innym przypadku program zostaje przerwany
		 * @return minimalna mozliwa wartość pola
		 * \sa getDoubleValue(), setDoubleValue(), setDoubleSpinBoxMax(), getDoubleSpinBoxMax(), setDoubleSpinBoxMin()
		 */
		double getDoubleSpinBoxMin() const;

		/**
		 * Dotyczy tylko pola typu TlenField::SpinBox. W innym przypadku program zostaje przerwany
		 * @return obecnie wskazana wartość pola
		 * \sa getIntValue(), setIntValue(), setSpinBoxMax(), getSpinBoxMax(), setSpinBoxMin(), getSpinBoxMin()
		 */
		int getIntValue() const;

		/**
		 * Dotyczy tylko pola typu TlenField::SpinBox. W innym przypadku program zostaje przerwany
		 * UWAGA!!! Jeśli póle zostanie utworzone do interakcji z uzytkownikiem, to jakiekolwiek zmiany w nim nie zostana odzwierciedlone
		 * @param val - nowa wartość pola. Jeśli val jest wieksze niż maksymalna wartość, lub mniejsze niz minimalna wartosc metoda asertuje.
		 * \sa getIntValue(), setSpinBoxMax(), getSpinBoxMax(), setSpinBoxMin(), getSpinBoxMin()
		 */
		void setIntValue(int val);

		/**
		 * Dotyczy tylko pola typu TlenField::SpinBox. W innym przypadku program zostaje przerwany
		 * Ustala maksymalna wartość
		 * UWAGA!!! Jeśli póle zostanie utworzone do interakcji z uzytkownikiem, to jakiekolwiek zmiany w nim nie zostana odzwierciedlone
		 * @param max - nowe mozliwe maksimum pola. Jeśli `max` jest mniejsze od obecnego minimum pola, metoda asertuje
		 * Jeśli obecna wartość pola jest większa niż nowe maksimum to wartości tej przypisywana jest wartość nowego maksimum
		 * \sa getIntValue(), setIntValue(), getSpinBoxMax(), setSpinBoxMin(), getSpinBoxMin()
		 */
		void setSpinBoxMax(int max);

		/**
		 * Dotyczy tylko pola typu TlenField::SpinBox. W innym przypadku program zostaje przerwany
		 * @return maksymalna mozliwa wartość pola
		 * \sa getIntValue(), setIntValue(), setSpinBoxMax(), setSpinBoxMin(), getSpinBoxMin()
		 */
		int getSpinBoxMax() const;

		/**
		 * Dotyczy tylko pola typu TlenField::SpinBox. W innym przypadku program zostaje przerwany
		 * Ustala nowe minimum pola
		 * UWAGA!!! Jeśli póle zostanie utworzone do interakcji z uzytkownikiem, to jakiekolwiek zmiany w nim nie zostana odzwierciedlone
		 * @param min - nowe mozliwe maksimum pola. Jeśli `min` jest wieksze od obecnego maksimum pola, metoda asertuje
		 * Jeśli obecna wartość pola jest mniejsza niż nowe minimum to wartości tej przypisywana jest wartość nowego minimum
		 * \sa getIntValue(), setIntValue(), setSpinBoxMax(), getSpinBoxMax(), getSpinBoxMin()
		 */
		void setSpinBoxMin(int min);

		/**
		 * Dotyczy tylko pola typu TlenField::SpinBox. W innym przypadku program zostaje przerwany
		 * @return minimalna mozliwa wartość pola
		 * \sa getIntValue(), setIntValue(), setSpinBoxMax(), getSpinBoxMax(), setSpinBoxMin()
		 */
		int getSpinBoxMin() const;

		/**
		 * Dotyczy tylko pól typu TlenField::CheckBox i TlenField::RadioButton. W innym przypadku program zostaje przerwany
		 * @return czy póle jest zaznaczone
		 * \sa setChecked()
		 */
		bool isChecked() const;

		/**
		 * Dotyczy tylko pól typu TlenField::LineEdit i TlenField::TextEdit. W innym przypadku program zostaje przerwany
		 * Ustala czy póle ma być zaznaczone
		 * UWAGA!!! Jeśli póle zostanie utworzone do interakcji z uzytkownikiem, to jakiekolwiek zmiany w nim nie zostana odzwierciedlone
		 * @param checked - true = zaznaczone, false = odznaczone
		 * \sa isChecked
		 */
		void setChecked(bool checked);

		/**
		 * Dotyczy tylko pola typu TlenField::ComboBox. W innym przypadku program zostaje przerwany
		 * @return wybrany obecnie string
		 * \sa setSelectedIndex(), getSelectedIndex(), getComboBoxItems()
		 */
		QString getSelectedLabel() const;
		QString getSelectedId() const;
		int getSelectedIndex() const;

		/**
		 * Dotyczy tylko pola typu TlenField::ComboBox. W innym przypadku program zostaje przerwany
		 * Zmienia wybrany indeks
		 * UWAGA!!! Jeśli póle zostanie utworzone do interakcji z uzytkownikiem, to jakiekolwiek zmiany w nim nie zostana odzwierciedlone
		 * @param idx - nowy wybrany index. Jeśli `idx` jest wiekszy badz rowny ilosci opcji do wyboru, metoda asertuje.
		 * \sa getSelectedString(), getSelectedIndex(), getComboBoxItems()
		 */
		void setSelectedId(const QString &id);
		void setSelectedIndex(int idx);



		/**
		 * Dotyczy tylko pola typu TlenField::ComboBox. W innym przypadku program zostaje przerwany
		 * @return lista opcji w tej samej kolejnosci w ktorej zostanie wyswietlona w programie
		 * \sa getSelectedString(), setSelectedIndex(), getSelectedIndex()
		 */
		QStringList getComboBoxIds() const;
		QStringList getComboBoxLabels() const;

		/**
		 * Dotyczy tylko pola typu TlenField::ComboBox. W innym przypadku program zostaje przerwany
		 * Ustala liste opcji. Przy zmianie listy opcji wybrany indeks zostaje ustawiony na 0
		 * @param sl - lista opcji
		 */
		void setComboBoxItems(const QStringList &ids, const QStringList &labels);

		/**
		 * Porownuje dwa TlenField
		 * TlenField sa identyczne jesli maja identyczne typy, identyfikatory, etykiety i wartości
		 */
		bool operator==(const TlenField &field) const;

		/**
		 * Wywoluje akcje pola typu TlenField::Button
		 */
		void clicked();
	
		/**
		 * @return true jesli jest pusty
		 */
		bool isNull() const;

		TlenXmlNode toXml() const;
		void fromXml(const TlenXmlNode &node);
		
		bool isReadOnly() const;
		void setReadOnly(bool value=true);
		bool isPressed() const;
		void setPressed(bool pressed=true);
		QByteArray getImgData() const;
		void setImgData(const QByteArray &);
		QDate getDate() const;
		void setDate(const QDate &date);
		QStringList getDepends() const;
		
		void setValidator(const QString &validator);
		QString getValidator() const;

		static TlenXmlNode toXml(const QList<TlenField> &fields);
		static QList<TlenField> fromXml(const QList<TlenField> &fields, const TlenXmlNode &node);		

	private:
		TlenFieldPrivate *d;
};



uint __tlen_data__ qHash(const TlenField &f);



















#endif
