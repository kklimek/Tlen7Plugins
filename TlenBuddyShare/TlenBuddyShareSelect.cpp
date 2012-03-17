#include <QSortFilterProxyModel>

#include "TlenBuddyShareSelect.h"

class SelectedBuddiesProxyModel: public QSortFilterProxyModel
{
public:
	SelectedBuddiesProxyModel(QObject * parent = 0)
		: QSortFilterProxyModel(parent)
		, filterOut(false)
	{
	}

	void setFilterOut(bool fout)
	{
		if(fout != filterOut)
		{
			filterOut = fout;
			invalidate();
		}
	}

protected:
	bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
	{
		bool retval = false;

		QModelIndex idx = sourceModel()->index(source_row, 0, source_parent);

		if(idx.isValid())
		{
			retval = selected.contains(idx.internalId()) != filterOut;
		}

		return retval;
	}

private:
	bool filterOut;

	QHash<uint, QString> selected;
};


QList<TlenBuddy> TlenBuddyShareSelect::buddies()
{
	TlenBuddyShareSelect select;

	QList<TlenBuddy> retval;

	if(select.exec() == QDialog::Accepted)
		retval = retval;

	return retval;
}

TlenBuddyShareSelect::TlenBuddyShareSelect(QWidget *parent)
	: QDialog(parent)
	, m_listModel(new SelectedBuddiesProxyModel(this))
	, m_selectedModel(new SelectedBuddiesProxyModel(this))
{
	m_listModel->setFilterOut(true);
}
