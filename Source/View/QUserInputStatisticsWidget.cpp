#include "QUserInputStatisticsWidget.h"
#include <QJsonObject>
#include <QSvgGenerator>
#include "Hook/SystemInputHook.h"

const int Spacing = 0;

QList<QColor> generateRandomColorList(int size) {
	static QList<QColor> Colors = {
		QColor(149, 162, 255),
		QColor(250, 128, 128),
		QColor(255, 192, 118),
		QColor(250, 231, 104),
		QColor(135, 232, 133),
		QColor(60, 185, 252),
		QColor(115, 171, 245),
		QColor(203, 155, 255),
		QColor(67, 67, 72),
		QColor(144, 237, 125),
		QColor(247, 163, 92),
		QColor(128, 133, 233)
	};

	QList<QColor> newColors;

	QColor prevColor;

	int randomIndex = rand() % Colors.size();
	newColors.append(Colors[randomIndex]);
	prevColor = Colors[randomIndex];

	for (int i = 1; i < size; ++i) {
		int newIndex = rand() % Colors.size();
		QColor newColor = Colors[newIndex];
		while (newColor == prevColor) {
			newIndex = rand() % Colors.size();
			newColor = Colors[newIndex];
		}
		newColors.append(newColor);
		prevColor = newColor;
	}

	return newColors;
}

QColor getRandomColor(int index) {

	static QList<QColor> Colors;
	if (Colors.size() <= index) {
		Colors = generateRandomColorList(qMin(128, index + 1));
	}
	return Colors[index];
}

UserInputStatistics operator+(const UserInputStatistics& a, const UserInputStatistics& b)
{
	UserInputStatistics mUserInputStatistics;
	mUserInputStatistics.keyUseTotalCount = a.keyUseTotalCount + b.keyUseTotalCount;
	mUserInputStatistics.mouseMoveDistance = a.mouseMoveDistance + b.mouseMoveDistance;

	for (const auto& item : a.keyUseCount.asKeyValueRange())
		mUserInputStatistics.keyUseCount[item.first] += item.second;
	for (const auto& item : b.keyUseCount.asKeyValueRange())
		mUserInputStatistics.keyUseCount[item.first] += item.second;

	for (const auto& item : a.keyUsePerHourCount.asKeyValueRange())
		mUserInputStatistics.keyUsePerHourCount[item.first] += item.second;
	for (const auto& item : b.keyUsePerHourCount.asKeyValueRange())
		mUserInputStatistics.keyUsePerHourCount[item.first] += item.second;

	return mUserInputStatistics;
}

UserInputStatistics UserInputStatistics::fromJsonObject(QJsonObject jsonObject)
{
	UserInputStatistics mUserInputStatistics;
	mUserInputStatistics.keyUseTotalCount = jsonObject["keyUseTotalCount"].toInteger();
	mUserInputStatistics.mouseMoveDistance = jsonObject["mouseMoveDistance"].toDouble();

	QJsonObject keyUseCountObject = jsonObject["keyUseCount"].toObject();
	for (auto key : keyUseCountObject.keys()) {
		mUserInputStatistics.keyUseCount[key] = keyUseCountObject[key].toInteger();
	}

	QJsonObject keyUsePerHourCountObject = jsonObject["keyUsePerHourCount"].toObject();
	for (auto key : keyUsePerHourCountObject.keys()) {
		mUserInputStatistics.keyUsePerHourCount[key] = keyUsePerHourCountObject[key].toInteger();
	}
	return mUserInputStatistics;
}

QJsonObject UserInputStatistics::toJsonObject()
{
	QJsonObject jsonObject;
	jsonObject["keyUseTotalCount"] = keyUseTotalCount;
	jsonObject["mouseMoveDistance"] = mouseMoveDistance;

	QJsonObject keyUseCountObject;
	for (auto item : keyUseCount.asKeyValueRange()) {
		keyUseCountObject[item.first] = item.second;
	}
	jsonObject["keyUseCount"] = keyUseCountObject;

	QJsonObject keyUsePerHourCountObject;
	for (auto item : keyUsePerHourCount.asKeyValueRange()) {
		keyUsePerHourCountObject[item.first] = item.second;
	}
	jsonObject["keyUsePerHourCount"] = keyUsePerHourCountObject;
	return jsonObject;
}


