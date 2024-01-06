#include "MLBase64.hpp"

namespace spark {
	namespace mlstl {
		namespace base64 {

			/// <summary>
			/// 
			/// </summary>
			std::string MLBase64::Encode(uc8_t* bytesToEncodeToBase64, int length)
			{
				uc8_t src[3];
				uc8_t target[4];

				std::string result;

				for (int i = 0; i < length; i += 3)
				{
					src[0] = (length >(i + 0)) ? bytesToEncodeToBase64[i + 0] : 0;
					src[1] = (length > (i + 1)) ? bytesToEncodeToBase64[i + 1] : 0;
					src[2] = (length > (i + 2)) ? bytesToEncodeToBase64[i + 2] : 0;

					// First 6 bits from src[0]
					target[0] = (src[0] & 252) >> 2;
					// Last 2 bits from src[0] plus first 4 bits from src[1]
					target[1] = ((src[0] & 0x03) << 4) + ((src[1] & 240) >> 4);
					// Last 4 bits from src[1] plus first 2 bits from src[2]
					target[2] = ((src[1] & 15) << 2) + ((src[2] & 192) >> 6);
					// Last 6 bits from src[2]
					target[3] = (src[2] & 63);

					bool last = ((i + 3) >= length) ? true : false;

					int s = 3 - (length % 3);

					result.push_back(GetBase64Chars()[target[0]]);
					result.push_back(GetBase64Chars()[target[1]]);
					result.push_back((last && (s == 2) && (target[2] == 0)) ? CHAR_PAD : GetBase64Chars()[target[2]]);
					result.push_back((last && (s == 1 || s == 2) && (target[3] == 0)) ? CHAR_PAD : GetBase64Chars()[target[3]]);
				}

				return result;
			}

			/// <summary>
			/// 
			/// </summary>
			std::vector<uc8_t> MLBase64::Decode(std::string base64EncodedString)
			{
				uc8_t src[4];
				uc8_t target[3];

				int length = base64EncodedString.size();

				std::unordered_map<char, uint32_t> hashtableCharToBase64Pos;

				for (int i = 0; i < GetBase64Chars().size(); i++)
				{
					std::pair<c8_t, int> pair(GetBase64Chars()[i], i);
					hashtableCharToBase64Pos.insert(pair);
				}

				std::vector<uc8_t> bytes;

				// we need 4 base64 chars to get at least 1 byte out 
				if (length >= 4)
				{
					for (int i = 0; i < length; i += 4)
					{
						uint32_t pos0 = hashtableCharToBase64Pos.at(base64EncodedString[i + 0]);
						uint32_t pos1 = hashtableCharToBase64Pos.at(base64EncodedString[i + 1]);
						uint32_t pos2 = hashtableCharToBase64Pos.at(base64EncodedString[i + 2]);
						uint32_t pos3 = hashtableCharToBase64Pos.at(base64EncodedString[i + 3]);
						
						src[0] = (pos0 == 64) ? 0 : pos0;
						src[1] = (pos1 == 64) ? 0 : pos1;
						src[2] = (pos2 == 64) ? 0 : pos2;
						src[3] = (pos3 == 64) ? 0 : pos3;

						target[0] = (src[0] << 2) + ((src[1] & 0x30) >> 4);
						target[1] = ((src[1] & 0xf) << 4) + ((src[2] & 0x3c) >> 2);
						target[2] = ((src[2] & 0x3) << 6) + src[3];

						bool last = ((i + 4) % length) == 0 ? true : false;

						if (!last)
						{
							bytes.push_back(target[0]);
							bytes.push_back(target[1]);
							bytes.push_back(target[2]);
						}
						else
						{
							bool third = base64EncodedString[i + 3] == CHAR_PAD ? false : true;
							bool sec = base64EncodedString[i + 2] == CHAR_PAD ? false : true;

							bytes.push_back(target[0]);
							if (sec) bytes.push_back(target[1]);
							if (third) bytes.push_back(target[2]);
						}
					}
				}

				return bytes;
			}

			/// <summary>
			/// 
			/// </summary>
			std::string MLBase64::GetBase64Chars()
			{
				return std::string(
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					"abcdefghijklmnopqrstuvwxyz"
					"0123456789+/=");
			}
		} // end namespace base64
	} // end namespace mlstl
} // end namespace spark