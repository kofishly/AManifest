//
//  CAXML.cpp
//  AXML
//
//  Created by 金陵小锦鲤 on 2022/3/19.
//

#include "CAXML.hpp"
int string_split_map(string source_string, string spacer, map<string, string>& key_values);

bool CAXML::FileEncodingDeclaration::init_data_string(string& source_data)
{
    int start = (int)source_data.find(start_flag);
    int end = (int)source_data.find(end_flag);
    
    if (start < 0 || end < 0) {
        return false;
    }
    
    string attribute = source_data.substr(start+start_flag.size()+strlen(" "), end - start-start_flag.size() -1);
    source_data = source_data.substr(end + end_flag.size());
    
    // 解析为map
    string_split_map(attribute, string(" "), content_map);
    return true;
}

bool CAXML::ManifestDeclaration::init_data_string(string& source_data)
{
    int start = (int)source_data.find(start_flag);
    int end_line = (int)source_data.find(declare_line_end_flag);
    if (end_line != -1 && start != -1)
    {
        // 提取数据
        string attribute = source_data.substr(start+start_flag.size(), end_line - start-start_flag.size());
        while (attribute.at(0) == ' ' )
        {
            attribute = attribute.substr(1);
        }
        while (attribute.at(attribute.size()-1) == ' ' )
        {
            attribute = attribute.substr(0, attribute.size()-1-1);
        }

        string_split_map(attribute, string(" "), get_attribute_map());
        // 去头
        source_data = source_data.substr(end_line + declare_line_end_flag.size());
        // 掐尾,保存内容
        string string_content = source_data.substr(0, source_data.find(end_flag));
        parse(&string_content);
        // 去除原数据中相关数据
        source_data = source_data.substr(source_data.find(end_flag) + end_flag.size());
        return true;
    }
    return false;
}

bool CAXML::ManifestDeclaration::parse(string* p_string_content)
{
    int index_start_flag = (int)p_string_content->find("<");
    while (index_start_flag > 0)
    {
        int index_line = (int)p_string_content->find("/>");
        int index_seg = (int)p_string_content->find(">");
        
        if (-1 == index_line && index_seg != -1)
        {
            return false;
        }
        
        if (index_line - index_seg > 0)
        {
            /**
             解析:
             <name>
             </name>
             */
            int end_attr = (int)p_string_content->find(">");
            string attr = p_string_content->substr(1, end_attr-1);
            
            // 内容数据去除属性
            *p_string_content = p_string_content->substr(end_attr+1);
            
            // 提取属性中的名字，可以知道是application、activity、service等
            string segment_name = attr.substr(0, attr.find(" "));
            // 属性去除已经解析的部分
            attr = attr.substr(attr.find(" ")+1);
            
            // 获取数据
            string end_sign = "</"+segment_name+">";
            int end_sign_lenth = (int)end_sign.size();
            int end_segment = (int)p_string_content->find(end_sign);
            
            string data = p_string_content->substr(0, end_segment);
            *p_string_content = p_string_content->substr(end_segment + end_sign_lenth);
            if (segment_name == "application")
            {
                // 一般情况下只含有一个application
                Applicaiton_Node* p_app_node = new Applicaiton_Node();
                // 解析
                p_app_node->set_name(segment_name);
                
                //p_app_node->string_content = data;
                
                p_app_node->param(attr, data);
                list_p_app_node.push_back(p_app_node);
            }
            else
            {
                Segment* p_segment = new Segment();
                // todo
                list_p_other_segment_node.push_back(p_segment);
            }
        }
        else if (index_seg - index_line > 0)
        {
            LineSegment* p_line_node = new LineSegment();
            
            // 取内容
            string line = p_string_content->substr(0, index_line);
            // 去除内容
            *p_string_content = p_string_content->substr(index_line);
            
            // 去除前无关内容
            line = line.substr(line.find("<"));
            
            //int left = (int)line.find("<");
            
            int right = (int)line.find(" ");
            string name = line.substr(1, right-1);
            p_line_node->set_name(name);
            
            // 截取数据
            string attr = line.substr(1 + name.size());
            while (attr.at(0) == ' ' )
            {
                attr = attr.substr(1);
            }
            while (attr.at(attr.size()-1) == ' ' )
            {
                attr = attr.substr(0, attr.size()-1-1);
            }
            
            string_split_map(attr, string(" "), p_line_node->get_attribute_map());
            list_p_line_declaration.push_back(p_line_node);
        }
        
        // 更新起始位置
        index_start_flag = (int)p_string_content->find("<");
        if (index_start_flag > 0) {
            *p_string_content = p_string_content->substr(index_start_flag);
        }
    }
    int i;
    while ((i = (int)p_string_content->find("\r")) >= 0) {
        *p_string_content = p_string_content->replace(i, 1, "");
    }
    while ((i = (int)p_string_content->find("\n")) >= 0) {
        *p_string_content = p_string_content->replace(i, 1, "");
    }
    while ((i = (int)p_string_content->find(" ")) >= 0) {
        *p_string_content = p_string_content->replace(i, 1, "");
    }
    if (p_string_content->length() > 0) {
        return false;
    }
    return true;
}

bool CAXML::Applicaiton_Node::init_data_string(string& source_data)
{
//    int start = (int)source_data.find(begin_string);
//    int end_line = (int)source_data.find(">");
//    if (end_line != -1 && start != -1)
//    {
//        data = source_data.substr(start+begin_string.size(), end_line - string(">").size() - start);
//        source_data = source_data.substr(end_line + string(">").size());
//        source_data = source_data.substr(0, source_data.find(end_flag));
//        return true;
//    }
    return false;
}

void CAXML::Applicaiton_Node::param(string attribute, string data_string)
{
    string_split_map(attribute, string(" "), attributes_map);
}

int string_split_map(string source_string, string spacer, map<string, string>& key_values)
{
    
    while (true) {
        int pos = (int)source_string.find(spacer);
        if (pos < 0 && source_string.length() <= 0) {
            break;
        }
        int pos_next = pos + (int)spacer.size();
        string tmp = source_string.substr(0, pos);
        source_string = source_string.substr(pos_next);
        int mid = (int)tmp.find("=");
        string s1 = tmp.substr(0, mid);
        string s2 = tmp.substr(mid+1);
        
        key_values.insert(std::pair<string, string>(s1, s2));
        if (tmp == source_string)
        {
            break;
        }
    }
    return (int)key_values.size();
}

void CAXML::append_xml_file(char* data)
{
    _axml_source_string.append(data);
}

bool CAXML::parse()
{
    if (!_encoding_declaration.init_data_string(_axml_source_string) || !_manifestDeclaration.init_data_string(_axml_source_string))
    {
        return false;
    }
    return true;
}

void CAXML::to_string()
{
    printf("文件编码信息：\r\n");
    _encoding_declaration.tostring();
    printf("----------------------------------------------\r\n");
    printf("Manifrst：\r\n");
    _manifestDeclaration.tostring();
    
    
    

}
