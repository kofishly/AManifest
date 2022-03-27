//
//  CAXML.hpp
//  AXML
//
//  Created by 金陵小锦鲤 on 2022/3/19.
//

#ifndef CAXML_hpp
#define CAXML_hpp

#include <stdio.h>
#include <string>
#include <list>
#include <map>

using std::string;
using std::list;
using std::map;

#define RST_INTERVAL_NOT_END    -1
#define RST_INTERVAL_END        0
#define RST_INTERVAL_SIZE_OUT   -2
class CAXML {
    
    class Segment
    {
    public:
        string name;
        string attributes;
        string data;
    };
    
    class LineSegment
    {
        string name;
        map<string, string> attribute_map;
    public:
        void set_name(string n){name = n;}
        map<string, string>& get_attribute_map(){return attribute_map;}
        void tostring(){
            printf("++ %s  ", name.c_str());
            map<string, string>::iterator it_bg = attribute_map.begin();
            map<string, string>::iterator it_ed = attribute_map.end();
            while (it_bg != it_ed)
            {
                printf("属性[%s][%s]\r\n", (*it_bg).first.c_str(), (*it_bg).second.c_str());
                it_bg++;
            }
        }
    };
    
    class Applicaiton_Node
    {
        const string begin_string = "<application";
        const string end_flag = "</application>";
        string name;
        map<string, string> attributes_map;
        
    public:
        string string_content;
        bool init_data_string(string& source_data);
        void set_name(string nam){
            name = nam;
        }
        map<string, string>& get_attribute_map(){
            return this->attributes_map;
        }
        void param(string attribute, string data_string);
        void tostring(){
            map<string, string>::iterator it_bg = attributes_map.begin();
            map<string, string>::iterator it_ed = attributes_map.end();
            printf("Applicaion 相关信息：");
            while (it_bg != it_ed)
            {
                printf("属性:[%s][%s]\r\n", (*it_bg).first.c_str(), (*it_bg).second.c_str());
                it_bg++;
            }
            printf("------------------------------------------------------------------\r\n");
        }
    };
    
    /**
     文件编码声明类
     <?xml version="1.0" encoding="utf-8" standalone="no"?>
     */
    class FileEncodingDeclaration
    {
        const string start_flag = "<?xml";
        const string end_flag = "?>";
        map<string, string> content_map;
    public:
        // 初始化数据，传入axml文件字符串，会提取文件编码相关的内容，
        // 同时删除source_data中关于文件编码的内容
        bool init_data_string(string& source_data);
        map<string, string>& get_kv_map() {return content_map;}
        void tostring(){
            map<string, string>::iterator it_bg = content_map.begin();
            map<string, string>::iterator it_ed = content_map.end();
            while (it_bg != it_ed)
            {
                printf("%s : %s \r\n", (*it_bg).first.c_str(), (*it_bg).second.c_str());
                it_bg++;
            }
        }
    };
    
    class ManifestDeclaration
    {
        const string start_flag = "<manifest";
        const string declare_line_end_flag = ">";
        const string end_flag = "</manifest>";
        map<string, string> attribute_map;
        list<Applicaiton_Node*> list_p_app_node;
        list<Segment*> list_p_other_segment_node;
        list<LineSegment*> list_p_line_declaration;
    public:
        bool init_data_string(string& source_data);
        bool parse(string* p_string_content);
        list<Applicaiton_Node*>* get_application_node(){return &list_p_app_node;}
        list<Segment*>* get_other_segment(){return &list_p_other_segment_node;}
        list<LineSegment*>* get_line_declare(){return &list_p_line_declaration;}
        map<string, string>& get_attribute_map(){return attribute_map;}
        void tostring()
        {
            // 打印属性信息
            map<string, string>::iterator it_bg = attribute_map.begin();
            map<string, string>::iterator it_ed = attribute_map.end();
            
            list<Applicaiton_Node*>* p_app_node = get_application_node();
            list<Segment*>* p_other_node = get_other_segment();
            list<LineSegment*>* p_m_line_node = get_line_declare();
            
            while (it_bg != it_ed)
            {
                printf("属性：[%s][%s]\r\n", (*it_bg).first.c_str(), (*it_bg).second.c_str());
                it_bg++;
            }
            printf("%d 处application声明信息。\r\n", (int)p_app_node->size());
            printf("%d 处其他段节点声明信息。\r\n", (int)p_other_node->size());
            printf("%d 处行声明信息。\r\n", (int)p_m_line_node->size());
            printf("------------------------------------------------------------------\r\n");
            //printf("属性：%s\r\n", attribute.c_str());
            list<LineSegment*>::iterator it_line_bg = p_m_line_node->begin();
            list<LineSegment*>::iterator it_line_ed = p_m_line_node->end();
            for (; it_line_bg != it_line_ed; it_line_bg++) {
                LineSegment* node = *it_line_bg;
                node->tostring();
            }
            printf("------------------------------------------------------------------\r\n");
            list<Applicaiton_Node*>::iterator app_it_bg = list_p_app_node.begin();
            list<Applicaiton_Node*>::iterator app_it_ed = list_p_app_node.end();
            for (; app_it_ed != app_it_bg; app_it_bg++) {
                Applicaiton_Node* node = *app_it_bg;
                node->tostring();
            }
        }
        
    };
    
    string _axml_source_string;
    FileEncodingDeclaration _encoding_declaration;
    ManifestDeclaration _manifestDeclaration;
    
    
public:
    void append_xml_file(char* data);
    bool parse();
    void to_string();
};

#endif /* CAXML_hpp */
