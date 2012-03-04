#ifndef _TLEN_ARG_H_
#define _TLEN_ARG_H_

#include <QString>
#include <QByteArray>
#include <QStringList>
#include <QMetaType>

#include <core/export.h>
#include <data/TlenBuddyResource.h>
#include <data/TlenTextFormat.h>

class TlenField;
class TlenXmlNode;
class TlenBuddy;
class TlenAccountConnection;
class TlenPlugin;
class TlenArgPrivate;
class TlenPluginAction;
class TlenPresence;
class TlenArg;
class TlenService;


/**
 * \brief Służy do przechowywania danych różnego typu
 *
 * Za pomocą TlenArg w programie przekazywane sa dane różnego typu. Jest to podstawowy typ używany m.in. w systemie sygnalów i slotów.
 */
class __tlen_data__ TlenArg
{
	public:
		/**
		 * \brief określa typ TlenArg
		 *
		 * Do TlenArg danego typu test można przypisać tylko TlenArg tego samego typu. Wyjątkiem jest TlenArg::None, do którego można przypisać dowolny TlenArg.\n
		 * Próba wyciągnięcia wartości innego typu niż określa to TlenArg::Type program zostaje przerwany.
		 * \sa getType()
		 */
		enum Type {
			None,			/**< Nie przechowuje żadnych danych. Do TlenArg typu None mozna przypisać TlenArg dowolnego typu. */
			Char,			/**< Przechowywany typ: char */
			UChar,			/**< Przechowywany typ: unsigned char */
			Int,			/**< Przechowywany typ: int */
			UInt,			/**< Przechowywany typ: unsigned int */
			Int64,		/**< Przechowywany typ: long long */
			UInt64,		/**< Przechowywany typ: unsigned long long */
			Float,			/**< Przechowywany typ: float */
			Double,			/**< Przechowywany typ: double */
			String,			/**< Przechowywany typ: QString */
			ByteArray,		/**< Przechowywany typ: QByteArray */
			StringList,		/**< Przechowywany typ: QStringList */
			Bool,			/**< Przechowywany typ: bool */
			Pointer,		/**< Przechowywany typ: void * */
			PointerList,	/**< Przechowywany typ: QList<void *> */
			Plugin,			/**< Przechowywany typ: TlenPlugin * */
			Field,			/**< Przechowywany typ: TlenField */
			FieldList,		/**< Przechowywany typ: QList<TlenField> */
			XmlNode,		/**< Przechowywany typ: TlenXmlNode */
			Buddy,			/**< Przechowywany typ: TlenBuddy */
			BuddyResource,	/**< Przechowywany typ: TlenBuddyResrouce */
			Account,		/**< Przechowywany typ: TlenAccountConnection */
			PluginAction,	/**< Przechowywany typ: TlenPluginAction */
			Presence,		/**< Przechowywany typ: TlenPresence */
			ArgList,	
			Service,		/**< Przechowywany typ: TlenService */
			ServiceList,		/**< Przechowywany typ: QList<TlenService> */
			TextFormatList,
			Undefined		/**< Wykorzystywane przy rejestrowaniu sygnalow do okreslenia typu, ktore moze przechowywac rozne typy*/
		};

		/**
		 * Tworzy TlenArg typu TlenArg::None
		 */
		TlenArg();

		TlenArg(const TlenArg &);
		~TlenArg();

		/**
		 * Tworzy TlenArg typu TlenArg::Char
		 * @param data - przechowywane dane
		 * \sa toChar(), operator=(const char &)
		 */
		TlenArg(const char &data);

		/**
		 * Tworzy TlenArg typu TlenArg::UChar
		 * @param data - przechowywane dane
		 * \sa toUChar(), operator=(const unsigned char &)
		 */
		TlenArg(const unsigned char &data);

		/**
		 * Tworzy TlenArg typu TlenArg::ByteArray
		 * @param data - przechowywane dane
		 * \sa toByteArray(), operator=(const QByteArray &)
		 */
		TlenArg(const QByteArray &data);
	
		/**
		 * Tworzy TlenArg typu TlenArg::Int
		 * @param data - przechowywane dane
		 * \sa toInt(), operator=(const int &)
		 */
		TlenArg(const int &data);

		TlenArg(const QList<TlenArg>& argsList);

		/**
		 * Tworzy TlenArg typu TlenArg::UInt
		 * @param data - przechowywane dane
		 * \sa toUInt(), operator=(const unsigned int &)
		 */
		TlenArg(const unsigned int &data);


		/**
		 * Tworzy TlenArg typu TlenArg::LongLong
		 * @param data - przechowywane dane
		 * \sa toLongLong(), operator=(const long long &);
		 */
		TlenArg(const qint64 &data);


		/**
		 * Tworzy TlenArg typu TlenArg::ULongLong
		 * @param data - przechowywane dane
		 * \sa toULongLong(), operator=(const unsigned long long &);
		 */
		TlenArg(const quint64 &data);

