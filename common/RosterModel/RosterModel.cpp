#include <QDebug>

#include <roster/TlenRoster.h>

#include "RosterModel.h"

RosterModel::RosterModel(QObject *parent)
	: QAbstractItemModel(parent)
	, m_roster(TlenRoster::getInstance())
{
	QStringList grps = m_roster->getGroupsNames();

	foreach(const QString &grp, grps)
	{
		TlenBuddyGroup bgroup = m_roster->addGroup(grp);
		m_buddies << bgroup;
	}
}

QModelIndex RosterModel::index(int row, int column, const QModelIndex &parent) const
{
	QModelIndex retval;

	if(column == 0)
	{
		if(parent.isValid())
		{
			if(m_buddyhash.contains(parent.internalId()))
			{
				TlenBuddy bparent = m_buddyhash[parent.internalId()];

				switch(bparent.getType())
				{
					case TlenBuddy::Group:
					{
						TlenBuddyGroup grp(bparent);

						if(grp.isValid())
						{
							if(row < grp.childCount())
							{
								TlenBuddy child = grp.buddyAt(row);
								uint id = qHash(child);
								m_buddyhash[id] = child;
								retval = createIndex(row, column, id);
							}
						}

						break;
					}

					case TlenBuddy::Meta:
					{
						TlenBuddyMeta meta(bparent);

						if(meta.isValid())
						{
							if(row < meta.childCount())
							{
								TlenBuddy child = meta.getBuddies()[row];
								uint id = qHash(child);
								m_buddyhash[id] = child;
								retval = createIndex(row, column, id);
							}
						}

						break;
					}

					case TlenBuddy::Contact:
					case TlenBuddy::Temporary:
					case TlenBuddy::Invalid:
					case TlenBuddy::Custom:
						break;
				}
			}
		}
		else if(row < m_buddies.size())
		{
			uint id = qHash(m_buddies[row]);
			m_buddyhash[id] = m_buddies[row];
			retval = createIndex(row, column, id);
		}
	}

	return retval;
}

QModelIndex RosterModel::parent(const QModelIndex &child) const
{
	QModelIndex retval;

	if(child.isValid() && m_buddyhash.contains(child.internalId()))
	{
		TlenBuddy b = m_buddyhash[child.internalId()];

		switch(b.getType())
		{
			case TlenBuddy::Group:
				break;

			case TlenBuddy::Meta:
			{
				TlenBuddyMeta meta(b);

				if(meta.isValid())
					retval = createIndex(meta.getGroup());

				break;
			}

			case TlenBuddy::Contact:
			{
				TlenBuddyContact c(b);

				if(c.isValid())
					retval = createIndex(c.getParent());

				break;
			}

			case TlenBuddy::Temporary:
			{
				TlenBuddyTemporary t(b);

				if(t.isValid())
					retval = createIndex(t.getGroup());
				break;
			}

			case TlenBuddy::Custom:
			{
				TlenBuddyCustom custom(b);

				if(custom.isValid())
					retval = createIndex(custom.getParent());
				break;
			}

			case TlenBuddy::Invalid:
				break;
		}
	}

	return retval;
}

int RosterModel::rowCount(const QModelIndex &parent) const
{
	int retval = 0;

	QStringList grps = m_roster->getGroupsNames();

	if( parent.isValid() )
	{
		uint id = parent.internalId();

		if(m_buddyhash.contains(id))
		{
			TlenBuddy b = m_buddyhash[id];

			switch(b.getType())
			{
				case TlenBuddy::Group:
				{
					TlenBuddyGroup grp(b);
					if(grp.isValid())
						retval = grp.childCount();
					break;
				}

				case TlenBuddy::Meta:
				{
					TlenBuddyMeta meta(b);

					if(meta.isValid())
						retval = meta.childCount();
					break;
				}

				case TlenBuddy::Contact:
				case TlenBuddy::Temporary:
				case TlenBuddy::Custom:
				case TlenBuddy::Invalid:
					break;
			}
		}
	}
	else
	{
		qDebug() << Q_FUNC_INFO << grps;

		retval = grps.size();
	}

	return retval;
}

int RosterModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 1;
}

QVariant RosterModel::data(const QModelIndex &index, int role) const
{
	QVariant retval;

	QStringList grps = m_roster->getGroupsNames();

	if(index.isValid() && index.column() == 0 && m_buddyhash.contains(index.internalId()))
	{
		TlenBuddy b = m_buddyhash[index.internalId()];

		if(b.isValid())
		{
			switch(role)
			{
				case Qt::DisplayRole:
					retval = b.getDisplay();
					break;
			}
		}
	}

	return retval;
}

QModelIndex RosterModel::createIndex(const TlenBuddy &buddy) const
{
	QModelIndex retval;

	if(buddy.isValid())
	{
		switch(buddy.getType())
		{
			case TlenBuddy::Group:
				retval = createIndex(TlenBuddyGroup(buddy));
				break;

			case TlenBuddy::Meta:
				retval = createIndex(TlenBuddyMeta(buddy));
				break;

			case TlenBuddy::Contact:
				Q_ASSERT(false);
				//retval = createIndex(TlenBuddyContact(buddy));
				break;

			case TlenBuddy::Temporary:
				Q_ASSERT(false);
				//retval = createIndex(TlenBuddyTemporary(buddy));
				break;

			case TlenBuddy::Custom:
				Q_ASSERT(false);
				//retval = createIndex(TlenBuddyCustom(buddy));
				break;

			case TlenBuddy::Invalid:
				break;
		}
	}

	return retval;
}

QModelIndex RosterModel::createIndex(const TlenBuddyGroup &grp) const
{
	QModelIndex retval;

	if(grp.isValid())
	{
		int row = m_buddies.indexOf(grp);

		if(row > -1)
		{
			uint id = qHash(grp);
			m_buddyhash[id] = grp;
			retval = createIndex(row, 0, id);
		}
	}

	return retval;
}
