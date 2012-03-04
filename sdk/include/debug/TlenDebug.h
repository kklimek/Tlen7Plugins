#ifndef __TLEN_DEBUG_H__
#define __TLEN_DEBUG_H__

#include <QDebug>
#include <QList>

#include <core/export.h>
#include <data/TlenArg.h>
#include <data/TlenBuddy.h>
#include <plugin/TlenXmlProtocol.h>
#include <xml/TlenXmlNode.h>

#ifdef TLEN_NO_DEBUG
#	define TlenDebug(module, stream)
#	define TlenDebug2(module)
#	define TlenError(module, stream)
#	define TlenWarning(module, stream)
#	define TlenMessage(module, stream)
#else
	
	#ifdef Q_OS_LINUX 
		#define TlenDebug(module, stream) qDebug()<<"DEBUG:\t["<<module<<"\t"<<__PRETTY_FUNCTION__<<":"<<__LINE__<<"]\t" << stream;
		#define TlenDebug2(module) qDebug()<<"DEBUG:\t["<<module<<"\t"<<__PRETTY_FUNCTION__<<":"<<__LINE__<<"]";
	#else
		#define TlenDebug(module, stream) qDebug()<<"DEBUG:\t["<<module<<"\t"<<__FILE__<<":"<<__LINE__<<"]\t" << stream;
		#define TlenDebug2(module) qDebug()<<"DEBUG:\t["<<module<<"\t"<<__FILE__<<":"<<__LINE__<<":"<<__LINE__<<"]";
	#endif
	
#	define TlenError(module, stream) qDebug()<<"ERROR:\t["<<module<<"\t"<<__FILE__<<":"<<__LINE__<<"]\t" << stream;
#	define TlenWarning(module, stream) qDebug()<<"WARNING:\t["<<module<<"\t"<<__FILE__<<":"<<__LINE__<<"]\t" << stream;
#	define TlenMessage(module, stream) qDebug()<<"MESSAGE:\t["<<module<<"\t"<<__FILE__<<":"<<__LINE__<<"]\t" << stream;
#endif


class TlenArchiveConversation;
class TlenArchiveConversationEntry;
class TlenPlugin;
class TlenProtocol;
class TlenAccountConnection;

/**
 * debugi archiwum
 */ 
__tlen_archive__ QDebug operator<<(QDebug dbg, const TlenArchiveConversation *conversation);
__tlen_archive__ QDebug operator<<(QDebug dbg, const TlenArchiveConversationEntry *entry);


/**
 * debugi data
 */

__tlen_data__ QDebug operator<<(QDebug dbg, TlenBuddy::Type);
__tlen_data__ QDebug operator<<(QDebug dbg, const TlenBuddy &buddy);
__tlen_data__ QDebug operator<<(QDebug dbg, const TlenBuddyContact &contat);
__tlen_data__ QDebug operator<<(QDebug dbg, const TlenBuddyGroup &group);
__tlen_data__ QDebug operator<<(QDebug dbg, const TlenBuddyCustom &custom);
__tlen_data__ QDebug operator<<(QDebug dbg, const TlenBuddyMeta &meta);
__tlen_data__ QDebug operator<<(QDebug dbg, const TlenBuddyTemporary &);
__tlen_data__ QDebug operator<<(QDebug dbg, const TlenArg &);
__tlen_data__ QDebug operator<<(QDebug dbg, TlenArg::Type);
__tlen_data__ QDebug operator<<(QDebug dbg, const QList<TlenField> &);
__tlen_data__ QDebug operator<<(QDebug dbg, const TlenField &);
__tlen_data__ QDebug operator<<(QDebug dbg, const TlenPresence &);
__tlen_data__ QDebug operator<<(QDebug dbg, const TlenService &);

/**
 * debugi protocol
 */
__tlen_plugin__ QDebug operator<<(QDebug dbg, TlenPlugin *);
__tlen_plugin__ QDebug operator<<(QDebug dbg, TlenProtocol *);
__tlen_plugin__ QDebug operator<<(QDebug dbg, TlenAccountConnection *);
__tlen_plugin__ QDebug operator<<(QDebug dbg, const TlenXmlProtocol::Error &);

/**
 * debugi xmla
 */
__tlen_xml__ QDebug operator<<(QDebug dbg, const TlenXmlNode &node);

/**
 * debugi network
 */

__tlen_network__ QDebug operator<<(QDebug dbg, TlenSocket::Error);

#endif

