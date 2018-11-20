/*
    DataTypeClass: SemanticChangeStructureDataType

    Generated Source Code - please do not change this source code

    DataTypeCodeGenerator Version:
        OpcUaStackCore - 4.1.0

    Autor: Kai Huebl (kai@huebl-sgh.de)
*/

#include "OpcUaStackCore/StandardDataTypes/SemanticChangeStructureDataType.h"

namespace OpcUaStackCore
{
    
    SemanticChangeStructureDataType::SemanticChangeStructureDataType(void)
    : Object()
    , ExtensionObjectBase()
    , affected_()
    , affectedType_()
    {
    }
    
    SemanticChangeStructureDataType::~SemanticChangeStructureDataType(void)
    {
    }
    
    OpcUaNodeId&
    SemanticChangeStructureDataType::affected(void)
    {
        return affected_;
    }
    
    OpcUaNodeId&
    SemanticChangeStructureDataType::affectedType(void)
    {
        return affectedType_;
    }
    
    bool
    SemanticChangeStructureDataType::operator==(const SemanticChangeStructureDataType& value)
    {
        SemanticChangeStructureDataType* dst = const_cast<SemanticChangeStructureDataType*>(&value);
        if (affected_ != dst->affected()) return false;
        if (affectedType_ != dst->affectedType()) return false;
        return true;
    }
    
    bool
    SemanticChangeStructureDataType::operator!=(const SemanticChangeStructureDataType& value)
    {
        return !this->operator==(value);
    }
    
    void
    SemanticChangeStructureDataType::copyTo(SemanticChangeStructureDataType& value)
    {
        affected_.copyTo(value.affected());
        affectedType_.copyTo(value.affectedType());
    }
    
    SemanticChangeStructureDataType&
    SemanticChangeStructureDataType::operator=(const SemanticChangeStructureDataType& value)
    {
        const_cast<SemanticChangeStructureDataType*>(&value)->copyTo(*this);
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
    SemanticChangeStructureDataType::factory(void)
    {
    	return constructSPtr<SemanticChangeStructureDataType>();
    }
    
    std::string
    SemanticChangeStructureDataType::namespaceName(void)
    {
    	return "http://opcfoundation.org/UA/";
    }
    
    std::string
    SemanticChangeStructureDataType::typeName(void)
    {
    	return "SemanticChangeStructureDataType";
    }
    
    OpcUaNodeId
    SemanticChangeStructureDataType::typeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)897,0);
    }
    
    OpcUaNodeId
    SemanticChangeStructureDataType::binaryTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)899, 0);
    }
    
    OpcUaNodeId
    SemanticChangeStructureDataType::xmlTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)898, 0);
    }
    
    OpcUaNodeId
    SemanticChangeStructureDataType::jsonTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15374, 0);
    }
    
    void
    SemanticChangeStructureDataType::opcUaBinaryEncode(std::ostream& os) const
    {
        affected_.opcUaBinaryEncode(os);
        affectedType_.opcUaBinaryEncode(os);
    }
    
    void
    SemanticChangeStructureDataType::opcUaBinaryDecode(std::istream& is)
    {
        affected_.opcUaBinaryDecode(is);
        affectedType_.opcUaBinaryDecode(is);
    }
    
    bool
    SemanticChangeStructureDataType::encode(boost::property_tree::ptree& pt, Xmlns& xmlns) const
    {
    }
    
    bool
    SemanticChangeStructureDataType::decode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
    }
    
    bool
    SemanticChangeStructureDataType::xmlEncode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
        if (!xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair(element, elementTree));
        return true;
    }
    
    bool
    SemanticChangeStructureDataType::xmlEncode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
    
        elementTree.clear();
        if (!affected_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("Affected", elementTree));
    
        elementTree.clear();
        if (!affectedType_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("AffectedType", elementTree));
    
        return true;
    }
    
    bool
    SemanticChangeStructureDataType::xmlDecode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree = pt.get_child_optional(element);
        if (!tree) return false;
        return xmlDecode(*tree, xmlns);
    }
    
    bool
    SemanticChangeStructureDataType::xmlDecode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree;
    
        tree = pt.get_child_optional("Affected");
        if (!tree) return false;
        if (!affected_.xmlDecode(*tree, xmlns)) return false;
    
        tree = pt.get_child_optional("AffectedType");
        if (!tree) return false;
        if (!affectedType_.xmlDecode(*tree, xmlns)) return false;
    
        return true;
    }
    
    bool
    SemanticChangeStructureDataType::jsonEncode(boost::property_tree::ptree& pt, const std::string& element)
    {
        return true;
    }
    
    bool
    SemanticChangeStructureDataType::jsonEncode(boost::property_tree::ptree& pt)
    {
        return true;
    }
    
    bool
    SemanticChangeStructureDataType::jsonDecode(boost::property_tree::ptree& pt, const std::string& element)
    {
    }
    
    bool
    SemanticChangeStructureDataType::jsonDecode(boost::property_tree::ptree& pt)
    {
    }
    
    void
    SemanticChangeStructureDataType::copyTo(ExtensionObjectBase& extensionObjectBase)
    {
    	SemanticChangeStructureDataType* dst = dynamic_cast<SemanticChangeStructureDataType*>(&extensionObjectBase);
    	copyTo(*dst);
    }
    
    bool
    SemanticChangeStructureDataType::equal(ExtensionObjectBase& extensionObjectBase) const
    {
    	SemanticChangeStructureDataType* dst = dynamic_cast<SemanticChangeStructureDataType*>(&extensionObjectBase);
    	return *const_cast<SemanticChangeStructureDataType*>(this) == *dst;
    }
    
    void
    SemanticChangeStructureDataType::out(std::ostream& os)
    {
        os << "Affected="; affected_.out(os);
        os << ", AffectedType="; affectedType_.out(os);
    }

}
