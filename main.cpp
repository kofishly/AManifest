//
//  main.cpp
//  AXML
//
//  Created by 金陵小锦鲤 on 2022/3/19.
//
#include "CAXML.hpp"
int main(int argc, const char * argv[])
{
    char buff[1024];
    string source_data = "";
    int read_bytes = 0;
    FILE* manifest = fopen("C:\\Users\\koifishly\\Desktop\\AndroidManifest.xml", "rb");
    //FILE* manifest = fopen("/Users/koifishly/Desktop/bdv5/input/AndroidManifest.xml", "rb");
    CAXML axml;
    string data;
    while(true)
    {
        read_bytes = (int)fread(buff, 1, 1023, manifest);
        if (read_bytes <= 0) {
            break;
        }
        buff[read_bytes] = 0;
        //axml.append_xml_file(buff);
        data.append(buff);
    }
    axml.parse_encoding(data);
    axml.parse_inner_data(data, axml.get_line_node_list(), axml.get_seg_node_list());
    axml.to_string();
    //((CSegNode)axml).parse_inner_data(data, axml.get_line_node_list(), axml.get_seg_node_list());
    //((CSegNode)axml).to_string("");
    return 0;
}
