/*
    DataTypeClass: DataTypeSchemaHeader

    Generated Source Code - please do not change this source code

    DataTypeCodeGenerator Version:
        OpcUaStackCore - 4.1.0

    Autor: Kai Huebl (kai@huebl-sgh.de)
*/

#include "OpcUaStackCore/StandardDataTypes/DataTypeSchemaHeader.h"

namespace OpcUaStackCore
{
    
    DataTypeSchemaHeader::DataTypeSchemaHeader(void)
    : Object()
    , ExtensionObjectBase()
    , namespaces_()
    , structureDataTypes_()
    , enumDataTypes_()
    , simpleDataTypes_()
    {
    }
    
    DataTypeSchemaHeader::~DataTypeSchemaHeader(void)
    {
    }
    
    OpcUaStringArray&
    DataTypeSchemaHeader::namespaces(void)
    {
        return namespaces_;
    }
    
    StructureDescriptionArray&
    DataTypeSchemaHeader::structureDataTypes(void)
    {
        return structureDataTypes_;
    }
    
    EnumDescriptionArray&
    DataTypeSchemaHeader::enumDataTypes(void)
    {
        return enumDataTypes_;
    }
    
    SimpleTypeDescriptionArray&
    DataTypeSchemaHeader::simpleDataTypes(void)
    {
        return simpleDataTypes_;
    }
    
    bool
    DataTypeSchemaHeader::operator==(const DataTypeSchemaHeader& value)
    {
        DataTypeSchemaHeader* dst = const_cast<DataTypeSchemaHeader*>(&value);
        if (namespaces_ != dst->namespaces()) return false;
        if (structureDataTypes_ != dst->structureDataTypes()) return false;
        if (enumDataTypes_ != dst->enumDataTypes()) return false;
        if (simpleDataTypes_ != dst->simpleDataTypes()) return false;
        return true;
    }
    
    bool
    DataTypeSchemaHeader::operator!=(const DataTypeSchemaHeader& value)
    {
        return !this->operator==(value);
    }
    
    void
    DataTypeSchemaHeader::copyTo(DataTypeSchemaHeader& value)
    {
        namespaces_.copyTo(value.namespaces());
        structureDataTypes_.copyTo(value.structureDataTypes());
        enumDataTypes_.copyTo(value.enumDataTypes());
        simpleDataTypes_.copyTo(value.simpleDataTypes());
    }
    
    DataTypeSchemaHeader&
    DataTypeSchemaHeader::operator=(const DataTypeSchemaHeader& value)
    {
        const_cast<DataTypeSchemaHeader*>(&value)->copyTo(*this);
        return *this;
    }
    
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    //
    // ExtensionObjectBase
    //
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    
    ExtensionObjectBase::SPtr
    DataTypeSchemaHeader::factory(void)
    {
    	return constructSPtr<DataTypeSchemaHeader>();
    }
    
    std::string
    DataTypeSchemaHeader::namespaceName(void)
    {
    	return "http://opcfoundation.org/UA/";
    }
    
    std::string
    DataTypeSchemaHeader::typeName(void)
    {
    	return "DataTypeSchemaHeader";
    }
    
