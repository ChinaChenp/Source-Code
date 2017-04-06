#include "base64.h"
#include <iostream>

int main() {
  const std::string s =
    "René Nyffenegger\n"
    "http://www.renenyffenegger.ch\n"
    "passion for data\n"
    "平哥 百度 阿里\n"
    "Base64编码要求把3个8位字节（3*8=24）转化为4个6位的字节（4*6=24），之后在6位的前面补两个0，形成8位一个字节的形式。 如果剩下的字符不足3个字节，则用0填充，输出字符使用'='，因此编码后输出的文本末尾可能会出现1或2个'='。"
    "为了保证所输出的编码位可读字符，Base64制定了一个编码表，以便进行统一转换。编码表的大小为2^6=64，这也是Base64名称的由来。";

  std::string encoded = base64::base64_encode(s.c_str(), s.length());
  std::string decoded = base64::base64_decode(encoded);

  std::cout << "encoded: " << std::endl << encoded << std::endl << std::endl;
  std::cout << "decoded: " << std::endl << decoded << std::endl;

  return 0;
}
