#include "settingServer.h"

SettingServer::SettingServer(QObject *parent) : QObject(parent), settings()
{
    settings.sync();
    settings.beginGroup("server");

    if (settings.contains("defaultName"))
        m_defaultName = settings.value("defaultName").toString();
    else
        resetDefaultName();

    if (settings.contains("defaultPassword"))
        m_defaultPassword = settings.value("defaultPassword").toString();
    else
        resetDefaultPassword();

    if (settings.contains("defaultDateFormat"))
        m_defaultDateFormat = settings.value("defaultDateFormat").toString();
    else
        resetDefaultDateFormat();

    if (settings.contains("defaultOnlineTimeout"))
        m_defaultOnlineTimeout = settings.value("defaultOnlineTimeout").toInt();
    else
        resetDefaultOnlineTimeout();

    if (settings.contains("defaultOfflineTimeout"))
        m_defaultOfflineTimeout = settings.value("defaultOfflineTimeout").toInt();
    else
        resetDefaultOfflineTimeout();

    if (settings.contains("defaultRequestTimeout"))
        m_defaultRequestTimeout = settings.value("defaultRequestTimeout").toInt();
    else
        resetDefaultRequestTimeout();

    if (settings.contains("defaultUpdatePriority"))
        m_defaultUpdatePriority = settings.value("defaultUpdatePriority").toInt();
    else
        resetDefaultUpdatePriority();

    if (settings.contains("defaultWorkingDomain"))
        m_defaultWorkingDomain  = settings.value("defaultWorkingDomain").toString();
    else
        resetDefaultWorkingDomain();

    if (settings.contains("defaultTestingDomain"))
        m_defaultTestingDomain  = settings.value("defaultTestingDomain").toString();
    else
        resetDefaultTestingDomain();

    m_domain     = settings.value("domain",     defaultWorkingDomain()).toString();
    m_name       = settings.value("name",       defaultName()).toString();
    m_password   = settings.value("password",   defaultPassword()).toString();
    m_dateFormat = settings.value("dateFormat", defaultDateFormat()).toString();
    m_onlineTimeout   = settings.value("onlineTimeout",   defaultOnlineTimeout()).toInt();
    m_offlineTimeout  = settings.value("offlineTimeout",  defaultOfflineTimeout()).toInt();
    m_requestTimeout  = settings.value("requestTimeout",  defaultRequestTimeout()).toInt();
    m_updatePriority  = settings.value("updatePriority",  defaultUpdatePriority()).toInt();
    m_workingDomain   = settings.value("workingDomain",   defaultWorkingDomain()).toString();
    m_testingDomain   = settings.value("testingDomain",   defaultTestingDomain()).toString();
    settings.endGroup();
}

void SettingServer::resetAll()
{
    resetDateFormat();
    resetDefaultDateFormat();
    resetDefaultName();
    resetDefaultOfflineTimeout();
    resetDefaultOnlineTimeout();
    resetDefaultPassword();
    resetDefaultRequestTimeout();
    resetDefaultTestingDomain();
    resetDefaultUpdatePriority();
    resetDefaultWorkingDomain();
    resetDomain();
    resetName();
    resetOfflineTimeout();
    resetOnlineTimeout();
    resetPassword();
    resetRequestTimeout();
    resetTestingDomain();
    resetUpdatePriority();
    resetWorkingDomain();
}

void SettingServer::setDomain(QString domain)
{
    if (m_domain != domain){
        m_domain  = domain;
        settings.setValue("server/domain", domain);
        emit domainChanged(m_domain);
        emit reconnect();
    }
}

void SettingServer::setName(QString name)
{
    if (m_name != name){
        m_name  = name;
        settings.setValue("server/name", name);
        emit nameChanged(m_name);
        emit reconnect();
    }
}

void SettingServer::setPassword(QString password)
{
    if (m_password != password){
        m_password  = password;
        settings.setValue("server/password", password);
        emit passwordChanged(m_password);
        emit reconnect();
    }
}

void SettingServer::setDateFormat(QString dateFormat)
{
    if (m_dateFormat != dateFormat){
        m_dateFormat  = dateFormat;
        settings.setValue("server/dateFormat", dateFormat);
        emit dateFormatChanged(m_dateFormat);
    }
}

void SettingServer::setOnlineTimeout(int onlineTimeout)
{
    if (m_onlineTimeout != onlineTimeout){
        m_onlineTimeout  = onlineTimeout;
        settings.setValue("server/onlineTimeout", onlineTimeout);
        emit onlineTimeoutChanged(m_onlineTimeout);
    }
}

