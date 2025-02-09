#ifndef QToast_h__
#define QToast_h__

#include <QWidget>
#include <QVector2D>

class QToast : public QWidget {
	Q_OBJECT
public:
	QToast(QString text, Qt::AlignmentFlag align = Qt::AlignCenter, float fadeOutTime = 2.0f, QVector2D spacing = QVector2D(0,0), bool alignToMouse = true, QWidget* parent = nullptr);

	void updateText(QString text);

	Qt::AlignmentFlag alignment() const;
	void setAlignment(Qt::AlignmentFlag val);

	QVector2D spacing() const;
	void setSpacing(QVector2D val);

	float fadeOutTime() const;
	void setFadeOutTime(float val);

	void fadeOut(bool immediate = false);
protected:
	void paintEvent(QPaintEvent* event) override;
	void showEvent(QShowEvent* event) override;
	void refreshGeomtry();
private:
	QString mText;
	QFont mFont;
	float mFadeOutTime = 2.0f;
	QVector2D mSpacing;
	Qt::AlignmentFlag mAlignment;
	bool mAlignToMouse;
};

#endif