#ifndef SETTING_SERVER_H
#define SETTING_SERVER_H

#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QDebug>

class SettingServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString domain READ       domain WRITE setDomain
                              RESET resetDomain NOTIFY   domainChanged)

    Q_PROPERTY(QString name READ       name WRITE setName
                            RESET resetName NOTIFY   nameChanged)

    Q_PROPERTY(QString password READ       password WRITE setPassword
                                RESET resetPassword NOTIFY   passwordChanged)

    Q_PROPERTY(QString dateFormat READ       dateFormat WRITE setDateFormat
                                  RESET resetDateFormat NOTIFY   dateFormatChanged)

    Q_PROPERTY(int onlineTimeout READ       onlineTimeout WRITE setOnlineTimeout
                                 RESET resetOnlineTimeout NOTIFY   onlineTimeoutChanged)

    Q_PROPERTY(int offlineTimeout READ       offlineTimeout WRITE setOfflineTimeout
                                  RESET resetOfflineTimeout NOTIFY   offlineTimeoutChanged)

    Q_PROPERTY(int requestTimeout READ       requestTimeout WRITE setRequestTimeout
                                  RESET resetRequestTimeout NOTIFY   requestTimeoutChanged)

    Q_PROPERTY(int updatePriority READ       updatePriority WRITE setUpdatePriority
                                  RESET resetUpdatePriority NOTIFY   updatePriorityChanged)

    Q_PROPERTY(QString workingDomain READ       workingDomain WRITE setWorkingDomain
                                     RESET resetWorkingDomain NOTIFY   workingDomainChanged)

    Q_PROPERTY(QString testingDomain READ       testingDomain WRITE setTestingDomain
                                     RESET resetTestingDomain NOTIFY   testingDomainChanged)

    Q_PROPERTY(QString defaultWorkingDomain READ       defaultWorkingDomain WRITE setDefaultWorkingDomain
                                            RESET resetDefaultWorkingDomain NOTIFY   defaultWorkingDomainChanged)

    Q_PROPERTY(QString defaultTestingDomain READ       defaultTestingDomain WRITE setDefaultTestingDomain
                                            RESET resetDefaultTestingDomain NOTIFY   defaultTestingDomainChanged)

    Q_PROPERTY(QString defaultName READ       defaultName WRITE setDefaultName
                                   RESET resetDefaultName NOTIFY   defaultNameChanged)

    Q_PROPERTY(QString defaultPassword READ       defaultPassword WRITE setDefaultPassword
                                       RESET resetDefaultPassword NOTIFY   defaultPasswordChanged)

    Q_PROPERTY(QString defaultDateFormat READ       defaultDateFormat WRITE setDefaultDateFormat
                                         RESET resetDefaultDateFormat NOTIFY   defaultDateFormatChanged)

    Q_PROPERTY(int defaultOnlineTimeout READ       defaultOnlineTimeout WRITE setDefaultOnlineTimeout
                                        RESET resetDefaultOnlineTimeout NOTIFY   defaultOnlineTimeoutChanged)

    Q_PROPERTY(int defaultOfflineTimeout READ       defaultOfflineTimeout WRITE setDefaultOfflineTimeout
                                         RESET resetDefaultOfflineTimeout NOTIFY   defaultOfflineTimeoutChanged)

    Q_PROPERTY(int defaultRequestTimeout READ       defaultRequestTimeout WRITE setDefaultRequestTimeout
                                         RESET resetDefaultRequestTimeout NOTIFY   defaultRequestTimeoutChanged)

    Q_PROPERTY(int defaultUpdatePriority READ       defaultUpdatePriority WRITE setDefaultUpdatePriority
                                         RESET resetDefaultUpdatePriority NOTIFY   defaultUpdatePriorityChanged)

