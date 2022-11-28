#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2v1/lab_camera.h"
#include "lab_m1/Tema2v1/transform3D.h"



namespace m1
{
    class Tema2v1 : public gfxc::SimpleScene
    {
     public:
        Tema2v1();
        ~Tema2v1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        my_camera::Camera *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        float left, right, buttom, top;
        float fov;

        struct Segment
        {
            Segment(VertexFormat p1, VertexFormat p2) : p1(p1), p2(p2) {};
            VertexFormat p1, p2;
        };

        glm::ivec2 resolution;
        float translateX, translateY, translateZ;
        glm::mat4 modelMatrix;

        glm::mat4 rotateCarMatrix;
        glm::vec3 poz_obiect;
        //glm::vec3 poz_camera;

        glm::vector<VertexFormat> red_and_blue_vertices_track;
    };
}   // namespace m1
