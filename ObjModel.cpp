#include "ObjModel.h"
#include <iostream>
ObjModel::ObjModel(string filename)
{
	vector<vec3> locations, normals;
	vector<vec2> uvs;
	vector<VertInd> indices;

	ifstream inFile(filename);
	string line;
	string label;
	if (inFile.good()) {
		while (getline(inFile, line)) {
			istringstream lineStream(line);
			lineStream >> label;
			if (label == "v") {
				vec3 v;
				lineStream >> v[0] >> v[1] >> v[2];
				locations.push_back(v);
			} 
			else if (label == "vt") {
				vec2 vt;
				lineStream >> vt[0] >> vt[1];
				uvs.push_back(vt);
			}
			else if (label == "vn") {
				vec3 vn;
				lineStream >> vn[0] >> vn[1] >> vn[2];
				normals.push_back(vn);
			}
			else if (label == "f") {
				char slash;
				unsigned int loc, uv, norm;
				for (int i = 0; i < 3; i++) {
					lineStream >> loc >> slash >> uv >> slash >> norm;
					indices.push_back({ loc, uv, norm });
				}
			}
		}
		vector<Vertex> vertBufData;
		float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

		for (auto& loc : locations) {
			minX = min(minX, loc.x);
			minY = min(minY, loc.y);
			minZ = min(minZ, loc.z);

			maxX = max(maxX, loc.x);
			maxY = max(maxY, loc.y);
			maxZ = max(maxZ, loc.z);
		}

		for (auto& loc : locations) {
			loc.x /= (maxX - minX);
			loc.y /= (maxY - minY);
			loc.z /= (maxZ - minZ);
		}



		for (unsigned int i = 0; i < indices.size(); i++) {
			unsigned int locInd = indices[i].locInd;
			unsigned int uvInd = indices[i].uvInd;
			unsigned int normInd = indices[i].normInd;
			vertBufData.push_back( {
				locations[indices[i].locInd - 1],
				uvs[indices[i].uvInd - 1],
				normals[indices[i].normInd - 1]
			});
		}

		vertCount = vertBufData.size();
		glGenVertexArrays(1, &vertArr);
		glGenBuffers(1, &vertBuf);

		glBindVertexArray(vertArr);
		glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
		glBufferData(GL_ARRAY_BUFFER,   // Where to copy to
			sizeof(Vertex) * vertCount,   // # bytes to copy
			&vertBufData[0],           // Where to copy from
			GL_STATIC_DRAW);	      // “hint” to OpenGL

		glEnableVertexAttribArray(0); // Attribute index – 0
		glVertexAttribPointer(
			0,			// Attribute index – 0 in this case
			3,			// Number of components (x, y, z)
			GL_FLOAT,	// Type of data
			GL_FALSE,	// Should we normalize the data?
			sizeof(Vertex),	// Stride (Bytes between attributes)
			0);		// Offset to this attribute
		glEnableVertexAttribArray(1); // Attribute index – 1

		glVertexAttribPointer(
			1,			// Attribute index – 1 in this case
			2,			// Number of components (x, y, z)
			GL_FLOAT,	// Type of data
			GL_FALSE,	// Should we normalize the data?
			sizeof(Vertex),	// Stride (Bytes between attributes)
			(void*)sizeof(vec3));		// Offset to this attribute

		glEnableVertexAttribArray(2); // Attribute index – 1
		glVertexAttribPointer(
			2,			// Attribute index – 1 in this case
			3,			// Number of components (x, y, z)
			GL_FLOAT,	// Type of data
			GL_FALSE,	// Should we normalize the data?
			sizeof(Vertex),	// Stride (Bytes between attributes)
			(void*)(sizeof(vec3) + sizeof(vec2)));		// Offset to this attribute

	}
	else {
		cout << "Couldn't load the file";
	}
}

ObjModel::~ObjModel()
{
}