		/**
		 * Tworzy TlenArg typu TlenArg::Double
		 * @param data - przechowywane dane
		 * \sa toDouble(), operator=(const double &)
		 */
		TlenArg(const double &data);


		/**
		 * Tworzy TlenArg typu TlenArg::Float
		 * @param data - przechowywane dane
		 * \sa toFloat(), operator=(const float &)
		 */
		TlenArg(const float &data);

		/**
		 * Tworzy TlenArg typu TlenArg::String
		 * @param data - przechowywane dane
		 * \sa toString(), operator=(const QString &)
		 */
		TlenArg(const QString &data);

		/**
		 * Tworzy TlenArg typu TlenArg::StringList
		 * @param data - przechowywane dane
		 * \sa toStringList(), oprator=(const QStringList &)
		 */
		TlenArg(const QStringList &data);

		/**
		 * Tworzy TlenArg typu TlenArg::Bool
		 * @param data - przechowywane dane
		 * \sa toBool(), operator=(const bool &);
		 */
		TlenArg(const bool &data);

		/**
		 * Tworzy TlenArg typu TlenArg::Pointer
		 * @param data - przechowywane dane
		 * \sa toPointer(), operator=(void *)
		 */
		TlenArg(void *data);

		/**
		 * Tworzy TlenArg typu TlenArg::PointerList
		 * @param data - przechowywane dane
		 * \sa toPointerList(), operator=(const QList<void *> &)
		 */
		TlenArg(const QList<void *> &data);

		/**
		 * Tworzy TlenArg typu TlenArg::Field
		 * @param data - przechowywane dane
		 * \sa toField(), operator=(const TlenField &)
		 */
		TlenArg(const TlenField &data);

		/**
		 * Tworzy TlenArg typu TlenArg::FieldList
		 * @param data - przechowywane dane
		 * \sa toFieldList(), operator=(const QList<TlenField> &)
		 */
		TlenArg(const QList<TlenField> &data);

		/**
		 * Tworzy TlenArg typu TlenArg::XmlNode
		 * @param data - przechowywane dane
		 * \sa toXmlNode(), operator=(const TlenXmlNode &)
		 */
		TlenArg(const TlenXmlNode &data);

		/**
		 * Tworzy TlenArg typu TlenArg::Buddy
		 * @param data - przechowywane dane
		 * \sa toBuddy(), operator=(const TlenBuddy &)
		 */
		TlenArg(const TlenBuddy &data);


		/** Tworzy TlenArg typu TlenArg::BuddyResource
		 * @param data - przechowywane dane
		 * \sa toBuddyResource(), operator=(const TlenBuddyResource &)
		 */
		TlenArg(const TlenBuddyResource &data);
	
		/**
		 * Tworzy TlenArg typu TlenArg::Account
		 * @param data - przechowywane dane
		 * \sa toAccount(), operator=(TlenAccountConnection *)
		 */
		TlenArg(TlenAccountConnection *data);

		/**
		 * Tworzy TlenArg typu TlenArg::PluginAction
		 * @param data - przechowywane dane
		 * \sa toPluginAction(), operator=(const TlenPluginAction &)
		 */
		TlenArg(const TlenPluginAction &);

		/**
		 * Tworzy TlenArg typu TlenArg::Plugin
		 * @param data - przechowywane dane
		 * \sa toPlugin(), operator=(TlenPlugin *)
		 */
		TlenArg(TlenPlugin *data);

		/**
		 * Tworzy TlenArg typu TlenArg::Presence
		 * @param data - przechowywane dane
		 * \sa toPresence(), operator=(const TlenPresence &)
		 */
		TlenArg(const TlenPresence &data);

		/**
		 * Tworzy TlenArg typu TlenArg::Service
		 * @param data - przechowywane dane
		 * \sa toService(), operator=(const QList<void *> &)
		 */
		TlenArg(const TlenService &data);

		/**
		 * Tworzy TlenArg typu TlenArg::ServiceList
		 * @param data - przechowywane dane
		 * \sa toServiceList(), operator=(const QList<void *> &)
		 */
		TlenArg(const QList<TlenService> &data);

		/**
		 * Tworzy TlenArg typu TlenArg::TextFormatList
		 * @param data - przechowywane dane
		 * \sa toTextFormatList(), operator=(const QList<void *> &)
		 */
		TlenArg(const QList<TlenTextFormat> &data);

