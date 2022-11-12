#pragma once
#include <cmath>
#include <string>
#include <vector>

namespace nk125 {
	class xorCrypt {
	public:
		static std::vector<unsigned char> strToUcv(const std::string& s) {
			return std::vector<unsigned char>(s.begin(), s.end());
		}

		static std::string ucvToStr(const std::vector<unsigned char>& v) {
			return std::string(v.begin(), v.end());
		}

		static std::vector<unsigned char> transform(std::vector<unsigned char> data, std::vector<unsigned char> pass) {
			size_t dLen = data.size(), pLen = pass.size(), offset = 0, pOffset = 0;

			if (!pLen || !dLen) {
				throw std::exception("The password and the plaintext can't be empty");
				return {};
			}

			std::vector<unsigned char> rData = data;

			auto cryptPacket = [&](size_t len) {
				for (size_t i = 0; i < len; i++) {
					rData[offset++] ^= pass[pOffset++];

					if (pOffset >= pLen) pOffset = 0;
				}
			};

			if (dLen > pLen) {
				for (size_t i = 0; i < trunc(dLen / pLen); i++) {
					cryptPacket(pLen);
				}
			}

			cryptPacket(dLen % pLen);

			return rData;
		}
	};
}