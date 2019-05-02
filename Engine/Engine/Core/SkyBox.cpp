#include "SkyBox.h"

SkyBox::SkyBox()
{
}

SkyBox::SkyBox(AssetManager * assets)
{
	skyMesh = boost::shared_ptr<Mesh>(new Mesh(assets->GetMesh("box")));
	skyShaders = boost::shared_ptr<ShaderProgram>(new ShaderProgram(*assets->GetShaderProgram("sky")));
}

void SkyBox::Render(CameraSystem * cam)
{
	glDepthMask(GL_FALSE);
	skyShaders->Use();
	glBindVertexArray(skyMesh->GetVertexArrayObject());
	glUniformMatrix4fv(glGetUniformLocation(skyShaders->GetProgram(), "cameraMatrix"), 1, GL_FALSE, &cam->cameraMatrix[0][0]);
	
	//TODO: Bind skybox texture before attempting to draw

	for (u32 i = 0; i < skyMesh->GetSubMeshes()->GetIndAmountCount(); i++) {
		glDrawElements(
			GL_TRIANGLES,
			skyMesh->GetSubMeshes()->GetIndAmounts()[i],
			GL_UNSIGNED_INT,
			(const void*)(skyMesh->GetSubMeshes()->GetIndOffsets()[i] * sizeof(u32)));
	}
	glDepthMask(GL_TRUE);
	/*
	// Example texture binding
	material->GetDiffuseTexture()->bind(0);
	glUniform1i(glGetUniformLocation(material->GetShaderProgram()->GetProgram(), "diffuse"), 0);
	*/
}

SkyBox::~SkyBox()
{
}
