#ifndef __TLEN_TEXT_FORMAT_H__
#define __TLEN_TEXT_FORMAT_H__


#include <core/export.h>

class __tlen_data__ TlenTextFormat
{
	public:	
	
	enum Type{
		Normal=0,
		Bold=1,
		Italic=2,
		Underline=4,		
	};
	
	TlenTextFormat() : color("#000000"), type(Normal)
	{
		
	}
	
	bool operator==(const TlenTextFormat &o) const
	{
		return start == o.start && end == o.end && color == o.color && fontSize == o.fontSize && font == o.font && type == o.type;
	}
	
	int start;
	int end;
	QString color;
	int fontSize;
	QString font;
	Type type;	
};


#endif

