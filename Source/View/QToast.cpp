#include "QToast.h"
#include <QPainter>
#include <QTimer>
#include <QCursor>

QToast::QToast(QString text, Qt::AlignmentFlag align, float fadeOutTime, QVector2D spacing, bool alignToMouse, QWidget* parent /*= nullptr*/)
	: mText(text)
	, mAlignment(align)
	, mFadeOutTime(fadeOutTime)
	, mSpacing(spacing)
	, mAlignToMouse(alignToMouse)
	, mFont("Arial", 12)
{
	this->setAttribute(Qt::WA_TransparentForMouseEvents);
	this->setWindowFlag(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground);
}

void QToast::updateText(QString text)
{
	mText = text;
	refreshGeomtry();
}

Qt::AlignmentFlag QToast::alignment() const
{
	return mAlignment;
}

void QToast::setAlignment(Qt::AlignmentFlag val)
{
	mAlignment = val;
	refreshGeomtry();
}

QVector2D QToast::spacing() const
{
	return mSpacing;
}

void QToast::setSpacing(QVector2D val)
{
	mSpacing = val;
	refreshGeomtry();
}

float QToast::fadeOutTime() const
{
	return mFadeOutTime;
}

void QToast::setFadeOutTime(float val)
{
	mFadeOutTime = val;
	refreshGeomtry();
}

void QToast::fadeOut(bool immediate)
{
	if (immediate) {
		this->deleteLater();
	}
	else {
		QTimer::singleShot(mFadeOutTime * 1000.f, [this]() {
			this->deleteLater();
		});
	}
}

void QToast::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setFont(mFont);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

	painter.fillRect(rect(), Qt::green);
	painter.drawText(rect(), Qt::AlignCenter, mText);
}

void QToast::showEvent(QShowEvent* event)
{
	QWidget::showEvent(event);
	refreshGeomtry();
}

void QToast::refreshGeomtry()
{
	QPainter painter(this);
	QFontMetrics metrics(mFont);
	int textWidth = metrics.horizontalAdvance(mText);
	int textHeight = metrics.height();
	QRect geomtry(0, 0, textWidth + 100, textHeight + 50);

	if (mAlignToMouse) {
		geomtry.moveCenter(QCursor::pos());
	}
	this->setGeometry(geomtry);
}

