/**
*
*/
#pragma once
class ShadowMapCanvas : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    ShadowMapCanvas(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        // Create SceneGraphManager3D                
        m_sceneGraphManager3D = device->createSceneGraphManager3D();
    }

    /**
    *
    */
    virtual ~ShadowMapCanvas()
    {
        m_device->getLogger()->info("Deleting ShadowMapCanvas");
    }

    /**
    *
    */
    void init()
    {
    }

    /**
    *
    */
    void paint(spark::renderer::ISparkRenderer* renderer)
    {
        m_sceneGraphManager3D->drawGraph(renderer);
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager3D> m_sceneGraphManager3D;
};