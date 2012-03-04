#ifndef __TLEN_TRANSFER_STATUS_H__
#define __TLEN_TRANSFER_STATUS_H__

#include <core/export.h>

class __tlen_gui_transfers__ TlenTransferStatus
{	
	public:
	
	enum Type{
		WaitingForAcceptation,
		Rejected,
		Sending,
		Receiving,
		Aborted,
		Completed
	};
};


#endif

