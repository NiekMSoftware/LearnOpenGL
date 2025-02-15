#pragma once

class Shader {
public:
	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	
	// use/active the shader
	void use();

	// utlity uniform functions

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

public:
	// the program ID
	unsigned int ID;
};