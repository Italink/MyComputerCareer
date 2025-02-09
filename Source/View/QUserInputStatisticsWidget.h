#ifndef QUserInputStatisticsWidget_h__
#define QUserInputStatisticsWidget_h__

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QElapsedTimer>

struct UserInputStatistics {
	QMap<QString, qint64> keyUseCount;
	QMap<QString, qint64> keyUsePerHourCount;
	qint64 keyUseTotalCount = 0;
	double mouseMoveDistance = 0.0;
	static UserInputStatistics fromJsonObject(QJsonObject json);
	QJsonObject toJsonObject();
};

UserInputStatistics operator+(const UserInputStatistics& a, const UserInputStatistics& b);

class QUserInputStatisticsWidget : public QWidget {
public:
	QUserInputStatisticsWidget();
	static float calcHeight(const UserInputStatistics& statistics);
	UserInputStatistics userInputStatistics() const;
	void activate(UserInputStatistics statistics, QRect outerGeomtry, bool anmiation = true);
protected:
	void paintEvent(QPaintEvent* event) override;
	void onUpdateAnimation();
private:
	UserInputStatistics mUserInputStatistics;
	QList<QPair<QString, qint64>> mKeyUseCountList;
	QList<QColor> mKeyColorList;
	int mKeyUseCountMax = 0;
	QTimer mTimer;
	QElapsedTimer mAnimator;
};

#endif