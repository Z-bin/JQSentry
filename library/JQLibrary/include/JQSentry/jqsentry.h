﻿#ifndef JQLIBRARY_INCLUDE_JQSENTRY_JQSENTRY_H_
#define JQLIBRARY_INCLUDE_JQSENTRY_JQSENTRY_H_

// C++ lib import
#include <functional>

// Qt lib import
#include <QObject>
#include <QPointer>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkProxy>

// JQLibrary lib import
#include <../JQDeclare>

class JQSentryTransit: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQSentryTransit )

public:
    JQSentryTransit() = default;

    ~JQSentryTransit() = default;

public slots:
    void transit(const std::function<void()> &callback);
};

class JQLIBRARY_EXPORT JQSentry: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQSentry )

    JQSentry() = default;

public:
    ~JQSentry() = default;

    static bool initialize(const QString &dsn);

    static void installMessageHandler(const int &acceptedType = QtWarningMsg | QtCriticalMsg);

    static bool serverReachable();


    static bool postLog(const QString &log, const QtMsgType &type = QtDebugMsg, const QMessageLogContext &context = { });

    static bool postMinidump(const QString &log, const QString &dumpFileName, const QByteArray &dumpFileData);


    inline static void setServerName(const QString &serverName);

    inline static void setUserId(const QString &userId);

    inline static void setUserName(const QString &userName);

    inline static void setRelease(const QString &release);

    inline static void setLoggerName(const QString &loggerName);

private:
    static void handleReply(QNetworkReply *reply);

    static QString getLogLevel(const QtMsgType &type);

    static QJsonObject sentryData();

    static QByteArray xSentryAuth();

private:
    static QSharedPointer< QNetworkAccessManager > networkAccessManager_;
    static QPointer< JQSentryTransit > transit_;
    static bool continueFlag_;

    static QString clientName_;
    static QString clientVersion_;

    static QString dsn_;
    static QString protocol_;
    static QString publicKey_;
    static QString host_;
    static quint16 port_;
    static QString path_;
    static QString projectId_;

    static QString serverName_;
    static QString userId_;
    static QString userName_;
    static QString userIpAddress_;
    static QString release_;
};

// .inc include
#include "jqsentry.inc"

#endif//JQLIBRARY_INCLUDE_JQSENTRY_JQSENTRY_H_
