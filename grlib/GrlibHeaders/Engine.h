#pragma once
#include "SceneException.h"

class VectorSpace;
class CoordinateSystem;

class Engine {
public:
	static void set_cs(CoordinateSystem* cs);
	static void set_vs(VectorSpace* vs);

	static CoordinateSystem* get_cs();
	static VectorSpace* get_vs();

private:
	static CoordinateSystem* _current_cs;
	static VectorSpace* _current_vs;

	static bool _current_cs_set;
	static bool _current_vs_set;
};