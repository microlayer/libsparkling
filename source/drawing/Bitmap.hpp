#ifndef __SPARK_DRAWING_BITMAP_HPP_INCLUDED__
#define __SPARK_DRAWING_BITMAP_HPP_INCLUDED__

#include "ISparkImage.hpp"
#include "spark/SparkTypes.hpp"
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "PixelFormat.hpp"
#include "ISparkTexture.hpp"

namespace spark {
    namespace drawing {
        /**
        * Encapsulates pixel data and attributes for a image
        */
        class Bitmap : public ISparkImage
        {
        public:
            Bitmap(uc8_t* stream, uint32_t width, uint32_t height, spark::drawing::E_PIXEL_FORMAT pixelFormat, std::string hash);
            virtual ~Bitmap(void);

        public: // ISparkImage
            uc8_t* getImageAsStream() const;
            uint32_t getWidth() const;
            uint32_t getHeight() const;
            spark::drawing::E_PIXEL_FORMAT getPixelFormat() const;
            std::string getHash() const;
            void setTexture(spark::renderer::ISparkTexture* texture);

        private:
            uc8_t* m_stream;
            uint32_t m_width;
            uint32_t m_height;
            uint32_t m_rawSize;
            spark::drawing::E_PIXEL_FORMAT m_pixelFormat;
            std::string m_hash;
            spark::renderer::ISparkTexture* m_texture;
        };
    } // end namespace drawing
} // end namespace spark
#endif