		/**
		 * @return typ TlenArg
		 * \sa TlenArg::Type
		 */
		TlenArg::Type getType() const;
		QString getTypeName() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::Char, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const char &), operator=(const char &)
		 */
		char toChar() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::UChar, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const unsigned char &), operator=(const unsigned char &)
		 */
		unsigned char toUChar() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::Int, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const int &), operator=(const int &)
		 */
		int toInt() const;
		
		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::UInt, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const unsigned int &), operator=(const unsigned int &)
		 */
		unsigned int toUInt() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::LongLong, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const long long &), operator=(const long long &)
		 */
		qint64 toInt64() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::ULongLong, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const unsigned long long &), operator=(const unsigned long long &)
		 */
		quint64 toUInt64() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::Double, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const double &), operator=(const double &)
		 */
		double toDouble() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::Float, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const float &), operator=(const float &)
		 */
		float toFloat() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::String, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const QString &), operator=(const QString &)
		 */
		QString toString() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::ByteArray, dzialanie programu zostaje przerwane
		 * @return przechowywane dane
		 * \sa TlenArg(const QByteArray &), operator=(const QByteArray &)
		 */
		QByteArray toByteArray() const;
	
	
		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::StringList, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const QStringList &), operator=(const QStringList &)
		 */
		QStringList toStringList() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::Bool, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const bool &), operator=(const bool &)
		 */
		bool toBool() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::Pointer, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(void *), operator=(void *)
		 */
		void *toPointer() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::PointerList, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const QList<void *> &), operator=(const QList<void *> &)
		 */
		QList<void *> toPointerList() const;


		QList<TlenArg> toArgList() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::Field, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const TlenField &), operator=(const TlenField &)
		 */
		TlenField toField() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::FieldList, metoda ta asertuje
		 * @return przechowywane dane
		 * \sa TlenArg(const QList<TlenField> &), operator=(const QList<TlenField> &)
		 */
		QList<TlenField> toFieldList() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::XmlNode, program zostaje przerwany
		 * @return przechowywane dane
		 * \sa TlenArg(const TlenXmlNode &), operator=(const TlenXmlNode &)
		 */
		TlenXmlNode toXmlNode() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::Buddy, program zostaje przerwany
		 * @return przechowywane dane
		 * \sa TlenArg(const TlenBuddy &), operator=(const TlenBuddy &)
		 */
		TlenBuddy toBuddy() const;

		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::BuddyResource, program zostaje przerwany
		 * @return przechowywane dane
		 * \sa TlenArg(const TlenBuddyResource &), operator=(const TlenBuddyResource &)
		 */
		TlenBuddyResource toBuddyResource() const;
	
		/**
		 * Jeśli TlenArg ma inny typ niż TlenArg::Account, program zostaje przerwany
		 * @return przechowywane dane
		 * \sa TlenArg(TlenAccountConnection *), operator=(TlenAccountConnection *)
		 */
		TlenAccountConnection *toAccount() const;

		/**
		 * Jeśli TlenArg ma innt typ niż TlenArg::PluginAction, program zostaje przerwany
		 * @return przechowywane dane
		 * \sa TlenArg(const TlenPluginAction &), operator=(const TlenPluginAction &)
		 */
		TlenPluginAction toPluginAction() const;

		/**
		 * Jeśli TlenArg ma innt typ niż TlenArg::Plugin, program zostaje przerwany
		 * @return przechowywane dane
		 * \sa TlenArg(TlenPlugin *), operator=(TlenPlugin *)
		 */
		TlenPlugin *toPlugin() const;
		
		/**
		 * Jeśli TlenArg ma innt typ niż TlenArg::Presence, program zostaje przerwany
		 * @return przechowywane dane
		 * \sa TlenArg(const TlenPresence &), operator=(const TlenPresence &)
		 */		
		TlenPresence toPresence() const;

		/**
		 * Jeśli TlenArg ma innt typ niż TlenArg::Service, program zostaje przerwany
		 * @return przechowywane dane
		 * \sa TlenArg(const TlenService &), operator=(const TlenService &)
		 */		
		TlenService toService() const;

		/**
		 * Jeśli TlenArg ma innt typ niż TlenArg::ServiceList, program zostaje przerwany
		 * @return przechowywane dane
		 * \sa TlenArg(const QList<TlenService> &), operator=(const QList<TlenService> &)
		 */		
		QList<TlenService> toServiceList() const;

		/**
		 * Jeśli TlenArg ma innt typ niż TlenArg::TextFormatList, program zostaje przerwany
		 * @return przechowywane dane
		 * \sa TlenArg(const QList<TlenTextFormat> &), operator=(const QList<TlenTextFormat> &)
		 */		
		QList<TlenTextFormat> toTextFormatList() const;


		/**
		 * Porównuje dwa TlenArg.\n
		 * Dwa TlenArg są identyczne jeśli:
		 *  - mają ten sam typ
		 *  - przechowują tą samą wartość
		 * @param arg - TlenArg z którym porównujemy
		 * @return true jeśli są identyczne. Inaczej false
		 */
		bool operator==(const TlenArg &arg) const;

		bool operator!=(const TlenArg &arg) const;

		TlenArg operator=(const TlenArg &other);
	
		/**
		 * Przypisuje wartość TlenArg do pola\n
		 * Jeśli TlenArg przechowuje typ wartości inny niż obsługuje TlenField, metoda asertuje
		 * @param field - pole do którego przypisujemy
		 * @param val - wartość którą przypisujemy
		 * @return true jesli wartosc pola zostala zmieniona, false jesli wartosci sa identyczne
		 */
		static bool setFieldValue(TlenField &field, const TlenArg &val);

	private:
		TlenArgPrivate *d;
};

Q_DECLARE_METATYPE(TlenArg);



#endif // _TLEN_ARG_H_
