#include "file/FileSystem.hpp"
#include "scene/SceneGraphManager3D.hpp"
#include "scene/SceneNode.hpp"
#include <mesh/generator/MeshGenerator.hpp>
#include "SparkSharedPointer.hpp"

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

        // Create SceneGraphManager3D
        m_sceneGraphManager3D = device->createSceneGraphManager3D();

        // Create Mesh
        spark::SparkSharedPointer<spark::mesh::ISparkMesh> cubeMesh(spark::mesh::MeshGenerator::createQuadMesh());

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::ISparkSceneNode> node = new spark::scene::SceneNode();
        node->setPosition(spark::math::Vector3f(0, 1, 0));
        node->attachMesh(cubeMesh.get());

        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node.get());

        // Set virtual resolution
        spark::perspective::OrthographicProjection orthographicProjection(device->getScreenResolution().m_width, device->getScreenResolution().m_height);
        orthographicProjection.setVirtualResolution(1196, 720, spark::perspective::VirtualResolution::E_LETTER_OR_PILLARBOX);
        device->getRenderer()->setOrthographicProjection(orthographicProjection);
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
        renderer->draw2DLine(0, 0, 1196, 720, spark::drawing::Color(0, 255, 0, 255));
        //renderer->draw2DBitmap(m_image, 10, 10);
        m_sceneGraphManager3D->drawGraph(renderer);
    }

private:
    spark::file::ISparkFileSystem* m_fileSystem;
    spark::drawing::ISparkImage* m_image;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager3D> m_sceneGraphManager3D;
};