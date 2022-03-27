//
//  main.cpp
//  AXML
//
//  Created by 金陵小锦鲤 on 2022/3/19.
//
#include <stdio.h>
#include "CAXML.hpp"
int main(int argc, const char * argv[])
{
    char buff[1024];
    string source_data = "";
    int read_bytes = 0;
    FILE* manifest = fopen("/Users/koifishly/Desktop/bdv5/input/AndroidManifest.xml", "rb");
    CAXML axml;
    while(true)
    {
        read_bytes = (int)fread(buff, 1, 1023, manifest);
        if (read_bytes <= 0) {
            break;
        }
        buff[read_bytes] = 0;
        axml.append_xml_file(buff);
    }
    axml.parse();
    axml.to_string();
    return 0;
}
