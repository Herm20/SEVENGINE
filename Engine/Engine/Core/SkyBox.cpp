#include "SkyBox.h"

SkyBox::SkyBox()
{
}

SkyBox::SkyBox(AssetManager * assets)
{
	skyMesh = boost::shared_ptr<Mesh>(new Mesh(assets->GetMesh("box")));
	skyShaders = boost::shared_ptr<ShaderProgram>(new ShaderProgram(*assets->GetShaderProgram("sky")));
	
	glGenTextures(1, &skyTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyTextureID);
	
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, &assets->GetTexture("right"));
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, &assets->GetTexture("left"));
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, &assets->GetTexture("top"));
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, &assets->GetTexture("bottom"));
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, &assets->GetTexture("front"));
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, &assets->GetTexture("back"));

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SkyBox::Render(const CameraSystem * cam)
{
	glDepthMask(GL_FALSE);
	skyShaders->Use();
	glBindVertexArray(skyMesh->GetVertexArrayObject());
	glUniformMatrix4fv(glGetUniformLocation(skyShaders->GetProgram(), "cameraMatrix"), 1, GL_FALSE, &cam->cameraMatrix[0][0]);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyTextureID);

	for (u32 i = 0; i < skyMesh->GetSubMeshes()->GetIndAmountCount(); i++) {
		glDrawElements(
			GL_TRIANGLES,
			skyMesh->GetSubMeshes()->GetIndAmounts()[i],
			GL_UNSIGNED_INT,
			(const void*)(skyMesh->GetSubMeshes()->GetIndOffsets()[i] * sizeof(u32)));
	}
	glDepthMask(GL_TRUE);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

SkyBox::~SkyBox()
{
}
