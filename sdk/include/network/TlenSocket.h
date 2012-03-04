#ifndef __TLEN_SOCKET_H__
#define __TLEN_SOCKET_H__

#include <QString>
#include <QByteArray>
#include <QSslCertificate>

#include <core/export.h>
#include <xml/TlenXmlNode.h>
#include <data/TlenArg.h>

class TlenSocketHelper;

/**
 * \brief Obsługa połączenia internetowego
 *
 * Należy napisać własną klasę dziedziczącą z TlenSocket i reimplementować chronione metody void TlenSocket::connected(), 
 * void TlenSocket::disconnected(), void TlenSocket::readyRead() i void TlenSocket::error(TlenSocket::Error) \n
 */
class __tlen_network__ TlenSocket
{
	friend class TlenSocketHelper;

	public:
		/**
		 * \brief określa jaki błąd wystąpił podczas operacji na sockecie
		 */
		enum Error {
			ConnectionRefused, /**< Połączenie zostało odrzucone. */
			RemoteHostClosed, /**< Zdalny host zamknął połączenie. */
			HostNotFound, /**< Adres hosta nie został znaleziony. */
			AccessError, /**< Operacja nie powiodła się ponieważ aplikacja nie ma odpowiednich uprawnień. */
			ResourceError, /**< System operacyjny wyczerpał wszystkie wolne zasoby (np. za dużo otwartych gniazd) */
			SocketTimeout, /**< Operacja na sockecie wyczerpała swój limit czasu */
			NetworkError, /**< Wystąpił błąd związany z połączeniem internetowym */
			ConnectionLost, /**< Połączenie po stronie klienta zostało zerwane */
			UnsupportedOperation, /**< Żądana operacja na gnieździe nie jest wspierana przez system operacyjny (np. brak wsparcia dla IPv6) */
			UnknownError /**< Wystąpił nieokreślony błąd */
		};

		enum SslError {
			NoError,
			UnableToGetIssuerCertificate,
			UnableToDecryptCertificateSignature,
			UnableToDecodeIssuerPublicKey,
			CertificateSignatureFailed,
			CertificateNotYetValid,
			CertificateExpired,
			InvalidNotBeforeField,
			InvalidNotAfterField,
			SelfSignedCertificate,
			SelfSignedCertificateInChain,
			UnableToGetLocalIssuerCertificate,
			UnableToVerifyFirstCertificate,
			CertificateRevoked,
			InvalidCaCertificate,
			PathLengthExceeded,
			InvalidPurpose,
			CertificateUntrusted,
			CertificateRejected,
			SubjectIssuerMismatch,
			AuthorityIssuerSerialNumberMismatch,
			NoPeerCertificate,
			HostNameMismatch,
			UnspecifiedError,
			NoSslSupport
		};
	
		enum SslProtocol {
			SslV3,
			SslV2,
			TlsV1,
			AnyProtocol
		};

		enum State {
			UnconnectedState,
			HostLookupState,
			ConnectingState,
			ConnectedState,
			BoundState,
			ClosingState,
			ListeningState
		};
	
		enum ProtocolType {
			Tcp,
			Udp
		};
		
		/**
		 * Domyślny konstruktor. Tworzenie socketa TCP
		 */
		TlenSocket();

		/**
		 * Ten konstruktor umożliwia wybór typ (TCP/UDP) tworzonego socketa.
		 * 
		 * \param protocolType
		 * Tcp lub Udp
		 */
		TlenSocket(ProtocolType protocolType);


		virtual ~TlenSocket();

		QByteArray readRawData(qint64 size = -1);

		/**
		 * otwiera połączenie
		 * @param address - adres serwera z którym chcemy nawiązać połączenie
		 * @param port - port na którym chcemy nawiązać połączenie
		 */
		void connectToHost(const QString &address, unsigned short port);
	
		/**
		 * otwiera połączenie szyfrowane.
		 */
		void connectToHostEncrypted(const QString &address, unsigned short port, SslProtocol = AnyProtocol);

		void startClientEncryption(SslProtocol = AnyProtocol);
	
		void ignoreSslError();
	
		void overridePeerName(const QString &peername);
	
		QString peerName() const;
	
		bool isEncrypted() const;
	
		QList<QSslCertificate> peerCertificateChain() const;
		QSslCertificate peerCertificate() const;
	
		void acceptCertificate();
	
		bool certificateAccepted() const;
	
		/**
		 * stan połączenia
		 */
		bool isConnectedToHost() const;
	
		State state() const;

		/**
		 * Zamyka połączenie o ile jest ono nawiązane, wcześniej zapisując
		 * dane które nie zostały jeszcze wysłane
		 */
		void disconnectFromHost();
		/**
		 * zrywa natychmiast połączenie
		 */
		void abort();
	
		/**
		 * wysyła dane
		 * @param data - dane do wysłania
		 * @param size - maksymalny rozmiar danych do zapisania (-1 aby zapisać cały ciąg)
		 * @return ilość zapisanych danych (zawsze size lub data.size() jeśli size jest równy -1)
		 */
		virtual void writeData(const QByteArray &data, qint64 size = -1);

		/**
		 * \overload
		 * wysyła node
		 * @param node - node do wysłania
		 */
		virtual void writeData(const TlenXmlNode &node);

		
		/**
		 * @return ostatni błąd jaki wystąpił przy operacji na sockecie
		 */
		TlenSocket::Error lastError() const;
	
		QList<TlenSocket::SslError> sslErrors() const;
		
	protected:
		/**
		 * Metoda wywoływana w momencie nawiązania połączenia. Należy ją reimplementować aby obsłużyć połączenie w spób jaki wymaga tego dany protokół.
		 */
		virtual void connected();

		/**
		 * Metoda wywoływana jest w momencie gdy połączenie zostanie zakończone.
		 */
		virtual void disconnected();

		/**
		 * Metoda wywoływana jest w momencie gdy wystąpi błąd operacji na gniździe.
		 * @param err - typ błędu jaki wystąpił
		 */
		virtual void error(TlenSocket::Error err);
	
		virtual void peerVerifyError(const QList<TlenSocket::SslError> &err);
	
		virtual void connectionEncrypted();
	
		/**
		 * Metoda wywoływana jest gdy wyłączony jest tryb blokujący i gdy w sockecie dostępne są dane do odczytu.
		 */
		virtual void readyRead();
		
	private:
		TlenSocketHelper* helper;
};









#endif
