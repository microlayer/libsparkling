/**
*
*/
/**
*
*/
#pragma once
#include <ISparkPBRMaterial.hpp>
class PBRLightCanvas : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    PBRLightCanvas(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        // Create SceneGraphManager3D                
        m_sceneGraphManager3D = device->createSceneGraphManager3D();
        
        // Material
        m_material = m_device->getRenderer()->createPBRMaterial();
        m_material->setAlbedo({ 1.0, 1.0, 1.0 });
        m_material->setRoughness(0.3f);
        m_material->setMetallic(0.3f);
        m_material->setAO(0.5f);
    }

    /**
    *
    */
    virtual ~PBRLightCanvas()
    {
        m_device->getLogger()->info("Deleting PBRLightCanvas");
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

    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager3D> m_sceneGraphManager3D;
    spark::SparkSharedPointer<spark::material::ISparkPBRMaterial> m_material;
};