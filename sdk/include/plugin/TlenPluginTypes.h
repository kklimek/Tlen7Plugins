#ifndef __TLEN_PLUGIN_TYPES_H__
#define __TLEN_PLUGIN_TYPES_H__

#include <QString>

class TlenPlugin;
template <class T>
class QList;
class TlenArg;

typedef void (TlenPlugin::*TlenPluginActionCallback)(QList<TlenArg> &);
typedef void (TlenPlugin::*TlenPluginSlot)(const QString &, QList<TlenArg> &);

#define TLEN_DECLARE_ACTION(action) void action(QList<TlenArg> &)
#define TLEN_DECLARE_SLOT(slot) void slot(const QString &senderId, QList<TlenArg>&)

#define TLEN_DEFINE_ACTION(classname, action) void classname::action(QList<TlenArg> &args)
#define TLEN_DEFINE_SLOT(classname, slot) void classname::slot(const QString &senderId, QList<TlenArg> &args)

#define TLEN_CALL_SLOT(owner, slot, sender, args) (owner->*slot)(sender, args)
#define TLEN_CALL_ACTION(owner, action, args) (owner->*action)(args)

#define TLEN_SLOT(ptr) (TlenPluginSlot)(&ptr)
#define TLEN_ACTION(ptr) (TlenPluginActionCallback)(&ptr)

#ifdef _WIN32
typedef struct HINSTANCE__*HINSTANCE;
typedef HINSTANCE LibraryHandle;
#else
typedef void* LibraryHandle;
#endif

#endif

