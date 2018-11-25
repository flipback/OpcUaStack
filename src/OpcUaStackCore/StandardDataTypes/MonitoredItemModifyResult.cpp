/*
    DataTypeClass: MonitoredItemModifyResult

    Generated Source Code - please do not change this source code

    DataTypeCodeGenerator Version:
        OpcUaStackCore - 4.1.0

    Autor: Kai Huebl (kai@huebl-sgh.de)
*/

#include "OpcUaStackCore/StandardDataTypes/MonitoredItemModifyResult.h"

namespace OpcUaStackCore
{
    
    MonitoredItemModifyResult::MonitoredItemModifyResult(void)
    : Object()
    , ExtensionObjectBase()
    , statusCode_()
    , revisedSamplingInterval_()
    , revisedQueueSize_()
    , filterResult_()
    {
    }
    
    MonitoredItemModifyResult::~MonitoredItemModifyResult(void)
    {
    }
    
    OpcUaStatus&
    MonitoredItemModifyResult::statusCode(void)
    {
        return statusCode_;
    }
    
    OpcUaDuration&
    MonitoredItemModifyResult::revisedSamplingInterval(void)
    {
        return revisedSamplingInterval_;
    }
    
    OpcUaCounter&
    MonitoredItemModifyResult::revisedQueueSize(void)
    {
        return revisedQueueSize_;
    }
    
    OpcUaExtensibleParameter&
    MonitoredItemModifyResult::filterResult(void)
    {
        return filterResult_;
    }
    
    bool
    MonitoredItemModifyResult::operator==(const MonitoredItemModifyResult& value)
    {
        MonitoredItemModifyResult* dst = const_cast<MonitoredItemModifyResult*>(&value);
        if (statusCode_ != dst->statusCode()) return false;
        if (revisedSamplingInterval_ != dst->revisedSamplingInterval()) return false;
        if (revisedQueueSize_ != dst->revisedQueueSize()) return false;
        if (filterResult_ != dst->filterResult()) return false;
        return true;
    }
    
    bool
    MonitoredItemModifyResult::operator!=(const MonitoredItemModifyResult& value)
    {
        return !this->operator==(value);
    }
    
    void
    MonitoredItemModifyResult::copyTo(MonitoredItemModifyResult& value)
    {
        statusCode_.copyTo(value.statusCode());
        value.revisedSamplingInterval_ = revisedSamplingInterval_;
        value.revisedQueueSize_ = revisedQueueSize_;
        filterResult_.copyTo(value.filterResult());
    }
    
