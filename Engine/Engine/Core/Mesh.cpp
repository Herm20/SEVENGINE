#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

bool Mesh::Load(MeshData* _data)
{
	// Creating the vectors as holders for the values
	vector<vec3> locations;
	vector<vec2> uvs;
	vector<vec3> normals;
	vector<VertInd> holder;

	// infile to read in the file that we pass in
	ifstream inFile;
	string line;

	inFile.open(objFile);

	if (inFile.is_open() == true)
	{
		// Reading in every line of the file
		while (getline(inFile, line))
		{
			istringstream object(line);
			string label;
			object >> label;

			// if statements to check the label
			if (label == "v")
			{
				float v1;
				float v2;
				float v3;

				object >> v1 >> v2 >> v3;

				vec3 newLoc = vec3(v1, v2, v3);

				locations.push_back(newLoc);
			}

			if (label == "vt")
			{
				float vt1;
				float vt2;

				object >> vt1 >> vt2;

				vec2 newUV = vec2(vt1, vt2);

				uvs.push_back(newUV);
			}

			if (label == "vn")
			{
				float vn1;
				float vn2;
				float vn3;

				object >> vn1 >> vn2 >> vn3;

				vec3 newNorms = vec3(vn1, vn2, vn3);

				normals.push_back(newNorms);
			}

			if (label == "f")
			{
				for (int i = 0; i < 3; i++)
				{
					unsigned int f1;
					unsigned int f2;
					unsigned int f3;
					char slash;
					char slash2;

					object >> f1 >> slash >> f2 >> slash2 >> f3;

					f1 -= 1;
					f2 -= 1;
					f3 -= 1;

					VertInd thing;
					thing.locInd = f1;
					thing.uvInd = f2;
					thing.normInd = f3;

					holder.push_back(thing);
				}
			}
		}
		inFile.close();
	}

	vertCount2 = holder.size();

	vector<Vertex> vertBufData(vertCount2);

	for (int i = 0; i < vertCount2; i++)
	{
		vertBufData[i] = { locations[holder[i].locInd],
							uvs[holder[i].uvInd],
							normals[holder[i].normInd] };
	}

	GLuint vertBuf;

	// Step 1
	glGenVertexArrays(1, &vertArr2);
	glGenBuffers(1, &vertBuf);

	// Step 2
	glBindVertexArray(vertArr2);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	// Step 3
	glBufferData(GL_ARRAY_BUFFER, // Where to copy to
		sizeof(Vertex)* vertCount2, // #bytes to copy
		&vertBufData[0], // Where to copy from
		GL_STATIC_DRAW); // "hint" to OpenGL

	// World Location
	glEnableVertexAttribArray(0); // Attribute index - 0

	glVertexAttribPointer(
		0,					// Attribute index - 0 in this case
		3,					// Number of components (x,y,z)
		GL_FLOAT,			// Type of data
		GL_FALSE,			// Should we normalize the data?
		sizeof(Vertex),		// Stride (bytes per vertex)
		0);	// Offset to this attribute

	// Uvs
	glEnableVertexAttribArray(1); // Attribute index - 1

	glVertexAttribPointer(
		1,					// Attribute index - 1 in this case
		2,					// Number of components (x,y)
		GL_FLOAT,			// Type of data
		GL_FALSE,			// Should we normalize the data?
		sizeof(Vertex),		// Stride (bytes per vertex)
		(void*)sizeof(vec3));	// Offset to this attribute


	// Normals
	glEnableVertexAttribArray(2); // Attribute index - 2

	glVertexAttribPointer(
		2,					// Attribute index - 0 in this case
		3,					// Number of components (x,y,z)
		GL_FLOAT,			// Type of data
		GL_FALSE,			// Should we normalize the data?
		sizeof(Vertex),		// Stride (bytes per vertex)
		(void*)(sizeof(vec3) + sizeof(vec2)));	// Offset to this attribute

	glBindVertexArray(0);	// unbind when finished editing

	return true;
}

void Mesh::Render(MeshData* _data)
{
	glBindVertexArray(vertArr2);
	glDrawArrays(GL_TRIANGLES, 0, vertCount2);
	glBindVertexArray(0);
}
