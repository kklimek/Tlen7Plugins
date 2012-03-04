#ifndef CPP_TLEN_XML_NODE_H
#define CPP_TLEN_XML_NODE_H

#include <core/export.h>

#include <QList>
#include <QString>
#include <QByteArray>
#include <QDomElement>
#include <QDomDocument>

/**
 * \brief Klasa do obsługi XML
 */

class __tlen_xml__ TlenXmlNode
{
public:
	/**
	 * Tworzy wezel o podanej nazwie, opcjonalnie jako dziecko podanego wezla
	 * @param name    nazwa wezla. Jesli nazwa jest pusta, tworzony jest pusty wezel
	 * @param nsUri   przestrzen nazw noda
	 * @param parent  opcjonalny rodzic
	 */
	TlenXmlNode(const QString &name = QString(), const QString &nsUri = QString(), TlenXmlNode *parent = 0);
	~TlenXmlNode();

	/**
	 * @return  nazwa dziecka
	 */
	QString name() const;

	/**
	 * @param - ident ilosc spacji uzywanych do wciec, -1 = zadnych bialych znakow, 0 = zadnych wciec ale wstawiane sa znaki nowej linii
	 * @return  string opisujacy strukture XML-a
	 */
	QString toString(int ident = -1) const;

	/**
	 * @param - ident ilosc spacji uzywanych do wciec, -1 = zadnych bialych znakow, 0 = zadnych wciec ale wstawiane sa znaki nowej linii
	 * @return QByteArray opisujacy strukture XML-a
	 */
	QByteArray toByteArray(int ident = -1) const;

	/**
	 * Wstawia dane do node np. Node \e <xmlnode/> po wykonaniu na nim operacji insertData("data") będzie wyglądał następująco: \e {<xmlnode>data</xmlnode>}
	 * @param data - wstawiane dane
	 * \sa getData(), hasData()
	 */
	void insertData(const QString &data);

	/**
	 * @return dane z node
	 * \sa insertData(), hasData()
	 */
	QString getData() const;

	/**
	 * Sprawdza czy node zawiera jakieś dane
	 * @return true jeśli node zawiera jakieś dane
	 * \sa getData(), insertData()
	 */
	bool hasData() const;


	/**
	 * Tworzy i zwraca nowe dziecko o podanej nazwie
	 * @param  name    nazwa dziecka
	 * @param  nsUri   przestrzen nazw dziecka
	 * @return  nowoutworzone dziecko
	 * \sa getChild(), hasChildNodes(), getChildNodes()
	 */
	TlenXmlNode addChild(const QString &name, const QString &nsUri = QString());

	/**
	 * Dodaje dziecko
	 * @param child - dodawane dziecko
	 */
	void appendChild(const TlenXmlNode &node);

	/**
	 * Metoda sluzaca do sprawdzania czy wezel jest pusty
	 * @return true jesli wezel jest pusty
	 */
	bool isNull() const;

	/**
	 * Sprawdza czy node jest rootem dokumentu
	 * @return true jeśli node jest rootem dokumentu
	 */
	bool isRoot() const;

	/**
	 * Zwraca dziecko o podanej sciezce. Elementy sciezki rozdzielamy znakiem /\n
	 * Np. dla XML-a:
	 * \code
	 * <a>
	 * 	<b>
	 * 		<c/>
	 * 	</b>
	 * </a>
	 * \endcode
	 * Wywolanie getChild("b/c"), na wezle 'a' zwroci wezel 'c'
	 * @param  childPath     sciezka dziecka ktore chcemy wyciagnac
	 * @return  wezel XML, pusty jesli nie znaleziono dziecka
	 * \sa addChild(), hasChildNodes(), getChildNodes()
	 */
	TlenXmlNode getChild(const QString &childPath) const;

	/**
	 * Sprawdza czy node ma podany atrybut
	 * @param name - nazwa atrybutu
	 * \sa setAttribute(), getAttribute()
	 */
	bool hasAttribute(const QString &name, const QString &nsUri = QString()) const;

	/**
	 * Ustawia atrybut
	 * @param name - nazwa atrybutu
	 * @param value - wartosc atrybutu
	 * \sa hasAttribute(), getAttribute()
	 */
	void setAttribute(const QString &name, const QString &value, const QString &nsUri = QString());

	void setAttribute(const QString &name, int, const QString &nsUri = QString());

	void setAttribute(const QString &name, unsigned, const QString &nsUri = QString());

	void setAttribute(const QString &name, double, const QString &nsUri = QString());
	
	void setAttribute(const QString &name, qint64, const QString &nsUri = QString());
	
	/**
	 * Pobiera atrybut
	 * @param name   nazwa atrybutu
	 * @return wartosc atrybutu lub null string jesli atrybut jest nieobecny
	 * \sa hasAttribute(), setAttribute()
	 */
	QString getAttribute(const QString &name, const QString &nsUri = QString()) const;

	/**
	 * Sprawdza czy node ma dzieci
	 * @return true jeśli node ma jedno lub wiecęj dzieci
	 * \sa addChild(), getChild(), getChildNodes()
	 */
	bool hasChildNodes() const;

	/**
	 * Pobiera liste wszystkich dzieci nodu
	 * @return wektor dzieci
	 * \sa addChild(), getChild(), getChildNodes()
	 */
	QList<TlenXmlNode> getChildNodes() const;

	/**
	 * Ustala tresc noda na data
	 * @param data - "tresc" noda
	 * @return true jesli wszystkie nody sa poprawnie zamkniete
	 * nawet jesli metoda zwroci false, bedzie mozna pobierac nazwe i parametry niezamknietego noda (np node otwierajacy sesje <s i="xxxxxx">)
	 * \sa setContent(const QString &)
	 */
	bool setContent(const QByteArray &data);

	/**
	 * Ustala tresc noda na data
	 * @param data - "tresc" noda
	 * @return true jesli wszystkie nody sa poprawnie zamkniete
	 * nawet jesli metoda zwroci false, bedzie mozna pobierac nazwe i parametry niezamknietego noda (np node otwierajacy sesje <s i="xxxxxx">)
	 * \sa setContent(const QByteArray &)
	 */
	bool setContent(const QString &data);
	
	/**
	 * @return prefiks dziecka
	 */
	QString prefix() const;
	
	/**
	 * Ustala prefiks noda na prefix
	 * @param prefix - prefiks noda
	 */
	void setPrefix(const QString &prefix);
	
	QString namespaceUri() const;

	bool operator==(const TlenXmlNode &) const;

private:
	// Szuka wezla na podstawie sciezki okreslonej przez liste stringow
	// @param parts   sciezka do wezla
	// @return wezel o podanej scieze, lub pusty jesli nie znaleziono
	TlenXmlNode getChild(QStringList &parts) const;

	QDomElement element;
	QDomDocument document;
};

#endif
