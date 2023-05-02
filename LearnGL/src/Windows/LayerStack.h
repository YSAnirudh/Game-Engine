#ifndef LAYER_STACK_H
#define LAYER_STACK_H

namespace YSAoo {
	class LayerStack
	{
		LayerStack();

		virtual void InitLayer();
		virtual void UpdateLayer();
		virtual void DrawLayer();

		~LayerStack();
	};
}

#endif