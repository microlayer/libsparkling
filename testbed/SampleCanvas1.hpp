#include "file/FileSystem.hpp"
#include <mesh/generator/MeshGenerator.hpp>
#include "SparkSharedPointer.hpp"
#include <math/Matrix4.hpp>
#include "animator/NodeRotationAnimator.hpp"
#include "scene/SceneNode.hpp"
#include "game/TiledLayer.hpp"

/**
*
*/
class SampleCanvas1 : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    SampleCanvas1(spark::device::ISparkDevice* device)
    {
        m_fileSystem = device->getFileSystem();
        //m_image = m_fileSystem->loadBitmap("texture1.png");
        //m_tiledLayer = m_fileSystem->loadTiledLayer("tiles4x4.tmx");

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

        // Set virtual resolution
        //spark::perspective::OrthographicProjection orthographicProjection(device->getScreenResolution().m_width, device->getScreenResolution().m_height);
        //orthographicProjection.setVirtualResolution(1196, 720, spark::perspective::VirtualResolution::E_LETTER_OR_PILLARBOX);
        //device->getRenderer()->setOrthographicProjection(orthographicProjection);        
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
    void paint(spark::renderer::ISparkRenderer* renderer)
    {
        //renderer->draw2DLine(0, 0, 1196, 720, spark::drawing::Color(0, 255, 0, 255));
        //renderer->draw2DBitmap(m_image.get(), 100, 10);
        //m_tiledLayer->paint(renderer);

        m_sceneGraphManager3D->drawGraph(renderer);
    }

private:
    spark::file::ISparkFileSystem* m_fileSystem;
    //spark::SparkSharedPointer<spark::drawing::ISparkImage> m_image;
    //spark::SparkSharedPointer<spark::game::TiledLayer> m_tiledLayer;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager3D> m_sceneGraphManager3D;
};