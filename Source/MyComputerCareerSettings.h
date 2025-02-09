#ifndef QMyComputerCareerSettings_h__
#define QMyComputerCareerSettings_h__

#include <QGuiApplication>
#include <QDir>
#include <QUrl>
#include <QRect>

class QMyComputerCareerSettings : public QObject{
	Q_OBJECT
public:
	static QMyComputerCareerSettings* Instance();

	QDir workDir() const;
	void setWorkDir(QDir val);

	void save();
	void load();

	void setAutoStartOnWindows(bool autoStart);
	bool isAutoStartOnWindows() const;

	float saveIntervalSec() const { return mSaveIntervalSec; }
	void setSaveIntervalSec(float val) { mSaveIntervalSec = val; }

	bool isToastEnabled() const { return mToastEnabled; }
	void setToastEnabled(bool val) { mToastEnabled = val; }
	QRect lastWindowGeomtry() const { return mLastWindowGeomtry; }
	void setLastWindowGeomtry(QRect val) { mLastWindowGeomtry = val; }
private:
	QMyComputerCareerSettings();
private:
	QDir mWorkDir = QDir("./Home");
	float mSaveIntervalSec = 300.0f;
	bool mToastEnabled = false;
	QRect mLastWindowGeomtry;
};

#endif // QMyComputerCareerSettings_h__