void SettingServer::setOfflineTimeout(int offlineTimeout)
{
    if (m_offlineTimeout != offlineTimeout){
        m_offlineTimeout  = offlineTimeout;
        settings.setValue("server/offlineTimeout", offlineTimeout);
        emit offlineTimeoutChanged(m_offlineTimeout);
    }
}

void SettingServer::setRequestTimeout(int requestTimeout)
{
    if (m_requestTimeout != requestTimeout){
        m_requestTimeout  = requestTimeout;
        settings.setValue("server/requestTimeout", requestTimeout);
        emit requestTimeoutChanged(m_requestTimeout);
    }
}

void SettingServer::setUpdatePriority(int updatePriority)
{
    if (m_updatePriority != updatePriority){
        m_updatePriority  = updatePriority;
        settings.setValue("server/updatePriority", updatePriority);
        emit updatePriorityChanged(m_updatePriority);
    }
}

void SettingServer::setWorkingDomain(QString workingDomain)
{
    if (m_workingDomain != workingDomain){
        m_workingDomain  = workingDomain;
        settings.setValue("server/workingDomain", workingDomain);
        emit workingDomainChanged(m_workingDomain);
    }
}

void SettingServer::setDefaultName(QString defaultName)
{
    if (m_defaultName != defaultName){
        m_defaultName  = defaultName;
        settings.setValue("server/defaultName", defaultName);
        emit defaultNameChanged(m_defaultName);
    }
}

void SettingServer::setDefaultPassword(QString defaultPassword)
{
    if (m_defaultPassword != defaultPassword){
        m_defaultPassword  = defaultPassword;
        settings.setValue("server/defaultPassword", defaultPassword);
        emit defaultPasswordChanged(m_defaultPassword);
    }
}

void SettingServer::setDefaultDateFormat(QString defaultDateFormat)
{
    if (m_defaultDateFormat != defaultDateFormat){
        m_defaultDateFormat  = defaultDateFormat;
        settings.setValue("server/defaultDateFormat", defaultDateFormat);
        emit defaultDateFormatChanged(m_defaultDateFormat);
    }
}

void SettingServer::setDefaultOnlineTimeout(int defaultOnlineTimeout)
{
    if (m_defaultOnlineTimeout != defaultOnlineTimeout){
        m_defaultOnlineTimeout  = defaultOnlineTimeout;
        settings.setValue("server/defaultOnlineTimeout", defaultOnlineTimeout);
        emit defaultOnlineTimeoutChanged(m_defaultOnlineTimeout);
    }
}

void SettingServer::setDefaultOfflineTimeout(int defaultOfflineTimeout)
{
    if (m_defaultOfflineTimeout != defaultOfflineTimeout){
        m_defaultOfflineTimeout  = defaultOfflineTimeout;
        settings.setValue("server/defaultOfflineTimeout", defaultOfflineTimeout);
        emit defaultOfflineTimeoutChanged(m_defaultOfflineTimeout);
    }
}

void SettingServer::setDefaultRequestTimeout(int defaultRequestTimeout)
{
    if (m_defaultRequestTimeout != defaultRequestTimeout){
        m_defaultRequestTimeout  = defaultRequestTimeout;
        settings.setValue("server/defaultRequestTimeout", defaultRequestTimeout);
        emit defaultRequestTimeoutChanged(m_defaultRequestTimeout);
    }
}

void SettingServer::setDefaultUpdatePriority(int defaultUpdatePriority)
{
    if (m_defaultUpdatePriority != defaultUpdatePriority){
        m_defaultUpdatePriority  = defaultUpdatePriority;
        settings.setValue("server/defaultUpdatePriority", defaultUpdatePriority);
        emit defaultUpdatePriorityChanged(m_defaultUpdatePriority);
    }
}

void SettingServer::setTestingDomain(QString testingDomain)
{
    if (m_testingDomain != testingDomain){
        m_testingDomain  = testingDomain;
        settings.setValue("server/testingDomain", testingDomain);
        emit testingDomainChanged(m_testingDomain);
    }
}

void SettingServer::setDefaultWorkingDomain(QString defaultWorkingDomain)
{
    if (m_defaultWorkingDomain != defaultWorkingDomain){
        m_defaultWorkingDomain  = defaultWorkingDomain;
        settings.setValue("server/defaultWorkingDomain", defaultWorkingDomain);
        emit defaultWorkingDomainChanged(m_defaultWorkingDomain);
    }
}

void SettingServer::setDefaultTestingDomain(QString defaultTestingDomain)
{
    if (m_defaultTestingDomain != defaultTestingDomain){
        m_defaultTestingDomain = defaultTestingDomain;
        settings.setValue("server/defaultTestingDomain", defaultTestingDomain);
        emit defaultTestingDomainChanged(m_defaultTestingDomain);
    }
}
