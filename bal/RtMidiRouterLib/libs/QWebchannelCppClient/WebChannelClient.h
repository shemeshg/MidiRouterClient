#pragma once

#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qpointer.h>

#include <map>
using namespace std;

#include <qtimer.h>
#include <qeventloop.h>

template <typename Signal>
bool WaitForSignal(const typename QtPrivate::FunctionPointer<Signal>::Object* sender, Signal signal, int msecs = 5000)
{
	QEventLoop loop;
	bool timeout = false;
	QObject::connect(sender, signal, &loop, &QEventLoop::quit);
	QTimer::singleShot(msecs, &loop, [&loop, &timeout]() {
		timeout = true;
		loop.quit();
		});
	loop.exec();

	return !timeout;
}


class QWebSocket;

class CWebChannelResponse : public QObject
{
	Q_OBJECT

signals:
	void result(const QJsonValue& message);
};

class CWebChannelConnection : public QObject
{
	Q_OBJECT

signals:
	void signal(const QJsonArray& message);
};



class CWebChannelClient : public QObject
{
	Q_OBJECT
public:
	CWebChannelClient(QWebSocket* socket);

	void initialize();

	//º¯Êý
	QPointer<CWebChannelResponse> invokeMethod(const QString& object, const QString& method, const QJsonArray& args = {});
	QJsonValue invokeMethodBlocking(const QString& object, const QString& method, const QJsonArray& args = {}, int msecs = 5000);

	//ÐÅºÅ
	QPointer<CWebChannelConnection> connect(const QString object, const QString& signal);
	void disconnect(const QString object, const QString& signal);

	//ÊôÐÔ
	//void setProperty(const QString& object, const QString& propertyName, );

signals:
	void initialized();

private:
	void handleReceivedMessage(const QString& text);

	QPointer<CWebChannelResponse> invoke(const QJsonObject& request, bool isResponse = true);

	struct WebChannelObject
	{
		map<QString, int> Methods;
		map<QString, int> Signals;

		map<int, QPointer<CWebChannelConnection>> Connections;
	};

	QWebSocket* m_socket;

	map<QString, WebChannelObject> m_objects;

	map<int, QPointer<CWebChannelResponse>> m_replys;

	int m_ID;
};