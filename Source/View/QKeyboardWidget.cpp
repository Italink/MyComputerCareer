#include "QKeyboardWidget.h"
#include <QPainter>
#include <QStringList>
#include <QRect>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <windows.h>      
#include <windowsx.h>
#include "Hook/SystemInputHook.h"
#include "MyComputerCareerApplication.h"
#include "MyComputerCareerSettings.h"

QKeyboardWidget::QKeyboardWidget(QWidget* parent) 
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setMouseTracking(true);
	initVirtKeyMap();
	resize(500, 130);
}

void QKeyboardWidget::setKeyPressed(quint32 vkCode, bool bPressed)
{
	mVirtKeyRectMap[vkCode].pressed = bPressed;
	if (vkCode == VK_RETURN) {
		mVirtKeyRectMap[VK_RRETURN].pressed = bPressed;
	}
	if (mUserInputStatisticsWidget && mUserInputStatisticsWidget->isVisible()) {
		showStatistics(false);
	}
}

QRect getWindowsTaskbarRect()
{
	APPBARDATA appBarData;
	appBarData.cbSize = sizeof(APPBARDATA);
	if (SHAppBarMessage(ABM_GETTASKBARPOS, &appBarData))
	{
		return QRect(appBarData.rc.left, appBarData.rc.top, appBarData.rc.right - appBarData.rc.left, appBarData.rc.bottom - appBarData.rc.top);
	}
	return QRect();
}

void QKeyboardWidget::showStatistics(bool animation)
{
	if (mUserInputStatisticsWidget == nullptr) {
		mUserInputStatisticsWidget = new QUserInputStatisticsWidget;
	}
	QMyComputerCareerApplication* app = (QMyComputerCareerApplication*)qApp;
	mUserInputStatisticsWidget->activate(app->getLocalUserInputStatistics(), geometry(), animation);
}

