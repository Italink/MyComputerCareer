#ifndef SystemInputHook_h__
#define SystemInputHook_h__

#include <QObject>
#include <QMouseEvent>
#include <QSharedPointer>

struct MinimizedInputEvent
{
	QEvent::Type type;
	qint64 timestamp;
};

struct MinimizedInputEvent_Mouse :public MinimizedInputEvent {
	Qt::MouseButton button;
	QPoint position;
};

struct MinimizedInputEvent_Keyboard :public MinimizedInputEvent {
	quint32 vkCode;
	Qt::KeyboardModifiers modifiers;
};

class SystemInputHook{
public:
	using KeyboardEventCallback = std::function<void(const MinimizedInputEvent_Keyboard&)>;
	using MouseEventCallback = std::function<void(const MinimizedInputEvent_Mouse&)>;

	static SystemInputHook* Instance();

	virtual void startup(KeyboardEventCallback keyboardCallback, MouseEventCallback mouseCallback);
	virtual void shutdown();

	void invokeKeyboardEvent(const MinimizedInputEvent_Keyboard& event);
	void invokeMouseEvent(const MinimizedInputEvent_Mouse& event);

	static QString getShortKeyNameByVkCode(int vk);
	static QString getKeyNameByVkCode(int vk);
	static int getVkCodeByKeyName(QString keyName);
	static QMap<int, QString> VkCodeToKeyName;
	static QMap<int, QString> VkCodeToShortKeyName;
protected:
	std::function<void(const MinimizedInputEvent_Keyboard& event)> mKeyboardEventCallback;
	std::function<void(const MinimizedInputEvent_Mouse& event)> mMouseEventCallback;
	
};

#endif // SystemInputHook_h__
