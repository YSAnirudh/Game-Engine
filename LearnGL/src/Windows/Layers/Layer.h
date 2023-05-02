#ifndef LAYER_H
#define LAYER_H

#include <string>

namespace YSAoo {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent() {}

		inline const std::string& GetName() { return DebugName; }

		virtual ~Layer();
	protected:
		std::string DebugName;
	};
}

#endif