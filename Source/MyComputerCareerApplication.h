#ifndef QMyComputerCareerApplication_h__
#define QMyComputerCareerApplication_h__

#include <QApplication>
#include <QMouseEvent>
#include <QMutex>
#include <QSet>
#include <QThread>
#include <QQueue>
#include <QSharedMemory>
#include <QSharedPointer>
#include "Hook/SystemInputHook.h"
#include "View/QKeyboardWidget.h"
#include "View/QToast.h"
#include <QMessageBox>
#include "View/QUserInputStatisticsWidget.h"

class QMyComputerCareerApplication : public QApplication{
	Q_OBJECT
	friend class QEventSaveThread;
public:
	QMyComputerCareerApplication(int& argc, char** argv);
	~QMyComputerCareerApplication();
	const UserInputStatistics& getLocalUserInputStatistics();
	bool isAppRunning() const;
	void initialize();
private:
	void save(QString message);
	QToast* spawnToast(QString text);
	void onKeyEvent(const MinimizedInputEvent_Keyboard& keyEvent);
	void onMouseEvent(const MinimizedInputEvent_Mouse& mouseEvent);
	void onUpdateWheelState();
protected:
	QKeyboardWidget* mKeyboradWidget = nullptr;
	QList<QString> mEventDataPool;
	QMutex mMutex;
	QSharedPointer<QThread> mEventSaveThread;
	UserInputStatistics mLocalUserInputStatistics;
	QSet<quint32> mPressedKeys;
	QToast* mCurrentToast = nullptr;
	QQueue<QToast*> mToastQueue;
	QSharedMemory mSharedMemory;
	bool isRunning;
	float mWheelHoldTime;
	QTimer mWheelHoldTimer;
};

#endif // QMyComputerCareerApplication_h__
