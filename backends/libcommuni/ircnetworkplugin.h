
#pragma once

#include "transport/config.h"
#include "transport/networkplugin.h"
#include "session.h"
#include <QtCore>
#include <QtNetwork>
#include "Swiften/EventLoop/Qt/QtEventLoop.h"
#include "ircnetworkplugin.h"


class IRCNetworkPlugin : public QObject, public NetworkPlugin {
	Q_OBJECT

	public:
		IRCNetworkPlugin(Config *config, Swift::QtEventLoop *loop, const std::string &host, int port);

		void handleLoginRequest(const std::string &user, const std::string &legacyName, const std::string &password);

		void handleLogoutRequest(const std::string &user, const std::string &legacyName);

		void handleMessageSendRequest(const std::string &user, const std::string &legacyName, const std::string &message, const std::string &/*xhtml*/, const std::string &/*id*/);

		void handleJoinRoomRequest(const std::string &user, const std::string &room, const std::string &nickname, const std::string &password);

		void handleLeaveRoomRequest(const std::string &user, const std::string &room);

		void handleRoomSubjectChangedRequest(const std::string &user, const std::string &room, const std::string &message);

		void tryNextServer();

	public slots:
		void readData();
		void sendData(const std::string &string);

	private:
		MyIrcSession *createSession(const std::string &user, const std::string &hostname, const std::string &nickname, const std::string &password, const std::string &suffix = "");
		std::string getSessionName(const std::string &user, const std::string &legacyName);
		std::string getTargetName(const std::string &legacyName);

	private:
		Config *config;
		QTcpSocket *m_socket;
		std::map<std::string, MyIrcSession *> m_sessions;
		std::vector<std::string> m_servers;
		int m_currentServer;
		std::string m_identify;
		bool m_firstPing;
};
