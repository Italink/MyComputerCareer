#include "MyComputerCareerApplication.h"
#include "Hook/SystemInputHook.h"
#include <QMutexLocker>
#include <QSaveFile>
#include <QtDebug>
#include <QSvgGenerator>
#include <QMetaEnum>
#include <QPainter>
#include "MyComputerCareerSettings.h"
#include <windows.h>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class QEventSaveThread : public QThread
{
public:
	QEventSaveThread(QMyComputerCareerApplication* app)
		:mApp(app) {
	}
	void run() override {
		QDateTime currentDateTime = QDateTime::currentDateTime();
		QElapsedTimer timer;
		timer.start();
		QString saveFilePath = QMyComputerCareerSettings::Instance()->workDir().absoluteFilePath(QString("History/UserInput/") + currentDateTime.toString("yyyy_MM_dd_hh_mm_ss") + ".txt");
		QFile file(saveFilePath);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
			qFatal() << "Failed to open file";
		}
		QTextStream QS(&file);
		while (!bRequestQuit) {
			if (!mApp->mEventDataPool.isEmpty()) {{
					QMutexLocker locker(&mApp->mMutex);
					for (auto eventData : mApp->mEventDataPool) {
						QS << eventData << '\n';
					}
					QS.flush();
					mApp->mEventDataPool.clear();
				}
				QThread::sleep(5);
				if (timer.elapsed() > QMyComputerCareerSettings::Instance()->saveIntervalSec() * 1000.0f) {
					mApp->save("[submit] sync user input");
					timer.restart();
				}
			}
		}
	}
public:
	bool bRequestQuit = false;
	QMyComputerCareerApplication* mApp = nullptr;
};

QMyComputerCareerApplication::QMyComputerCareerApplication(int& argc, char** argv)
	: QApplication(argc, argv)
	, mEventSaveThread(QSharedPointer<QEventSaveThread>::create(this))
{
	mSharedMemory.setKey("MyComputerCareer");
	if (mSharedMemory.attach()) {
		isRunning = true;
	}
	else {
		isRunning = false;
		if (!mSharedMemory.create(1)) {
			;
			return;
		}
	}
}

QMyComputerCareerApplication::~QMyComputerCareerApplication()
{
	SystemInputHook::Instance()->shutdown();
	((QEventSaveThread*)mEventSaveThread.get())->bRequestQuit = true;
	mEventSaveThread->quit();
	mEventSaveThread->wait();
	save("[submit] today is over");
}

void QMyComputerCareerApplication::initialize()
{
	setWindowIcon(QIcon(":/Resources/Icon.png"));
	mKeyboradWidget = new QKeyboardWidget;
	QMyComputerCareerSettings::Instance()->load();
	QDir workDir = QMyComputerCareerSettings::Instance()->workDir();
	if (!workDir.exists() || !workDir.exists("History/UserInput")) {
		workDir.mkpath("History/UserInput");
	}
	QString userInputSavePath = workDir.absoluteFilePath("UserInputStatistics.json");
	QFile file(userInputSavePath);
	QByteArray jsonData;
	if (file.open(QIODevice::ReadWrite)) {
		jsonData = file.readAll();
		file.close();
	}
	QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
	QJsonObject jsonObject = jsonDoc.object();
	mLocalUserInputStatistics = UserInputStatistics::fromJsonObject(jsonObject);
	
	SystemInputHook::Instance()->startup(std::bind(&QMyComputerCareerApplication::onKeyEvent, this, std::placeholders::_1), std::bind(&QMyComputerCareerApplication::onMouseEvent, this, std::placeholders::_1));
	mEventSaveThread->start();
	mKeyboradWidget->show();
	QRect rect = QMyComputerCareerSettings::Instance()->lastWindowGeomtry();
	if (!rect.isEmpty()) {
		mKeyboradWidget->setGeometry(rect);
	}
}

void QMyComputerCareerApplication::save(QString message)
{
	QDir workDir = QMyComputerCareerSettings::Instance()->workDir();
	QString userInputSavePath = workDir.absoluteFilePath("UserInputStatistics.json");
	QJsonDocument jsonDoc(mLocalUserInputStatistics.toJsonObject());
	QByteArray jsonData = jsonDoc.toJson();
	QFile file(userInputSavePath);
	if (file.open(QIODevice::WriteOnly)) {
		file.write(jsonData);
		file.close();
	}
}

QToast* QMyComputerCareerApplication::spawnToast(QString text)
{
	QToast* toast = new QToast(text);
	toast->show();
	mToastQueue.enqueue(toast);
	connect(toast, &QObject::destroyed, [this, toast]() {
		mToastQueue.removeOne(toast);
	});
	return toast;
}

