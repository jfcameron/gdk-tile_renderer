// © 2020 Joseph Cameron - All Rights Reserved

#include <cstdlib>
#include <memory>

#include <gdk/tile_renderer.h>

#include <jfc/glfw_window.h>

#include <gdk/graphics_context.h>
#include <gdk/scene.h>

#include <GLFW/glfw3.h>

using namespace gdk;

//// //// //// //// //// ////

class tile_renderer
{
public:
    using attribute_array_type = std::vector<float>;

private:

public:
    tile_renderer(std::shared_ptr<graphics::context>);
};

class my_tile_renderer
{

};

tile_renderer::tile_renderer(std::shared_ptr<graphics::context> aContext)
{
    //create_tile
    {
    }
}

//// //// //// //// //// ////

int main(int count, char **args)
{
    glfw_window window("tile renderer demo");

    auto pContext = std::shared_ptr<graphics::context>(std::move(
        graphics::context::make(graphics::context::implementation::opengl_webgl1_gles2)));
    
    auto pScene = pContext->make_scene();

    auto pCamera = std::shared_ptr<gdk::camera>(std::move(pContext->make_camera()));
    pScene->add_camera(pCamera);

    tile_renderer t(pContext);

//////////////////////////////////////////////////////////////////
    //{
        using attribute_array_type = std::vector<float>;

        attribute_array_type position{
            1, 1, 0,
            0, 1, 0,
            0, 0, 0,
            1, 1, 0,
            0, 0, 0,
            1, 0, 0,
        };

        attribute_array_type uv{
            1, 0,
            0, 0,
            0, 1,
            1, 0,
            0, 1,
            1, 1,
        };
        
        auto pUserModel = std::shared_ptr<model>(std::move(
            pContext->make_model({vertex_data_view::UsageHint::Static,
            {
                { 
                    "a_Position",
                    {
                        &position.front(),
                        position.size(),
                        3
                    }
                },
                { 
                    "a_UV",
                    {
                        &uv.front(),
                        uv.size(),
                        2
                    }
                }
            }})));

        std::vector<std::underlying_type<std::byte>::type> imageData({ // raw rgba data
            0x00, 0xff, 0xff, 0xff,                                    
            0xff, 0xff, 0xff, 0xff,                                    
            0xff, 0xff, 0xff, 0xff,
            0x00, 0x00, 0x00, 0xff
        });
    
        texture::image_data_2d_view view;
        view.width = 2;
        view.height = 2;
        view.format = texture::data_format::rgba;
        view.data = reinterpret_cast<std::byte *>(&imageData.front());

        auto pTexture = std::shared_ptr<texture>(std::move(pContext->make_texture(view)));

        auto pAlpha = pContext->get_alpha_cutoff_shader();

        auto pMaterial = std::shared_ptr<material>(std::move(pContext->make_material(pAlpha)));

        // Uniforms must be explicitly set; all defaults are zero
        pMaterial->setTexture("_Texture", pTexture);
        pMaterial->setVector2("_UVScale", { 1, 1 });
        pMaterial->setVector2("_UVOffset", { 0, 0 });

        auto pEntity = std::shared_ptr<entity>(std::move(pContext->make_entity(pUserModel, pMaterial)));

        pEntity->set_model_matrix(Vector3<float>{0., 0., -1.}, Quaternion<float>());

        pScene->add_entity(pEntity);

    //}
//////////////////////////////////////////////////////////////////
    
    for (float deltaTime(0); !window.shouldClose();)
    {
        pScene->draw(window.getWindowSize());

        glfwPollEvents();
        
        window.swapBuffer(); 
    }

    return EXIT_SUCCESS;
}

