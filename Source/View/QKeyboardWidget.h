#ifndef QKeyboardWidget_h__
#define QKeyboardWidget_h__

#include <QWidget>
#include "QUserInputStatisticsWidget.h"

const QSize VirtualKeyboardSize(1215, 270);

const quint32 VK_CUSTOM = 10000;
const quint32 VK_NULL = VK_CUSTOM + 1;
const quint32 VK_RRETURN = VK_CUSTOM + 2;
const quint32 VK_STATISTICS = VK_CUSTOM + 3;
const quint32 VK_AUTO_START = VK_CUSTOM + 4;
const quint32 VK_CLOSE = VK_CUSTOM + 5;
const quint32 VK_MBUTTON_UP = VK_CUSTOM + 6;
const quint32 VK_MBUTTON_DOWN = VK_CUSTOM + 7;

class QKeyboardWidget : public QWidget {
public:
	QKeyboardWidget(QWidget* parent = nullptr);
	void setKeyPressed(quint32 vkCode, bool bPressed);
	void showStatistics(bool animation);
protected:
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void showEvent(QShowEvent* event) override;
	void initVirtKeyMap();
private:
	struct VirtualKeyInfo {
		QRect region;
		QString text;
		bool pressed = false;
		bool advancedDisplay = false;
		QColor textColor = Qt::white;
		QColor baseColor = QColor(0, 0, 0, 150);
 		QColor hoverdColor = QColor(0, 0, 0, 200);
		QColor pressedColor = QColor(100, 200, 100);
		std::function<void()> clickedCallback;
		QMap<QString, QString> meta;
	};
	int mBoundaryWidth = 8;
	QPoint mLastClickPos;
	bool bHovered = false;
	QMap<quint32, VirtualKeyInfo> mVirtKeyRectMap;
	QUserInputStatisticsWidget* mUserInputStatisticsWidget = nullptr;
};

#endif