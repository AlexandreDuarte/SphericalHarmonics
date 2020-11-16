#pragma once

#include"shader_s.h"
#include<vector>
#include<complex>
#include"camera.h"
#include"cSphericalHarmonics.h"

class Engine
{
public:
	


public:
	Engine();
	~Engine();

public:
	Camera* camera;
	bool start;
	double rotation;
	double v_rotation;
	int l, m;
	bool b_rotation;
	bool b_change_lm;
	unsigned int *VBO, *VAO, *EBO;
	int active_draw;
	cSphericalHarmonics::points_array* points;

public:
	void init_shader();
	void render(double*, double);

public:
	void create_points();
	//void generate_points(Engine::points_array* ,int, int, int);
	void processInput(GLFWwindow* window, double*);
};

