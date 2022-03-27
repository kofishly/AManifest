#ifndef CFileEncodingDeclaration_hpp
#define CFileEncodingDeclaration_hpp

#include "CSegNode.h"
class CFileEncodingDeclaration :
    public CLineNode
{
    const string start_flag = "<?xml";
    const string end_flag = "?>";
public:
    // ��ʼ�����ݣ�����axml�ļ��ַ���������ȡ�ļ�������ص����ݣ�
    // ͬʱɾ��source_data�й����ļ����������
    void parse_file_encoding_declaration(string& content);
    
    void to_string();
};
#endif

