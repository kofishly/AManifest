#include "CFileEncodingDeclaration.h"

void CFileEncodingDeclaration::parse_file_encoding_declaration(string& content)
{
    int start = (int)content.find(start_flag);
    int end_line = (int)content.find(end_flag);
    if (end_line != -1 && start != -1)
    {
        // 提取数据
        string line = content.substr(start+start_flag.size(), end_line - (start+start_flag.size()));
        while (line.at(0) == ' ')
        {
            line = line.substr(1);
        }
        while (line.at(line.size() - 1) == ' ')
        {
            line = line.substr(0, line.size() - 1 - 1);
        }

        parse_attribute(line, this->get_attribute_map_ref());
        // 去除原数据中相关数据
        content = content.substr(end_line + end_flag.size());
    }
}

void CFileEncodingDeclaration::to_string()
{
    printf("%s", start_flag.c_str());
    map<string, string>::iterator it_bg = get_attribute_map_ref().begin();
    map<string, string>::iterator it_ed = get_attribute_map_ref().end();
    while (it_bg != it_ed)
    {
        printf(" %s=%s", (*it_bg).first.c_str(), (*it_bg).second.c_str());
        it_bg++;
    }
    printf("%s\r\n", end_flag.c_str());
}
