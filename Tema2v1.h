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
        struct Car
        {
            //Car(glm::vector<glm::vec3> trajectory, int indice_last_point, float fractiune_npc) : trajectory(trajectory), indice_last_point(indice_last_point), fractiune_npc(fractiune_npc) {};
            
            glm::vector<glm::vec3> trajectory;
            int indice_last_point;
            float fractiune_npc;
        };

        glm::ivec2 resolution;
        float translateX, translateY, translateZ;
        glm::mat4 modelMatrix;

        glm::mat4 rotateCarMatrix;
        glm::vec3 poz_obiect;
        //glm::vec3 poz_camera;
        float fractiune_npc;
        int indice_last_point_npc;
        glm::vector<glm::vec3> points_npc_car;
        glm::vector<glm::vec3> points_npc_car2;
        glm::vector<glm::vec3> points_npc_cars[2];
        glm::vector<VertexFormat> red_and_blue_vertices_track;
        glm::vector<glm::vec3> positions_trees;
        Car cars_npc[2];
        float cameraSpeed;
        glm::vec3 median;
        float scaleCar;
        float scaleRoad;
        float yCar;
        float YCamera;
        float yTrunk;
        float yLeaves;
        float scaleZTrunk;
        float scaleTree;
        
    };
}   // namespace m1
