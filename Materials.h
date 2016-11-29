#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#ifndef __MATERIAL__
#define __MATERIAL__

namespace Material {

	const GLint NofMaterials = 24;

	const GLchar * const MaterialName[24] = {
		"Emerald","Jade","Obsidian","Perl","Ruby","Turquoise","Brass","Bronze","Chrome","Copper","Gold","Silver","Black Plastic","Cyan Plastic","Green Plastic",
		"Red Plastic","White Plastic","Yellow Plastic","Black Rubber","Cyan Rubber", "Green Rubber","Red Rubber","White Rubber","Yellow Rubber"
	};
	const GLfloat AmbientR[NofMaterials] = {
		0.0215f,0.135f,0.05375f,0.25f,0.1745f,0.1f,
		0.329412f,0.2125f,0.25f,0.19125f,0.24725f,0.19225f,
		0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		0.02f,0.0f,0.0f,0.05f,0.05f,0.05f };
	const GLfloat AmbientG[NofMaterials] = {
		0.1745f,0.2225f,0.05f,0.20725f,0.01175f,0.18725f,
		0.223529f,0.1275f,0.25f,0.0735f,0.1995f,0.19225f,
		0.0f,0.1f,0.0f,0.0f,0.0f,0.0f,
		0.02f,0.05f,0.05f,0.0f,0.05f,0.05f
	};
	const GLfloat AmbientB[NofMaterials] = {
		0.0215f,0.1575f,0.06625f,0.20725f,0.01175f,0.1745f,
		0.027451f,0.054f,0.25f,0.0225f,0.0745f,0.19225f,
		0.0f,0.06f,0.0f,0.0f,0.0f,0.0f,
		0.02f,0.05f,0.0f,0.0f,0.05f,0.0f
	};
	const GLfloat DiffuseR[NofMaterials] = {
		0.07568f,0.51f,0.18275f,1.0f,0.61424f,0.396f,
		0.780392f,0.714f,0.4f,0.7038f,0.75164f,0.50754f,
		0.01f,0.0f,0.1f,0.5f,0.55f,0.5f,
		0.01f,0.4f,0.4f,0.5f,0.5f,0.5f
	};
	const GLfloat DiffuseG[NofMaterials] = {
		0.61424f,0.89f,0.17f,0.829f,0.04136f,0.74151f,
		0.568627f,0.4284f,0.4f,0.27048f,0.60648f,0.50754f,
		0.01f,0.50980392f,0.35f,0.0f,0.55f,0.5f,
		0.01f,0.5f,0.5f,0.4f,0.5f,0.5f
	};
	const GLfloat DiffuseB[NofMaterials] = {
		0.07568f,0.63f,0.22525f,0.829f,0.04136f,0.69102f,
		0.113725f,0.18144f,0.4f,0.0828f,0.22648f,0.50754f,
		0.01f,0.50980392f,0.35f,0.0f,0.55f,0.5f,
		0.01f,0.5f,0.5f,0.4f,0.5f,0.5f
	};
	const GLfloat SpecularR[NofMaterials] = {
		0.633f,0.316228f,0.332741f,0.296648f,0.727811f,0.297254f,
		0.992157f,0.393548f,0.774597f,0.256777f,0.628281f,0.508273f,
		0.50f,0.50196078f,0.45f,0.7f,0.70f,0.60f,
		0.4f,0.04f,0.04f,0.7f,0.7f,0.7f

	};
	const GLfloat SpecularG[NofMaterials] = {
		0.727811f,0.316228f,0.328634f,0.296648f,0.727811f,0.297254f,
		0.992157f,0.393548f,0.774597f,0.256777f,0.628281f,0.508273f,
		0.50f,0.50196078f,0.55f,0.6f,0.70f,0.60f,
		0.4f,0.7f,0.7f,0.04f,0.7f,0.7f
	};
	const GLfloat SpecularB[NofMaterials] = {
		0.633f,0.316228f,0.346435f,0.296648f,0.626959f,0.306678f,
		0.807843f,0.166721f,0.774597f,0.086014f,0.366065f,0.508273f,
		0.50f,0.50196078f,0.45f,0.6f,0.70f,0.50f,
		0.4f,0.7f,0.04f,0.04f,0.7f,0.04f
	};
	const GLfloat Shininess[NofMaterials] = {
		0.6f,0.1f,0.3f,0.888f,0.6f,0.1f,
		0.21794872f,0.2f,0.6f,0.1f,0.4f,0.4f,
		0.25f,0.25f,0.25f,0.25f,0.25f,0.25f,
		0.078125f,0.078125f,0.078125f,0.078125f,0.078125f,0.078125,
	};
}
#endif