#ifndef TLEN_UTIL_H
#define TLEN_UTIL_H

#include <QObject>
#include <QString>
#include <QCoreApplication>

#include <core/export.h>

class QIODevice;

/// Usypia biezacy watek na `milisec` milisekund (1ms = 1/1000sek)
// @param milisec   czas uspienia
__tlen_core__ void tlen_sleep(unsigned long milisec);

__tlen_core__ QString getArrayMd5(const QByteArray &byteArray);
__tlen_core__ QString getFileMd5(const QString &filepath);
__tlen_core__ QString getMd5FromDeviceData(QIODevice *device);

__tlen_core__ QString getArraySha1(const QByteArray &byteArray);
__tlen_core__ QString getFileSha1(const QString &filepath);
__tlen_core__ QString getSha1FromDeviceData(QIODevice *device);

__tlen_core__ QString formatSize(quint64 size);
__tlen_core__ QString formatTime(long sec);
__tlen_core__ QString versionToString(int version);

__tlen_core__ void codeData(QByteArray &data);
__tlen_core__ QString cutSection(const QString &style, const QString &name);

__tlen_core__ QString versionString();

__tlen_core__ void removeDir(const QString & path);

#define tlen_tr(text, comment) QCoreApplication::translate("translation", text, comment)

template<class T>
QString i2s(T i)
{
	return QString("%1").arg(i);
}









#endif
