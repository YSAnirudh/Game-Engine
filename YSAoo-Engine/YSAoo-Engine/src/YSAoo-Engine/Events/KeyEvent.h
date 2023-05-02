#pragma once
#include "YSApch.h"
#include "Event.h"

namespace YSAoo {

	class YSAoo_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard| EventCategoryInput)
	protected:
		KeyEvent(int KeyCode) : m_KeyCode(KeyCode) {}

		int m_KeyCode;
	};

	class YSAoo_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int KeyCode, int KeyRepeats) 
			: KeyEvent(KeyCode), m_KeyRepeats(KeyRepeats) {}

		inline int GetKeyRepeats() const {
			return m_KeyRepeats;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_KeyRepeats << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_KeyRepeats;
	};

	class YSAoo_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int KeyCode)
			: KeyEvent(KeyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}