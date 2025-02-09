#include "MyComputerCareerSettings.h"
#include <QSettings>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFontDatabase>
#include <QFont>

QMyComputerCareerSettings::QMyComputerCareerSettings()
{
	setAutoStartOnWindows(true);
	QFontDatabase::addApplicationFont(":/Resources/Roboto-Regular-14.ttf");
	QFontDatabase::addApplicationFont(":/Resources/Roboto-Bold-3.ttf");
}

QMyComputerCareerSettings* QMyComputerCareerSettings::Instance()
{
	static QMyComputerCareerSettings Inst;
	return &Inst;
}

QDir QMyComputerCareerSettings::workDir() const
{
	return mWorkDir;
}

void QMyComputerCareerSettings::setWorkDir(QDir val)
{
	mWorkDir = val;
}

QJsonArray rectToJsonArray(const QRect& rect) {
	QJsonArray array;
	array.append(rect.x());
	array.append(rect.y());
	array.append(rect.width());
	array.append(rect.height());
	return array;
}

QRect jsonArrayToRect(const QJsonArray& array) {
	if (array.size() == 4) {
		int x = array.at(0).toInt();
		int y = array.at(1).toInt();
		int width = array.at(2).toInt();
		int height = array.at(3).toInt();
		return QRect(x, y, width, height);
	}
	return QRect(); 
}

void QMyComputerCareerSettings::save()
{
	QJsonObject jsonObject;
	QJsonArray lastWindowGeomtry;
	jsonObject["LastWindowGeomtry"] = rectToJsonArray(mLastWindowGeomtry);
	jsonObject["SaveIntervalSec"] = mSaveIntervalSec;
	QString confiPath = mWorkDir.absoluteFilePath("config.json");
	QJsonDocument jsonDoc(jsonObject);
	QByteArray jsonData = jsonDoc.toJson();
	QFile file(confiPath);
	if (file.open(QIODevice::WriteOnly)) {
		file.write(jsonData);
		file.close();
	}
}

void QMyComputerCareerSettings::load()
{
	QString confiPath = mWorkDir.absoluteFilePath("config.json");
	QFile file(confiPath);
	QByteArray jsonData;
	if (file.open(QIODevice::ReadWrite)) {
		jsonData = file.readAll();
		file.close();
	}
	QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
	QJsonObject jsonObject = jsonDoc.object();
	if (jsonObject.contains("SaveIntervalSec")) {
		mSaveIntervalSec = jsonObject["SaveIntervalSec"].toDouble();
	}
	if (jsonObject.contains("LastWindowGeomtry")) {
		mLastWindowGeomtry = jsonArrayToRect(jsonObject["LastWindowGeomtry"].toArray());
	}
}

void QMyComputerCareerSettings::setAutoStartOnWindows(bool autoStart)
{
	QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
	QString appName = QCoreApplication::applicationName();
	QString appPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
	if (autoStart) {
		settings.setValue(appName, appPath);
		qDebug() << "已设置开机自启";
	}
	else {
		settings.remove(appName);
		qDebug() << "已取消开机自启";
	}
}

bool QMyComputerCareerSettings::isAutoStartOnWindows() const
{
	QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
	QString appName = QCoreApplication::applicationName();
	QString appPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
	return settings.value(appName) == appPath;
}
