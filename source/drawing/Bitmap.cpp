#include "drawing/Bitmap.hpp"

namespace spark {
    namespace drawing {
        /**
        *
        */
        Bitmap::Bitmap(uc8_t* stream, uint32_t width, uint32_t height, spark::drawing::E_PIXEL_FORMAT pixelFormat, std::string hash) :
            m_stream(stream),
            m_width(width),
            m_height(height),
            m_pixelFormat(pixelFormat),
            m_hash(hash)
        {
            if (spark::drawing::E_RGBA8 == pixelFormat)
            {
                m_rawSize = 4 * m_width * m_height;
            }

            if (spark::drawing::E_GRAY8 == pixelFormat)
            {
                m_rawSize = m_width * m_height;
            }

            m_stream = new uc8_t[m_rawSize];
            memcpy(m_stream, stream, m_rawSize);
        }

        /**
        *
        */
        Bitmap::~Bitmap(void)
        {
            delete m_stream;
        }

        /**
        * Gets the raw byte stream of the image
        */
        uc8_t* Bitmap::getImageAsStream() const
        {
            return m_stream;
        }

        /**
        * Gets the width of the image in pixel
        */
        uint32_t Bitmap::getWidth() const
        {
            return m_width;
        }

        /**
        * Gets the height of the image in pixel
        */
        uint32_t Bitmap::getHeight() const
        {
            return m_height;
        }

        /**
        * Gets the bitmap format for stream
        */
        spark::drawing::E_PIXEL_FORMAT Bitmap::getPixelFormat() const
        {
            return m_pixelFormat;
        }

        /**
        * Gets the calculated hash value of the raw image stream data
        */
        std::string Bitmap::getHash() const
        {
            return m_hash;
        }
    } // end namespace drawing
} // end namespace spark