    OpcUaNodeId
    DataTypeSchemaHeader::typeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15534,0);
    }
    
    OpcUaNodeId
    DataTypeSchemaHeader::binaryTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15676, 0);
    }
    
    OpcUaNodeId
    DataTypeSchemaHeader::xmlTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15950, 0);
    }
    
    OpcUaNodeId
    DataTypeSchemaHeader::jsonTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)16151, 0);
    }
    
    void
    DataTypeSchemaHeader::opcUaBinaryEncode(std::ostream& os) const
    {
        namespaces_.opcUaBinaryEncode(os);
        structureDataTypes_.opcUaBinaryEncode(os);
        enumDataTypes_.opcUaBinaryEncode(os);
        simpleDataTypes_.opcUaBinaryEncode(os);
    }
    
    void
    DataTypeSchemaHeader::opcUaBinaryDecode(std::istream& is)
    {
        namespaces_.opcUaBinaryDecode(is);
        structureDataTypes_.opcUaBinaryDecode(is);
        enumDataTypes_.opcUaBinaryDecode(is);
        simpleDataTypes_.opcUaBinaryDecode(is);
    }
    
    bool
    DataTypeSchemaHeader::encode(boost::property_tree::ptree& pt, Xmlns& xmlns) const
    {
    }
    
    bool
    DataTypeSchemaHeader::decode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
    }
    
    bool
    DataTypeSchemaHeader::xmlEncode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
        if (!xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair(element, elementTree));
        return true;
    }
    
    bool
    DataTypeSchemaHeader::xmlEncode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
    
        elementTree.clear();
        if (!namespaces_.xmlEncode(elementTree, "String", xmlns)) return false;
        pt.push_back(std::make_pair("Namespaces", elementTree));
    
        elementTree.clear();
        if (!structureDataTypes_.xmlEncode(elementTree, "StructureDescription", xmlns)) return false;
        pt.push_back(std::make_pair("StructureDataTypes", elementTree));
    
        elementTree.clear();
        if (!enumDataTypes_.xmlEncode(elementTree, "EnumDescription", xmlns)) return false;
        pt.push_back(std::make_pair("EnumDataTypes", elementTree));
    
        elementTree.clear();
        if (!simpleDataTypes_.xmlEncode(elementTree, "SimpleTypeDescription", xmlns)) return false;
        pt.push_back(std::make_pair("SimpleDataTypes", elementTree));
    
        return true;
    }
    
    bool
    DataTypeSchemaHeader::xmlDecode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree = pt.get_child_optional(element);
        if (!tree) return false;
        return xmlDecode(*tree, xmlns);
    }
    
    bool
    DataTypeSchemaHeader::xmlDecode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree;
    
        tree = pt.get_child_optional("Namespaces");
        if (!tree) return false;
        if (!namespaces_.xmlDecode(*tree, "String", xmlns)) return false;
    
        tree = pt.get_child_optional("StructureDataTypes");
        if (!tree) return false;
        if (!structureDataTypes_.xmlDecode(*tree, "StructureDescription", xmlns)) return false;
    
        tree = pt.get_child_optional("EnumDataTypes");
        if (!tree) return false;
        if (!enumDataTypes_.xmlDecode(*tree, "EnumDescription", xmlns)) return false;
    
        tree = pt.get_child_optional("SimpleDataTypes");
        if (!tree) return false;
        if (!simpleDataTypes_.xmlDecode(*tree, "SimpleTypeDescription", xmlns)) return false;
    
        return true;
    }
    
    bool
    DataTypeSchemaHeader::jsonEncode(boost::property_tree::ptree& pt, const std::string& element)
    {
        return true;
    }
    
    bool
    DataTypeSchemaHeader::jsonEncode(boost::property_tree::ptree& pt)
    {
        return true;
    }
    
    bool
    DataTypeSchemaHeader::jsonDecode(boost::property_tree::ptree& pt, const std::string& element)
    {
    }
    
    bool
    DataTypeSchemaHeader::jsonDecode(boost::property_tree::ptree& pt)
    {
    }
    
    void
    DataTypeSchemaHeader::copyTo(ExtensionObjectBase& extensionObjectBase)
    {
    	DataTypeSchemaHeader* dst = dynamic_cast<DataTypeSchemaHeader*>(&extensionObjectBase);
    	copyTo(*dst);
    }
    
    bool
    DataTypeSchemaHeader::equal(ExtensionObjectBase& extensionObjectBase) const
    {
    	DataTypeSchemaHeader* dst = dynamic_cast<DataTypeSchemaHeader*>(&extensionObjectBase);
    	return *const_cast<DataTypeSchemaHeader*>(this) == *dst;
    }
    
    void
    DataTypeSchemaHeader::out(std::ostream& os)
    {
        os << "Namespaces="; namespaces_.out(os);
        os << ", StructureDataTypes="; structureDataTypes_.out(os);
        os << ", EnumDataTypes="; enumDataTypes_.out(os);
        os << ", SimpleDataTypes="; simpleDataTypes_.out(os);
    }

}
