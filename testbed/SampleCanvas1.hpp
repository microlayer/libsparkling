#include "file/FileSystem.hpp"

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
        if (m_image != NULL) m_image->release();
    }

    /**
    *
    */
    void paint(spark::renderer::ISparkRenderer* renderer)
    {
        renderer->draw2DLine(0, 0, 1196, 720, spark::drawing::Color(0, 255, 0, 255));
        //renderer->draw2DBitmap(m_image, 10, 10);
    }
private:
    spark::file::ISparkFileSystem* m_fileSystem;
    spark::drawing::ISparkImage* m_image;
};