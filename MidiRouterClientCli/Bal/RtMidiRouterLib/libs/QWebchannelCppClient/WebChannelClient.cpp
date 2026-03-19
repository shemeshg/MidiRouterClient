#include "WebChannelClient.h"

#include <qwebsocket.h>
#include <qjsondocument.h>
#include <qeventloop.h>
#include <qtimer.h>

enum QWebChannelMessageTypes
{
	mtSignal = 1,    //信号通知
	mtPropertyUpdate = 2,   //不使用
	mtInit = 3,     //初始化
	mtIdle = 4,     //客户端正常通告
	mtDebug = 5,    //不使用
	mtInvokeMethod = 6, //函数调用
	mtConnectToSignal = 7,  //信号连接
	mtDisconnectFromSignal = 8, //断开信号连接
	setProperty = 9,    //不使用
	mtResponse = 10,    //服务器对请求的响应
};

CWebChannelClient::CWebChannelClient(QWebSocket* socket):m_socket(socket), m_ID(0) {}

void CWebChannelClient::initialize()
{
	QObject::connect(m_socket, &QWebSocket::textMessageReceived, this, &CWebChannelClient::handleReceivedMessage);

	auto response = invoke(
		{ {"type", mtInit},
		{ "id", m_ID } });

	QObject::connect(response, &CWebChannelResponse::result, this, [=](const QJsonValue& message)
		{
			//qDebug() << message;
			const auto data = message.toObject();
			for (auto itr = data.begin(); itr != data.end(); ++itr)
			{
				const QString objectName = itr.key();
				const QJsonObject object = itr->toObject();

				auto& webChannelObj = m_objects[objectName];

                for (const auto method : object["methods"].toArray())
				{
                    const auto& descrip = method.toArray();

					webChannelObj.Methods[descrip[0].toString()] = descrip[1].toInt();
				}

                for (const auto signal : object["signals"].toArray())
				{
                    const auto& descrip = signal.toArray();
					const auto signalID = descrip[1].toInt();
					const auto signalName = descrip[0].toString();
					webChannelObj.Signals[signalName] = signalID;

					webChannelObj.Connections[signalID] = QPointer<CWebChannelConnection>(new CWebChannelConnection());

                    //this->disconnect(objectName, signalName);

				}
			}

			this->invoke({ {"type", mtIdle} }, false);

			emit this->initialized();
		});
}


QPointer<CWebChannelResponse> CWebChannelClient::invokeMethod(const QString& object, const QString& method, const QJsonArray& args)
{
	QPointer<CWebChannelResponse> response;
	do
	{
		if (m_objects.find(object) == m_objects.end()) break;
		if (m_objects[object].Methods.find(method) == m_objects[object].Methods.end()) break;

		response = invoke({
			{"type", mtInvokeMethod},
			{"object", object},
			{"method", m_objects[object].Methods[method]},
			{"args", args},
			{"id", m_ID}
			});

	} while (0);

	return response;
}


QJsonValue CWebChannelClient::invokeMethodBlocking(const QString& object, const QString& method, const QJsonArray& args, int msecs)
{
	QJsonValue rtVal;

	auto response = invokeMethod(object, method, args);
	if (response == nullptr) return rtVal;
	
	QEventLoop responseLoop;
	QObject::connect(response, &CWebChannelResponse::result, &responseLoop,//注意变量的存活期
		[&rtVal, &responseLoop](const QJsonValue& obj)
		{
			rtVal = obj;
			responseLoop.quit();
		});
	QTimer::singleShot(msecs, &responseLoop, &QEventLoop::quit);
	responseLoop.exec();

	return rtVal;
}

QPointer<CWebChannelConnection> CWebChannelClient::connect(const QString object, const QString& signal)
{
	QPointer<CWebChannelConnection> connection;

	do
	{
		if (m_objects.find(object) == m_objects.end()) break;
		if (m_objects[object].Signals.find(signal) == m_objects[object].Signals.end()) break;

		const int signalID = m_objects[object].Signals[signal];

		invoke(
			{
				{"type", mtConnectToSignal},
				{"object", object},
				{"signal", signalID}
			}, false);

		connection = m_objects[object].Connections[signalID];

	} while (0);

	return connection;
}

void CWebChannelClient::disconnect(const QString object, const QString& signal)
{
	if (m_objects.find(object) == m_objects.end()) return;
	if (m_objects[object].Signals.find(signal) == m_objects[object].Signals.end()) return;

	const int signalID = m_objects[object].Signals[signal];

	invoke({
		{"type", mtDisconnectFromSignal},
		{"object", object},
		{"signal", signalID}
		}, false);

	m_objects[object].Connections[signalID]->disconnect();
}

void CWebChannelClient::invokeNoResponseMethod(const QString &object,
                                               const QString &method,
                                               const QJsonArray &args)
{
    if (m_objects.find(object) == m_objects.end())
        return;
    if (m_objects[object].Methods.find(method) == m_objects[object].Methods.end())
        return;

    invoke({{"type", mtInvokeMethod},
            {"object", object},
            {"method", m_objects[object].Methods[method]},
            {"args", args},
            {"id", m_ID}},
           false);
}

void CWebChannelClient::handleReceivedMessage(const QString& text)
{
	QJsonObject obj;
	QJsonParseError error;
	QJsonDocument message = QJsonDocument::fromJson(text.toUtf8(), &error);
	if (error.error) {
		return;
	}
	else if (!message.isObject()) {
		return;
	}

	obj = message.object();

	int type = obj["type"].toInt();
	if (type == mtResponse)
	{
		int id = obj["id"].toInt();
		auto itr = m_replys.find(id);
		if (itr != m_replys.end())
		{
			emit itr->second->result(obj["data"]);
			itr->second->disconnect();
			delete itr->second;
			m_replys.erase(itr);
		}
	}
	else if (type == mtSignal)
	{
		const int signal = obj["signal"].toInt();

		const QString object = obj["object"].toString();
		auto connection = m_objects[object].Connections[signal];

		emit connection->signal(obj["args"].toArray());
	}
}

QPointer<CWebChannelResponse> CWebChannelClient::invoke(const QJsonObject& request, bool isResponse)
{
	QPointer<CWebChannelResponse> response;

	QString text = QJsonDocument(request).toJson();
	m_socket->sendTextMessage(text);

	if (isResponse)
	{
		response = QPointer<CWebChannelResponse>(new CWebChannelResponse);
		m_replys[m_ID] = response;

		if (m_ID == INT_MAX)
		{
			m_ID = 0;
		}
		else
		{
			m_ID++;
		}

	}

	return response;
}
