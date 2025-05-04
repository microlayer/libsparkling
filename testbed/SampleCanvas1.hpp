#include "file/FileSystem.hpp"
#include <mesh/generator/MeshGenerator.hpp>
#include "SparkSharedPointer.hpp"
#include <math/Matrix4.hpp>
#include "animator/NodeRotationAnimator.hpp"
#include "scene/SceneNode.hpp"
#include "game/TiledLayer.hpp"
#include "game/Sprite.hpp"
#include "scene/SceneGraphManager2D.hpp"

//#define SAMPLE_2D

/**
*
*/
class SampleCanvas1 : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    SampleCanvas1(spark::device::ISparkDevice* device) :
        m_device(device)
    {

#ifdef SAMPLE_2D
        m_fileSystem = device->getFileSystem();
        m_image = m_fileSystem->loadBitmap("texture1.png");
        m_playerImage = m_fileSystem->loadBitmap("ghost1.png");
        m_explosionImage = m_fileSystem->loadBitmap("explosion.png");
        m_tiledLayer = m_fileSystem->loadTiledLayer("tiles4x4_32_v1-11.tmx");

        m_playerSprite = m_device->createSprite(m_playerImage.get());
        m_explosionSprite = m_device->createSprite(m_explosionImage.get());

        // Setup TiledLayer
        m_tiledLayer->setPosition(250, 50);

        // Setup Sprite
        m_playerSprite->setPosition(50, 300);
        m_explosionSprite->setPosition(100, 100);
        m_explosionSprite->startAnimation();
        m_explosionSprite->setAnimationDetails(100, 25, 25);
#else
        // Create SceneGraphManager3D
        m_sceneGraphManager3D = device->createSceneGraphManager3D();

        // Create Mesh
        spark::SparkSharedPointer<spark::mesh::ISparkMesh> cubeMesh(spark::mesh::MeshGenerator::createQuadMesh());

        // Create Animator
        spark::SparkSharedPointer<spark::animator::NodeRotationAnimator> nodeRotationAnimaror = new spark::animator::NodeRotationAnimator(spark::math::Vector3f(40, 50, 20));

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::ISparkSceneNode> node = new spark::scene::SceneNode();
        node->setPosition(spark::math::Vector3f(0, 0, 10));
        node->attachMesh(cubeMesh.get());
        node->addAnimator(nodeRotationAnimaror.get());

        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node.get());
#endif        
    }

    /**
    *
    */
    virtual ~SampleCanvas1()
    {

    }

    /**
    *
    */
    void init()
    {
        // Set virtual resolution
        spark::perspective::OrthographicProjection orthographicProjection(m_device->getScreenResolution().m_width, m_device->getScreenResolution().m_height);
        orthographicProjection.setVirtualResolution(1196, 720, spark::perspective::VirtualResolution::E_LETTER_OR_PILLARBOX);
        m_device->getRenderer()->setOrthographicProjectionMatrix(orthographicProjection);
    }

    /**
    *
    */
    void paint(spark::renderer::ISparkRenderer* renderer)
    {
#ifdef SAMPLE_2D
        renderer->draw2DLine(0, 0, 1196, 720, spark::drawing::Color(0, 255, 0, 255));
        renderer->draw2DBitmap(m_image.get(), 100, 10);
        m_tiledLayer->paint(renderer);
        renderer->drawString(spark::font::ESFT_ARIAL_16, "Hello libsparkling", spark::drawing::Color(128, 128, 128, 128), 400, 25);

        m_playerSprite->paint(renderer);

        m_explosionSprite->paint(renderer);
#else
        m_sceneGraphManager3D->drawGraph(renderer);
#endif
    }

    /**
    *
    */
    void onKeyPressed(int key, int action)
    {
        m_device->getLogger()->info("onKeyPressed");
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::file::ISparkFileSystem* m_fileSystem;
    spark::SparkSharedPointer<spark::drawing::ISparkImage> m_image;
    spark::SparkSharedPointer<spark::drawing::ISparkImage> m_playerImage;
    spark::SparkSharedPointer<spark::drawing::ISparkImage> m_explosionImage;
    spark::SparkSharedPointer<spark::game::ISparkSprite> m_playerSprite;
    spark::SparkSharedPointer<spark::game::ISparkSprite> m_explosionSprite;
    spark::SparkSharedPointer<spark::game::ISparkTiledLayer> m_tiledLayer;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager3D> m_sceneGraphManager3D;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager2D> m_sceneGraphManager2D;
};