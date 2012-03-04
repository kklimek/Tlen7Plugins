#ifndef __TLEN_BUDDY_RESOURCE_H__
#define __TLEN_BUDDY_RESOURCE_H__

#include <QString>

#include <core/export.h>
#include <data/TlenPresence.h>

class __tlen_data__ TlenBuddyResourceType
{
	private:
		TlenBuddyResourceType(const QString &name, const QString &icopath = QString());
		QString name;
		QString icon;
		friend class TlenProtocol;
		friend class TlenBuddyResource;
};

class __tlen_data__ TlenBuddyResource
{
	public:
		TlenBuddyResource();
		QString getName() const;
		QString getIcon() const;
		int getPriority() const;
		TlenPresence getPresence() const;
		bool isValid() const;
		bool operator==(const TlenBuddyResource &) const;

	private:
		TlenBuddyResource(TlenBuddyResourceType *, const TlenPresence &);
		TlenBuddyResourceType *type;
		TlenPresence presence;
		friend class TlenRoster;
		friend class TlenProtocol;		
};

#endif

