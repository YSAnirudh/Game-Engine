#ifndef RENDERING_COMMONS_H
#define RENDERING_COMMONS_H

enum RENDERING_TECHNIQUE {
	FORWARD_RENDERING,
	DEFERRED_RENDERING,
	GBUFFER_RENDERING //Test case with 4 screens
};

const RENDERING_TECHNIQUE MAIN_RENDERING_TECHNIQUE = RENDERING_TECHNIQUE::FORWARD_RENDERING;

#endif