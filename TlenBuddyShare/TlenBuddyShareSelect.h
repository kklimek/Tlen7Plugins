#ifndef TLENBUDDYSELECT_H
#define TLENBUDDYSELECT_H

#include <QDialog>

#include <data/TlenBuddy.h>

class SelectedBuddiesProxyModel;

class TlenBuddyShareSelect: public QDialog
{
Q_OBJECT

public:
	static QList<TlenBuddy> buddies();

protected:
	TlenBuddyShareSelect(QWidget * parent = 0);

private:
	SelectedBuddiesProxyModel * m_listModel;
	SelectedBuddiesProxyModel * m_selectedModel;
};

#endif
