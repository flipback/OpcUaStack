/*
    DataTypeClass: DataSetMetaDataType

    Generated Source Code - please do not change this source code

    DataTypeCodeGenerator Version:
        OpcUaStackCore - 4.1.0

    Autor: Kai Huebl (kai@huebl-sgh.de)
*/

#include "OpcUaStackCore/StandardDataTypes/DataSetMetaDataType.h"

namespace OpcUaStackCore
{
    
    DataSetMetaDataType::DataSetMetaDataType(void)
    : DataTypeSchemaHeader()
    , name_()
    , description_()
    , fields_()
    , dataSetClassId_()
    , configurationVersion_()
    {
    }
    
    DataSetMetaDataType::~DataSetMetaDataType(void)
    {
    }
    
    OpcUaString&
    DataSetMetaDataType::name(void)
    {
        return name_;
    }
    
    OpcUaLocalizedText&
    DataSetMetaDataType::description(void)
    {
        return description_;
    }
    
    FieldMetaDataArray&
    DataSetMetaDataType::fields(void)
    {
        return fields_;
    }
    
    OpcUaGuid&
    DataSetMetaDataType::dataSetClassId(void)
    {
        return dataSetClassId_;
    }
    
    ConfigurationVersionDataType&
    DataSetMetaDataType::configurationVersion(void)
    {
        return configurationVersion_;
    }
    
    bool
    DataSetMetaDataType::operator==(const DataSetMetaDataType& value)
    {
        DataSetMetaDataType* dst = const_cast<DataSetMetaDataType*>(&value);
        if (name_ != dst->name()) return false;
        if (description_ != dst->description()) return false;
        if (fields_ != dst->fields()) return false;
        if (dataSetClassId_ != dst->dataSetClassId()) return false;
        if (configurationVersion_ != dst->configurationVersion()) return false;
        return true;
    }
    
    bool
    DataSetMetaDataType::operator!=(const DataSetMetaDataType& value)
    {
        return !this->operator==(value);
    }
    
    void
    DataSetMetaDataType::copyTo(DataSetMetaDataType& value)
    {
        name_.copyTo(value.name());
        description_.copyTo(value.description());
        fields_.copyTo(value.fields());
        dataSetClassId_.copyTo(value.dataSetClassId());
        configurationVersion_.copyTo(value.configurationVersion());
    }
    
    DataSetMetaDataType&
    DataSetMetaDataType::operator=(const DataSetMetaDataType& value)
    {
        const_cast<DataSetMetaDataType*>(&value)->copyTo(*this);
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
    DataSetMetaDataType::factory(void)
    {
    	return constructSPtr<DataSetMetaDataType>();
    }
    
    std::string
    DataSetMetaDataType::namespaceName(void)
    {
    	return "http://opcfoundation.org/UA/";
    }
    
    std::string
    DataSetMetaDataType::typeName(void)
    {
    	return "DataSetMetaDataType";
    }
    
    OpcUaNodeId
    DataSetMetaDataType::typeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)14523,0);
    }
    
    OpcUaNodeId
    DataSetMetaDataType::binaryTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)124, 0);
    }
    
    OpcUaNodeId
    DataSetMetaDataType::xmlTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)14794, 0);
    }
    
    OpcUaNodeId
    DataSetMetaDataType::jsonTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15050, 0);
    }
    
    void
    DataSetMetaDataType::opcUaBinaryEncode(std::ostream& os) const
    {
        name_.opcUaBinaryEncode(os);
        description_.opcUaBinaryEncode(os);
        fields_.opcUaBinaryEncode(os);
        dataSetClassId_.opcUaBinaryEncode(os);
        configurationVersion_.opcUaBinaryEncode(os);
    }
    
    void
    DataSetMetaDataType::opcUaBinaryDecode(std::istream& is)
    {
        name_.opcUaBinaryDecode(is);
        description_.opcUaBinaryDecode(is);
        fields_.opcUaBinaryDecode(is);
        dataSetClassId_.opcUaBinaryDecode(is);
        configurationVersion_.opcUaBinaryDecode(is);
    }
    
    bool
    DataSetMetaDataType::encode(boost::property_tree::ptree& pt, Xmlns& xmlns) const
    {
    }
    
    bool
    DataSetMetaDataType::decode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
    }
    
    bool
    DataSetMetaDataType::xmlEncode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
        if (!xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair(element, elementTree));
        return true;
    }
    
    bool
    DataSetMetaDataType::xmlEncode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
    
        elementTree.clear();
        if (!name_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("Name", elementTree));
    
        elementTree.clear();
        if (!description_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("Description", elementTree));
    
        elementTree.clear();
        if (!fields_.xmlEncode(elementTree, "FieldMetaData", xmlns)) return false;
        pt.push_back(std::make_pair("Fields", elementTree));
    
        elementTree.clear();
        if (!dataSetClassId_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("DataSetClassId", elementTree));
    
        elementTree.clear();
        if (!configurationVersion_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("ConfigurationVersion", elementTree));
    
        return true;
    }
    
    bool
    DataSetMetaDataType::xmlDecode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree = pt.get_child_optional(element);
        if (!tree) return false;
        return xmlDecode(*tree, xmlns);
    }
    
    bool
    DataSetMetaDataType::xmlDecode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree;
    
        tree = pt.get_child_optional("Name");
        if (!tree) return false;
        if (!name_.xmlDecode(*tree, xmlns)) return false;
    
        tree = pt.get_child_optional("Description");
        if (!tree) return false;
        if (!description_.xmlDecode(*tree, xmlns)) return false;
    
        tree = pt.get_child_optional("Fields");
        if (!tree) return false;
        if (!fields_.xmlDecode(*tree, "FieldMetaData", xmlns)) return false;
    
        tree = pt.get_child_optional("DataSetClassId");
        if (!tree) return false;
        if (!dataSetClassId_.xmlDecode(*tree, xmlns)) return false;
    
        tree = pt.get_child_optional("ConfigurationVersion");
        if (!tree) return false;
        if (!configurationVersion_.xmlDecode(*tree, xmlns)) return false;
    
        return true;
    }
    
    bool
    DataSetMetaDataType::jsonEncode(boost::property_tree::ptree& pt, const std::string& element)
    {
        return true;
    }
    
    bool
    DataSetMetaDataType::jsonEncode(boost::property_tree::ptree& pt)
    {
        return true;
    }
    
    bool
    DataSetMetaDataType::jsonDecode(boost::property_tree::ptree& pt, const std::string& element)
    {
    }
    
    bool
    DataSetMetaDataType::jsonDecode(boost::property_tree::ptree& pt)
    {
    }
    
    void
    DataSetMetaDataType::copyTo(ExtensionObjectBase& extensionObjectBase)
    {
    	DataSetMetaDataType* dst = dynamic_cast<DataSetMetaDataType*>(&extensionObjectBase);
    	copyTo(*dst);
    }
    
    bool
    DataSetMetaDataType::equal(ExtensionObjectBase& extensionObjectBase) const
    {
    	DataSetMetaDataType* dst = dynamic_cast<DataSetMetaDataType*>(&extensionObjectBase);
    	return *const_cast<DataSetMetaDataType*>(this) == *dst;
    }
    
    void
    DataSetMetaDataType::out(std::ostream& os)
    {
        os << "Name="; name_.out(os);
        os << ", Description="; description_.out(os);
        os << ", Fields="; fields_.out(os);
        os << ", DataSetClassId="; dataSetClassId_.out(os);
        os << ", ConfigurationVersion="; configurationVersion_.out(os);
    }

}