void QKeyboardWidget::initVirtKeyMap()
{
	mVirtKeyRectMap.clear();

	const std::vector<int> firstRowVK = { VK_ESCAPE, 0, VK_F1, VK_F2, VK_F3, VK_F4, 1, VK_F5, VK_F6, VK_F7, VK_F8, 1, VK_F9, VK_F10, VK_F11, VK_F12, 1, VK_SNAPSHOT, VK_SCROLL, VK_PAUSE};
	const std::vector<int> secondRowVK = { VK_OEM_3, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', VK_OEM_MINUS, VK_OEM_PLUS, VK_BACK, 1, VK_INSERT, VK_HOME, VK_PRIOR, 1, VK_NUMLOCK, VK_DIVIDE, VK_MULTIPLY, VK_SUBTRACT };
	const std::vector<int> thirdRowVK = { VK_TAB, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', VK_OEM_4, VK_OEM_6, VK_OEM_5, 1, VK_DELETE, VK_END, VK_NEXT, 1, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9 };
	const std::vector<int> fourthRowVK = { VK_CAPITAL, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', VK_OEM_1, VK_OEM_7, VK_RETURN, 1, 0, 0, 0, 1, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6};
	const std::vector<int> fifthRowVK = { VK_LSHIFT, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', VK_OEM_COMMA, VK_OEM_PERIOD, VK_OEM_2, VK_RSHIFT, 1, 0, VK_UP, 0, 1, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3};
	const std::vector<int> sixthRowVK = { VK_LCONTROL, VK_LWIN, VK_LMENU, VK_SPACE, VK_RMENU, VK_RWIN, VK_APPS, VK_RCONTROL, 1, VK_LEFT, VK_DOWN, VK_RIGHT, 1, VK_NUMPAD0, VK_DECIMAL };

	auto fillRow = [this](const std::vector<int>& keys, int yPos) {
		int currentX = 5;
		for (int key : keys) {
			int keyWidth;
			if (key == VK_LCONTROL || key == VK_RCONTROL || key == VK_LMENU || key == VK_RMENU || key == VK_LWIN || key == VK_RWIN || key == VK_APPS) {
				keyWidth = 52;
			}
			else if (key == 1) {
				key = 0;
				keyWidth = 40 / 2;
			}
			else if (key == VK_TAB) {
				keyWidth = 60;
			}
			else if (key == VK_OEM_5) {
				keyWidth = 70;
			}
			else if (key == VK_CAPITAL) {
				keyWidth = 70;
			}
			else if (key == VK_LSHIFT) {
				keyWidth = 95;
			}
			else if (key == VK_RSHIFT) {
				keyWidth = 125;
			}
			else if (key == VK_SPACE) {
				keyWidth = 276;
			}
			else if (key == VK_BACK) {
				keyWidth = 90;
			}
			else if (key == VK_RETURN) {
				keyWidth = 105;
			}
			else if (key == VK_NUMPAD0) {
				keyWidth = 85;
			}
			else {
				keyWidth = 40;
			}
			if (key != 0) {
				QRect keyRect(currentX, yPos, keyWidth, 40);
				mVirtKeyRectMap[key].region = keyRect;
			}
			currentX += keyWidth + 5;
		}
	};

	int currentY = 5;
	fillRow(firstRowVK, currentY);
	currentY += 40 + 5;

	fillRow(secondRowVK, currentY);
	currentY += 40 + 5;

	fillRow(thirdRowVK, currentY);
	mVirtKeyRectMap[VK_ADD].region = QRect(1005, currentY, 40, 40 * 2 + 5);
	currentY += 40 + 5;

	fillRow(fourthRowVK, currentY);
	currentY += 40 + 5;

	fillRow(fifthRowVK, currentY);
	mVirtKeyRectMap[VK_RRETURN].region = QRect(1005, currentY, 40, 40 * 2 + 5);
	currentY += 40 + 5;

	fillRow(sixthRowVK, currentY);
	mVirtKeyRectMap[VK_LBUTTON].region = QRect(1075, 50, 40, 130);
	mVirtKeyRectMap[VK_RBUTTON].region = QRect(1165, 50, 40, 130);

	for (auto key : mVirtKeyRectMap.asKeyValueRange()) {
		mVirtKeyRectMap[key.first].text = SystemInputHook::getShortKeyNameByVkCode(key.first);
	}
	mVirtKeyRectMap[VK_RRETURN].text = SystemInputHook::getShortKeyNameByVkCode(VK_RETURN);

	mVirtKeyRectMap[VK_MBUTTON_UP].region = QRect(1120, 50, 40, 40);
	mVirtKeyRectMap[VK_MBUTTON_UP].text = "▲";

	mVirtKeyRectMap[VK_MBUTTON].region = QRect(1120, 95, 40, 40);

	mVirtKeyRectMap[VK_MBUTTON_DOWN].region = QRect(1120, 140, 40, 40);
	mVirtKeyRectMap[VK_MBUTTON_DOWN].text = "▼";

	mVirtKeyRectMap[VK_NULL].region = QRect(1075, 185, 130, 85);

	mVirtKeyRectMap[VK_STATISTICS].region = QRect(1075, 5, 40, 40);
	mVirtKeyRectMap[VK_STATISTICS].text = "⛵";
	mVirtKeyRectMap[VK_STATISTICS].advancedDisplay = true;
	mVirtKeyRectMap[VK_STATISTICS].clickedCallback = [this]() {
		showStatistics(true);
	};

	mVirtKeyRectMap[VK_AUTO_START].region = QRect(1120, 5, 40, 40);
	mVirtKeyRectMap[VK_AUTO_START].text = "√";
	mVirtKeyRectMap[VK_AUTO_START].advancedDisplay = true;
	bool autoStart = QMyComputerCareerSettings::Instance()->isAutoStartOnWindows();
	mVirtKeyRectMap[VK_AUTO_START].textColor = autoStart ? Qt::green : Qt::white;
	mVirtKeyRectMap[VK_AUTO_START].clickedCallback = [this]() {
		bool autoStart = !QMyComputerCareerSettings::Instance()->isAutoStartOnWindows();
		QMyComputerCareerSettings::Instance()->setAutoStartOnWindows(autoStart);
		mVirtKeyRectMap[VK_AUTO_START].textColor = autoStart ? Qt::green : Qt::white;
		update();
	};

	mVirtKeyRectMap[VK_CLOSE].region = QRect(1165, 5, 40, 40);
	mVirtKeyRectMap[VK_CLOSE].hoverdColor = Qt::red;
	mVirtKeyRectMap[VK_CLOSE].advancedDisplay = true;
	mVirtKeyRectMap[VK_CLOSE].text = "X";
	mVirtKeyRectMap[VK_CLOSE].clickedCallback = []() {
		QMyComputerCareerSettings::Instance()->save();
		qApp->quit();
	};
}

void QKeyboardWidget::wheelEvent(QWheelEvent* event)
{
	QSize curentSize = size();
	if (event->angleDelta().y() > 0 && curentSize.width() < 1000) {
		resize(curentSize * 1.1);
	}	
	else if (event->angleDelta().y() < 0 && curentSize.width() > 400) {
		resize(curentSize * 0.9);
	}
	if (mUserInputStatisticsWidget && mUserInputStatisticsWidget->isVisible()) {
		mUserInputStatisticsWidget->hide();
	}
	QMyComputerCareerSettings::Instance()->setLastWindowGeomtry(geometry());
	QWidget::wheelEvent(event);
}

void QKeyboardWidget::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton) {
		mLastClickPos = e->pos();
		QVector2D scale(VirtualKeyboardSize.width() / (float)width(), VirtualKeyboardSize.height() / (float)height());
		QVector2D mousePos(mapFromGlobal(QCursor::pos()));
		QPoint virtualMousePos = (mousePos * scale).toPoint();
		for (const auto& key : mVirtKeyRectMap.asKeyValueRange()) {
			if (key.second.region.contains(virtualMousePos) && key.second.clickedCallback) {
				key.second.clickedCallback();
			}
		}
	}
	QWidget::mousePressEvent(e);
}

void QKeyboardWidget::mouseMoveEvent(QMouseEvent* e)
{
	if (e->buttons() & Qt::LeftButton) {
		move(QCursor::pos() - mLastClickPos);
		if (mUserInputStatisticsWidget && mUserInputStatisticsWidget->isVisible()) {
			mUserInputStatisticsWidget->hide();
		}
		QMyComputerCareerSettings::Instance()->setLastWindowGeomtry(geometry());
	}
	update();
	QWidget::mouseMoveEvent(e);
}

void QKeyboardWidget::enterEvent(QEnterEvent* e)
{
	QWidget::enterEvent(e);
	bHovered = true;
	update();
}

void QKeyboardWidget::leaveEvent(QEvent* e)
{
	QWidget::leaveEvent(e);
	bHovered = false;
	update();
	if (mUserInputStatisticsWidget && mUserInputStatisticsWidget->isVisible()) {
		mUserInputStatisticsWidget->hide();
	}
}

void QKeyboardWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setFont(QFont("Roboto", 7));
	painter.setRenderHint(QPainter::Antialiasing);  
	painter.setRenderHint(QPainter::TextAntialiasing); 
	painter.fillRect(rect(), bHovered ? QColor(0, 0, 0, 50) : QColor(0, 0, 0, 1));
	QVector2D scale(VirtualKeyboardSize.width() / (float)width(), VirtualKeyboardSize.height() / (float)height());
	QVector2D mousePos(mapFromGlobal(QCursor::pos()));
	QPoint virtualMousePos = (mousePos * scale).toPoint();
	for (auto item : mVirtKeyRectMap.asKeyValueRange()) {
		quint32 vkCode = item.first;
		if (!bHovered && item.second.advancedDisplay)
			continue;
		QRect rect = item.second.region;
		rect.setCoords(rect.left() / scale.x(), rect.top() / scale.y(), rect.right() / scale.x(), rect.bottom() / scale.y());
		if (item.second.pressed) {
			painter.fillRect(rect, item.second.pressedColor);
		}
		else if (item.second.region.contains(virtualMousePos)) {
			painter.fillRect(rect, item.second.hoverdColor);
		}
		else {
			painter.fillRect(rect, item.second.baseColor);
		}
		painter.setPen(item.second.textColor);
		painter.drawText(rect, Qt::AlignCenter, item.second.text);
	}
}

void QKeyboardWidget::showEvent(QShowEvent* event)
{
	QWidget::showEvent(event);
}
