#ifndef CFileEncodingDeclaration_hpp
#define CFileEncodingDeclaration_hpp

#include "CSegNode.h"
class CFileEncodingDeclaration :
    public CLineNode
{
    const string start_flag = "<?xml";
    const string end_flag = "?>";
public:
    // 初始化数据，传入axml文件字符串，会提取文件编码相关的内容，
    // 同时删除source_data中关于文件编码的内容
    void parse_file_encoding_declaration(string& content);
    
    void to_string();
};
#endif