    MonitoredItemModifyResult&
    MonitoredItemModifyResult::operator=(const MonitoredItemModifyResult& value)
    {
        const_cast<MonitoredItemModifyResult*>(&value)->copyTo(*this);
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
    MonitoredItemModifyResult::factory(void)
    {
    	return constructSPtr<MonitoredItemModifyResult>();
    }
    
    std::string
    MonitoredItemModifyResult::namespaceName(void)
    {
    	return "http://opcfoundation.org/UA/";
    }
    
    std::string
    MonitoredItemModifyResult::typeName(void)
    {
    	return "MonitoredItemModifyResult";
    }
    
    OpcUaNodeId
    MonitoredItemModifyResult::typeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)758,0);
    }
    
    OpcUaNodeId
    MonitoredItemModifyResult::binaryTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)760, 0);
    }
    
    OpcUaNodeId
    MonitoredItemModifyResult::xmlTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)759, 0);
    }
    
    OpcUaNodeId
    MonitoredItemModifyResult::jsonTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15326, 0);
    }
    
    void
    MonitoredItemModifyResult::opcUaBinaryEncode(std::ostream& os) const
    {
        statusCode_.opcUaBinaryEncode(os);
        OpcUaNumber::opcUaBinaryEncode(os,revisedSamplingInterval_);
        OpcUaNumber::opcUaBinaryEncode(os,revisedQueueSize_);
        filterResult_.opcUaBinaryEncode(os);
    }
    
    void
    MonitoredItemModifyResult::opcUaBinaryDecode(std::istream& is)
    {
        statusCode_.opcUaBinaryDecode(is);
        OpcUaNumber::opcUaBinaryDecode(is,revisedSamplingInterval_);
        OpcUaNumber::opcUaBinaryDecode(is,revisedQueueSize_);
        filterResult_.opcUaBinaryDecode(is);
    }
    
    bool
    MonitoredItemModifyResult::encode(boost::property_tree::ptree& pt, Xmlns& xmlns) const
    {
    }
    
    bool
    MonitoredItemModifyResult::decode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
    }
    
    bool
    MonitoredItemModifyResult::xmlEncode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
        if (!xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair(element, elementTree));
        return true;
    }
    
    bool
    MonitoredItemModifyResult::xmlEncode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
    
        elementTree.clear();
        if (!statusCode_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("StatusCode", elementTree));
    
        elementTree.clear();
        if(!XmlNumber::xmlEncode(elementTree, revisedSamplingInterval_)) return false;
        pt.push_back(std::make_pair("RevisedSamplingInterval", elementTree));
    
        elementTree.clear();
        if(!XmlNumber::xmlEncode(elementTree, revisedQueueSize_)) return false;
        pt.push_back(std::make_pair("RevisedQueueSize", elementTree));
    
        elementTree.clear();
        if (!filterResult_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("FilterResult", elementTree));
    
        return true;
    }
    
    bool
    MonitoredItemModifyResult::xmlDecode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree = pt.get_child_optional(element);
        if (!tree) return false;
        return xmlDecode(*tree, xmlns);
    }
    
    bool
    MonitoredItemModifyResult::xmlDecode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree;
    
        tree = pt.get_child_optional("StatusCode");
        if (!tree) return false;
        if (!statusCode_.xmlDecode(*tree, xmlns)) return false;
    
        tree = pt.get_child_optional("RevisedSamplingInterval");
        if (!tree) return false;
        if(!XmlNumber::xmlDecode(*tree, revisedSamplingInterval_)) return false;
    
        tree = pt.get_child_optional("RevisedQueueSize");
        if (!tree) return false;
        if(!XmlNumber::xmlDecode(*tree, revisedQueueSize_)) return false;
    
        tree = pt.get_child_optional("FilterResult");
        if (!tree) return false;
        if (!filterResult_.xmlDecode(*tree, xmlns)) return false;
    
        return true;
    }
    
    bool
    MonitoredItemModifyResult::jsonEncode(boost::property_tree::ptree& pt, const std::string& element)
    {
        return true;
    }
    
    bool
    MonitoredItemModifyResult::jsonEncode(boost::property_tree::ptree& pt)
    {
        return true;
    }
    
    bool
    MonitoredItemModifyResult::jsonDecode(boost::property_tree::ptree& pt, const std::string& element)
    {
    }
    
    bool
    MonitoredItemModifyResult::jsonDecode(boost::property_tree::ptree& pt)
    {
    }
    
    void
    MonitoredItemModifyResult::copyTo(ExtensionObjectBase& extensionObjectBase)
    {
    	MonitoredItemModifyResult* dst = dynamic_cast<MonitoredItemModifyResult*>(&extensionObjectBase);
    	copyTo(*dst);
    }
    
    bool
    MonitoredItemModifyResult::equal(ExtensionObjectBase& extensionObjectBase) const
    {
    	MonitoredItemModifyResult* dst = dynamic_cast<MonitoredItemModifyResult*>(&extensionObjectBase);
    	return *const_cast<MonitoredItemModifyResult*>(this) == *dst;
    }
    
    void
    MonitoredItemModifyResult::out(std::ostream& os)
    {
        os << "StatusCode="; statusCode_.out(os);
        os << ", RevisedSamplingInterval=" << revisedSamplingInterval_;
        os << ", RevisedQueueSize=" << revisedQueueSize_;
        os << ", FilterResult="; filterResult_.out(os);
    }

}