#include "Engine.h"

bool Engine::_current_cs_set = false;
bool Engine::_current_vs_set = false;

CoordinateSystem* Engine::_current_cs = nullptr;
VectorSpace* Engine::_current_vs = nullptr;

void Engine::set_cs(CoordinateSystem* cs) {
	Engine::_current_cs = cs;
	Engine::_current_cs_set = true;
}

void Engine::set_vs(VectorSpace* vs) {
	Engine::_current_vs = vs;
	Engine::_current_vs_set = true;
}

CoordinateSystem* Engine::get_cs() {
	if (_current_cs_set) return Engine::_current_cs;
	else throw SceneException("There is no setted coordinate system");
}

VectorSpace* Engine::get_vs() {
	if (_current_vs_set) return Engine::_current_vs;
	else throw SceneException("There is no setted vector space");
}
