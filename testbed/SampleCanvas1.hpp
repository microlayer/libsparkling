#include <mesh/generator/MeshGenerator.hpp>
#include "SparkSharedPointer.hpp"
#include "animator/NodeRotationAnimator.hpp"

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
        // Create SceneGraphManager3D
        m_sceneGraphManager3D = device->createSceneGraphManager3D();

        // Create Mesh
        spark::SparkSharedPointer<spark::mesh::ISparkMesh> cubeMesh(spark::mesh::MeshGenerator::createQuadMesh());

        // Create Animator
        spark::SparkSharedPointer<spark::animator::NodeRotationAnimator> nodeRotationAnimaror = new spark::animator::NodeRotationAnimator(spark::math::Vector3f(40, 50, 20));

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::ISparkSceneNode> node = new spark::scene::SceneNode();
        node->setPosition(spark::math::Vector3f(0, 0, 0));
        node->attachMesh(cubeMesh.get());
        node->addAnimator(nodeRotationAnimaror.get());

        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node.get());
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
        m_device->getLogger()->info("Init Canvas1");

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
        m_sceneGraphManager3D->drawGraph(renderer);
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
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager3D> m_sceneGraphManager3D;
};