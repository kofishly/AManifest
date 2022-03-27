#include "CAXML.hpp"
//
//  CAXML.cpp
//  AXML
//
//  Created by 金陵小锦鲤 on 2022/3/19.
//

void CAXML::parse_encoding(string& content)
{
    file_encoding_declaration.parse_file_encoding_declaration(content);
}

void CAXML::to_string()
{
    file_encoding_declaration.to_string();

    list<CLineNode*>::iterator ln_bg = get_line_node_list().begin();
    list<CLineNode*>::iterator ln_ed = get_line_node_list().end();
    for (; ln_bg != ln_ed; ln_bg++)
    {
        (*ln_bg)->to_string("");
    }

    list<CSegNode*>::iterator sn_bg = get_seg_node_list().begin();
    list<CSegNode*>::iterator sn_ed = get_seg_node_list().end();
    for (; sn_bg != sn_ed; sn_bg++)
    {
        (*sn_bg)->to_string("");
    }
}