void QMyComputerCareerApplication::onKeyEvent(const MinimizedInputEvent_Keyboard& keyEvent)
{
	QMutexLocker locker(&mMutex);
	QString data;
	QTextStream stream(&data, QDataStream::OpenModeFlag::WriteOnly);
	stream << keyEvent.timestamp << " " << keyEvent.type << " " << keyEvent.vkCode << " " << keyEvent.modifiers;
	bool needSpawnNewToast = false;
	if (keyEvent.type == QEvent::KeyPress) {
		QDateTime dateTime = QDateTime::currentDateTime();
		QString timeString = dateTime.toString("yyyy.MM.dd hh:00:00");
		QString keyName = SystemInputHook::getKeyNameByVkCode(keyEvent.vkCode);
		mLocalUserInputStatistics.keyUseCount[keyName]++;
		mLocalUserInputStatistics.keyUsePerHourCount[timeString]++;
		mLocalUserInputStatistics.keyUseTotalCount++;
		mKeyboradWidget->setKeyPressed(keyEvent.vkCode, true);
		mPressedKeys.insert(keyEvent.vkCode);
		if (mPressedKeys.size() == 1) {
			needSpawnNewToast = true;
		}
	}
	else {
		mKeyboradWidget->setKeyPressed(keyEvent.vkCode, false);
		mPressedKeys.remove(keyEvent.vkCode);
		needSpawnNewToast = true;
	}
	mKeyboradWidget->update();
	mEventDataPool << data;

	//if (!QMyComputerCareerSettings::Instance()->isToastEnabled())
	//	return;
	//QString text;
	//for (auto vkCode : mPressedKeys) {
	//	if (!text.isEmpty())
	//		text += "+";
	//	text += SystemInputHook::getKeyNameByVkCode(vkCode);
	//}
	//if (!text.isEmpty()) {
	//	if (needSpawnNewToast || mCurrentToast == nullptr) {
	//		if (mCurrentToast) {
	//			mCurrentToast->fadeOut();
	//			mCurrentToast = nullptr;
	//		}
	//		mCurrentToast = spawnToast(text);
	//	}
	//	else {
	//		mCurrentToast->updateText(text);
	//	}
	//}
	//else if (mCurrentToast) {
	//	mCurrentToast->fadeOut();
	//	mCurrentToast = nullptr;
	//}
}

void QMyComputerCareerApplication::onMouseEvent(const MinimizedInputEvent_Mouse& mouseEvent)
{
	static QPoint lastMousePosition(INT_MIN, INT_MIN);
	if (mouseEvent.type == QEvent::MouseMove) {
		if (lastMousePosition.x() != INT_MIN&& lastMousePosition.y() != INT_MIN) {
			int dx = mouseEvent.position.x() - lastMousePosition.x();
			int dy = mouseEvent.position.y() - lastMousePosition.y();
			mLocalUserInputStatistics.mouseMoveDistance += qSqrt(dx * dx + dy * dy);
		}
		lastMousePosition = mouseEvent.position;
		return;
	}
	QMutexLocker locker(&mMutex);
	QString data;
	QTextStream stream(&data, QDataStream::OpenModeFlag::WriteOnly);
	stream << mouseEvent.timestamp << " " << mouseEvent.type << " " << mouseEvent.button << " " << mouseEvent.position.x() << " " << mouseEvent.position.y();
	if (mouseEvent.type == QEvent::MouseButtonPress) {
		QString mouseButtonName = "Unknown";
		QMetaEnum metaEnum = QMetaEnum::fromType<Qt::MouseButtons>();
		int mouseButtonValue = static_cast<int>(mouseEvent.button);
		if (mouseButtonValue < metaEnum.keyCount()) {
			mouseButtonName = QString(metaEnum.valueToKey(mouseButtonValue));
		}
		mLocalUserInputStatistics.keyUseCount[mouseButtonName]++;
		if(mouseEvent.button & Qt::LeftButton)
			mKeyboradWidget->setKeyPressed(VK_LBUTTON, true);
		if (mouseEvent.button & Qt::RightButton)
			mKeyboradWidget->setKeyPressed(VK_RBUTTON, true);
	}	
	if (mouseEvent.type == QEvent::MouseButtonRelease) {
		if (mouseEvent.button & Qt::LeftButton)
			mKeyboradWidget->setKeyPressed(VK_LBUTTON, false);
		if (mouseEvent.button & Qt::RightButton)
			mKeyboradWidget->setKeyPressed(VK_RBUTTON, false);
	}
	mEventDataPool << data;
	mKeyboradWidget->update();
}

const UserInputStatistics& QMyComputerCareerApplication::getLocalUserInputStatistics()
{
	return mLocalUserInputStatistics;
}

bool QMyComputerCareerApplication::isAppRunning() const
{
	return isRunning;
}