public:
    explicit SettingServer(QObject *parent = nullptr);

    // READ ----------------------------------------------------------------------------------------
    QString domain()     const { return m_domain; }
    QString name()       const { return m_name; }
    QString password()   const { return m_password; }
    QString dateFormat() const { return m_dateFormat; }
    int onlineTimeout()  const { return m_onlineTimeout; }
    int offlineTimeout() const { return m_offlineTimeout; }
    int requestTimeout() const { return m_requestTimeout; }
    int updatePriority() const { return m_updatePriority; }
    QString defaultWorkingDomain() const { return m_defaultWorkingDomain; }
    QString defaultTestingDomain() const { return m_defaultTestingDomain; }
    QString workingDomain()     const { return m_workingDomain; }
    QString testingDomain()     const { return m_testingDomain; }
    QString defaultName()       const { return m_defaultName; }
    QString defaultPassword()   const { return m_defaultPassword; }
    QString defaultDateFormat() const { return m_defaultDateFormat; }
    int defaultOnlineTimeout()  const { return m_defaultOnlineTimeout; }
    int defaultOfflineTimeout() const { return m_defaultOfflineTimeout; }
    int defaultRequestTimeout() const { return m_defaultRequestTimeout; }
    int defaultUpdatePriority() const { return m_defaultUpdatePriority; }

    // RESET ---------------------------------------------------------------------------------------
    void resetAll();
    void resetDomain() { setDomain(defaultTestingDomain()); }
    void resetName() { setName(defaultName()); }
    void resetPassword() { setPassword(defaultPassword()); }
    void resetDateFormat() { setDateFormat(defaultDateFormat()); }
    void resetOnlineTimeout() { setOnlineTimeout(defaultOnlineTimeout()); }
    void resetOfflineTimeout() { setOfflineTimeout(defaultOfflineTimeout()); }
    void resetRequestTimeout() { setRequestTimeout(defaultRequestTimeout()); }
    void resetUpdatePriority() { setUpdatePriority(defaultUpdatePriority()); }
    void resetWorkingDomain() { setWorkingDomain(defaultWorkingDomain()); }
    void resetTestingDomain() { setTestingDomain(defaultTestingDomain()); }

    void resetDefaultWorkingDomain() { setDefaultWorkingDomain("https://wms.eridon.ua:7443/wms/hs/tcd-http/"); }
    void resetDefaultTestingDomain() { setDefaultTestingDomain("http://138.201.225.55/eridon/hs/tcd-http/"); }
    void resetDefaultName() { setDefaultName("Admin"); }
    void resetDefaultPassword() { setDefaultPassword("WMS#2016"); }
    void resetDefaultDateFormat() { setDefaultDateFormat("yyyyMMddhhmmss"); }
    void resetDefaultOnlineTimeout() { setDefaultOnlineTimeout(30); }
    void resetDefaultOfflineTimeout() { setDefaultOfflineTimeout(30); }
    void resetDefaultRequestTimeout() { setDefaultRequestTimeout(30); }
    void resetDefaultUpdatePriority() { setDefaultUpdatePriority(3); }

signals:
    void domainChanged(QString domain);
    void nameChanged(QString name);
    void passwordChanged(QString password);
    void dateFormatChanged(QString dateFormat);
    void onlineTimeoutChanged(int onlineTimeout);
    void offlineTimeoutChanged(int offlineTimeout);
    void requestTimeoutChanged(int requestTimeout);
    void updatePriorityChanged(int updatePriority);
    void defaultDomainChanged(QString defaultDomain);
    void workingDomainChanged(QString workingDomain);
    void defaultNameChanged(QString defaultName);
    void defaultPasswordChanged(QString defaultPassword);
    void defaultDateFormatChanged(QString defaultDateFormat);
    void defaultOnlineTimeoutChanged(int defaultOnlineTimeout);
    void defaultOfflineTimeoutChanged(int defaultOfflineTimeout);
    void defaultRequestTimeoutChanged(int defaultRequestTimeout);
    void defaultUpdatePriorityChanged(int defaultUpdatePriority);
    void testingDomainChanged(QString testingDomain);
    void defaultWorkingDomainChanged(QString defaultWorkingDomain);
    void defaultTestingDomainChanged(QString defaultTestingDomain);

private:
    QSettings settings;

    QString m_domain;
    QString m_name;
    QString m_password;
    QString m_dateFormat;
    int m_onlineTimeout;
    int m_offlineTimeout;
    int m_requestTimeout;
    int m_updatePriority;
    QString m_workingDomain;
    QString m_defaultName;
    QString m_defaultPassword;
    QString m_defaultDateFormat;
    int m_defaultOnlineTimeout;
    int m_defaultOfflineTimeout;
    int m_defaultRequestTimeout;
    int m_defaultUpdatePriority;
    QString m_testingDomain;
    QString m_defaultWorkingDomain;
    QString m_defaultTestingDomain;

public slots:
    void setDomain(QString domain);
    void setName(QString name);
    void setPassword(QString password);
    void setDateFormat(QString dateFormat);
    void setOnlineTimeout(int onlineTimeout);
    void setOfflineTimeout(int offlineTimeout);
    void setRequestTimeout(int requestTimeout);
    void setUpdatePriority(int updatePriority);
    void setWorkingDomain(QString workingDomain);
    void setDefaultName(QString defaultName);
    void setDefaultPassword(QString defaultPassword);
    void setDefaultDateFormat(QString defaultDateFormat);
    void setDefaultOnlineTimeout(int defaultOnlineTimeout);
    void setDefaultOfflineTimeout(int defaultOfflineTimeout);
    void setDefaultRequestTimeout(int defaultRequestTimeout);
    void setDefaultUpdatePriority(int defaultUpdatePriority);
    void setTestingDomain(QString testingDomain);
    void setDefaultWorkingDomain(QString defaultWorkingDomain);
    void setDefaultTestingDomain(QString defaultTestingDomain);
};

#endif // SETTING_SERVER_H

