//
//  CAXML.hpp
//  AXML
//
//  Created by 金陵小锦鲤 on 2022/3/19.
//

#ifndef CAXML_hpp
#define CAXML_hpp

#include "CFileEncodingDeclaration.h"
#include "CSegNode.h"
class CAXML :
    public CSegNode
{
    CFileEncodingDeclaration file_encoding_declaration;
public:
    void parse_encoding(string& content);
    void to_string();
};

#endif
