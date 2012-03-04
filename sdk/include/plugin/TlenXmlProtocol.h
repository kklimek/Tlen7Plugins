#ifndef __TLEN_XML_PROTOCOL_H__
#define __TLEN_XML_PROTOCOL_H__

#include <QHash>

#include <plugin/TlenProtocol.h>

class TlenAccountConnection;
class QXmlStreamReader;

/**
 * \brief Klasa bazowa dla protokołów bazujących na strumieniu XML.
 *
 * Jeśli chcemy zaimplementować protokół bazujący na strumieniu XML najwygodniejszym sposobem jest wykorzystanie tej klasy. 
 * Klasa ma cztery metody, które TRZEBA reimplementować:
 *  - onNode
 *  - onRootOpen
 *  - onRootClose
 *  - onError
 *  \n
 *
 *  Metoda onRootOpen jest wywoływana przy napotkaniu pierwszego node XML.\n
 *  Metoda onNode jest wywołtwana przy napotkaniu każdego kolejnego node XML.\n
 *  Metoda onRootClose jest wywoływana przy zamknięciu pierwszego node XML.\n\n
 *  Przykład:\n
 *  Następujący dokument XML:
 *  \code
 *  <xmlroot>
 *  	<xmlchild1>
 *  		<xmlchild2/>
 *  	</xmlchild1>
 *  </xmlroot>
 *  \endcode
 *  spowoduje:
 *   -# onRootOpen z TlenXmlNode <xmlroot>
 *   -# onNode z TlenXmlNode <xmlchild1><xmlchild2/><xmlchild1/>
 *   -# onRootClose z TlenXmlNode <xmlroot/>
 */
class __tlen_plugin__ TlenXmlProtocol: public TlenProtocol
{
	public:
		/**
		 * \brief Opisuje błąd parsowania XML
		 */
		enum Error {
			UnexpectedElementError,		/**< Nieoczekiwany element w drzewie xml */
			XmlNotWellFormedError		/**< Zle uformowany xml, czyli np jakis node zamyka sie za nodem rodzicem itd */
		};

		TlenXmlProtocol(bool namespaceprocessing = true);
		~TlenXmlProtocol();
		/**
		 * Metoda zaimplementowana na potrzeby protokołu bazującego na strumieniu XML. Nie należy jej reimplementować, inaczej metody onRootOpen, onNode, onRootClose i onError nie zostaną wywołane
		 */

		void socketReadyRead(TlenAccountConnection *acc, const QByteArray &data);

		TLEN_DECLARE_SLOT(xmlProtocolOnNode);

	protected:
		void reset(TlenAccountConnection *acc);
	
		/**
		 * Otwiera nowy stream w protokole. Nastepny odebrany node zostanie przekazany do onRootOpen, a nie onXmlNode.
		 */
	
		void writeRootOpen(TlenAccountConnection *, const TlenXmlNode &node);
		void writeDTD(TlenAccountConnection *, const QByteArray &version = "1.0", const QByteArray &encoding = "UTF-8");
		
		/**
		 * Metoda reaguje na node w roocie dokumentu
		 * np. jesli przyjdzie node <a><b><tekst></b></a> to zostanie przekazany w calosci do metody
		 * @param node - node xml
		 * @param acc - konto ktore otrzymalo noda
		 */
		virtual void onNode(const TlenXmlNode &node, TlenAccountConnection *acc) = 0;
		
		/**
		 * Metoda reagujaca na pierwszy otwierajacy node w strumieniu
		 * @param node - node xml
		 * @param acc - konto ktore otrzymalo noda
		 */
		virtual void onRootOpen(const TlenXmlNode &node, TlenAccountConnection *acc) = 0;
		
		/**
		 * Metoda reaguje na zakonczenie dokumentu, bedzie to zamkniecie noda ktory przyszedl w onRootOpen
		 * @param node - node xml
		 * @param acc - konto ktore otrzymalo noda
		 */
		virtual void onRootClose(const TlenXmlNode &node, TlenAccountConnection *acc) = 0;

		/**
		 * Metoda reaguje na blad w parsowaniu xmla
		 * @param err - blad
		 * @param acc - konto ktore napotkalo blad
		 */
		virtual void onError(TlenXmlProtocol::Error err, TlenAccountConnection *acc) = 0;

	private:
		void getWholeNode(QXmlStreamReader *, TlenAccountConnection *);
		QHash<TlenAccountConnection *, bool> documentStarted;

		QHash<TlenAccountConnection *, QXmlStreamReader *> readermap;
		QHash<TlenAccountConnection *, QString> rootmap;
		QHash<TlenAccountConnection *, QString> nodemap;
		
		QHash<TlenAccountConnection *, TlenXmlNode> wholeNode;
		QHash<TlenAccountConnection *, QList<TlenXmlNode> > nodeLevel;
	
		bool xmlprocessing;
};



#endif