QUserInputStatisticsWidget::QUserInputStatisticsWidget()
{
	setWindowFlags(Qt::FramelessWindowHint | /*Qt::Tool |*/ Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	mTimer.setInterval(30);
	connect(&mTimer, &QTimer::timeout, this, &QUserInputStatisticsWidget::onUpdateAnimation);
}

float QUserInputStatisticsWidget::calcHeight(const UserInputStatistics& mUserInputStatistics)
{
	QFontMetrics metrics(QFont("Roboto", 7));
	const int rowHeight = metrics.height();
	return (Spacing + rowHeight) * (mUserInputStatistics.keyUseCount.size() + 1) / 2 + 20 + 100;
}

UserInputStatistics QUserInputStatisticsWidget::userInputStatistics() const
{
	return mUserInputStatistics;
}

void QUserInputStatisticsWidget::activate(UserInputStatistics statistics, QRect outerGeomtry, bool anmiation)
{
	mUserInputStatistics = statistics;
	mKeyUseCountMax = 0;
	mKeyUseCountList.clear();
	mKeyColorList.clear();
	for (const auto& item : mUserInputStatistics.keyUseCount.asKeyValueRange()) {
		if (!item.first.isEmpty()) {
			mKeyUseCountList << item;
			mKeyColorList << getRandomColor(mKeyUseCountList.size() - 1);
			mKeyUseCountMax = qMax(mKeyUseCountMax, item.second);
		}
	}
	std::sort(mKeyUseCountList.begin(), mKeyUseCountList.end(), [](const QPair<QString, qint64>& a, const QPair<QString, qint64>& b) {
		return SystemInputHook::getVkCodeByKeyName(a.first) < SystemInputHook::getVkCodeByKeyName(b.first);
	});
	QRect geom = QRect(0, 0, outerGeomtry.width(), calcHeight(mUserInputStatistics));
	geom.moveBottomLeft(outerGeomtry.topLeft());
	setGeometry(geom);
	show();
	if (anmiation) {
		mAnimator.restart();
		if (!mTimer.isActive()) {
			mTimer.start();
		}
	}
	else {
		update();
	}
}

void QUserInputStatisticsWidget::paintEvent(QPaintEvent* event)
{ 
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

	const int rowHeight = painter.fontMetrics().height();
	float progress = qBound(0.f, mAnimator.elapsed() / 500.0f, 1.f);
	float background = qBound(0.f, progress, 0.2f) * 5;
	painter.setOpacity(background);
	painter.fillRect(rect(), QColor(0, 0, 0, 150));

	painter.setFont(QFont("Roboto", 10, 100));
	painter.setPen(Qt::white);

	QRect title(0, 0, width(), 25);
	painter.drawText(title, Qt::AlignVCenter | Qt::AlignCenter, "MY COMPUTER CAREER");

	painter.setFont(QFont("Roboto", 7));
	QRect subtitle(0, 25, width(), 15);
	painter.setPen(QColor(220, 220, 220));
	painter.drawText(subtitle, Qt::AlignVCenter | Qt::AlignCenter, "nothing but enthusiasm brightens up the endless years.");

	for (int i = 0; i < mKeyUseCountList.size() / 2; i++) {
		QColor color = mKeyColorList[i];
		QRect rect(0, 0, 60, rowHeight);
		rect.moveTopLeft(QPoint(0, 50 + i * (rowHeight + Spacing)));
		painter.setPen(Qt::white);
		painter.drawText(rect, Qt::AlignVCenter | Qt::AlignRight, QString("%1").arg(mKeyUseCountList[i].first));
		rect.moveLeft(rect.right() + 10);
		rect.setRight(width() / 2 - 50);
		rect.setWidth(rect.width() * mKeyUseCountList[i].second / (float)mKeyUseCountMax * progress);
		painter.fillRect(rect.adjusted(0, 2, 0, -2), color);
		rect.moveLeft(rect.right() + 10);
		rect.setRight(width() / 2);
		painter.drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, QString("%1").arg(mKeyUseCountList[i].second));
	}
	for (int i = mKeyUseCountList.size() / 2; i < mKeyUseCountList.size(); i++) {
		QColor color = mKeyColorList[i];
		QRect rect(0, 0, 60, rowHeight);
		rect.moveTopLeft(QPoint(width() / 2, 50 + (i - mKeyUseCountList.size() / 2) * (rowHeight + Spacing)));
		painter.setPen(Qt::white);
		painter.drawText(rect, Qt::AlignVCenter | Qt::AlignRight, QString("%1").arg(mKeyUseCountList[i].first));
		rect.moveLeft(rect.right() + 10 );
		rect.setRight(width() - 50);
		rect.setWidth(rect.width() * mKeyUseCountList[i].second / (float)mKeyUseCountMax * progress);
		painter.fillRect(rect.adjusted(0, 2, 0, -2), color);
		rect.moveLeft(rect.right() + 10);
		rect.setRight(width());
		painter.drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, QString("%1").arg(mKeyUseCountList[i].second));
	}
}

void QUserInputStatisticsWidget::onUpdateAnimation()
{
	if (mAnimator.elapsed() > 500) {
		mTimer.stop();
	}
	update();
}

