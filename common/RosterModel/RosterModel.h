#ifndef __ROSTERMODEL_H
#define __ROSTERMODEL_H

#include <QAbstractItemModel>

#include <data/TlenBuddy.h>

class TlenRoster;
class TlenAccountConnection;

class RosterModel: public QAbstractItemModel
{
	Q_OBJECT

public:
	RosterModel(QObject * parent = 0);

	QModelIndex index(int row, int column, const QModelIndex &parent) const;
	QModelIndex parent(const QModelIndex &child) const;
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;

protected:
	using QAbstractItemModel::createIndex;
	QModelIndex createIndex(const TlenBuddyGroup &group) const;
	QModelIndex createIndex(const TlenBuddy &buddy) const;
	QModelIndex createIndex(const TlenBuddyContact &buddy) const;
	QModelIndex createIndex(const TlenBuddyTemporary &buddy) const;
	QModelIndex createIndex(const TlenBuddyCustom &buddy) const;

private:
	TlenRoster *m_roster;
	QList<TlenAccountConnection *> m_accounts;
	QList<TlenBuddyGroup> m_buddies;
	mutable QHash<uint, TlenBuddy> m_buddyhash;
};

#endif // __ROSTERMODEL_H
