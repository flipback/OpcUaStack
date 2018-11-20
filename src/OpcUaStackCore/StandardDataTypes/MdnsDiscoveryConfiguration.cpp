/*
    DataTypeClass: MdnsDiscoveryConfiguration

    Generated Source Code - please do not change this source code

    DataTypeCodeGenerator Version:
        OpcUaStackCore - 4.1.0

    Autor: Kai Huebl (kai@huebl-sgh.de)
*/

#include "OpcUaStackCore/StandardDataTypes/MdnsDiscoveryConfiguration.h"

namespace OpcUaStackCore
{
    
    /**
     * The discovery information needed for mDNS registration.
     */
    MdnsDiscoveryConfiguration::MdnsDiscoveryConfiguration(void)
    : DiscoveryConfiguration()
    , mdnsServerName_()
    , serverCapabilities_()
    {
    }
    
    MdnsDiscoveryConfiguration::~MdnsDiscoveryConfiguration(void)
    {
    }
    
    OpcUaString&
    MdnsDiscoveryConfiguration::mdnsServerName(void)
    {
        return mdnsServerName_;
    }
    
    OpcUaStringArray&
    MdnsDiscoveryConfiguration::serverCapabilities(void)
    {
        return serverCapabilities_;
    }
    
    bool
    MdnsDiscoveryConfiguration::operator==(const MdnsDiscoveryConfiguration& value)
    {
        MdnsDiscoveryConfiguration* dst = const_cast<MdnsDiscoveryConfiguration*>(&value);
        if (mdnsServerName_ != dst->mdnsServerName()) return false;
        if (serverCapabilities_ != dst->serverCapabilities()) return false;
        return true;
    }
    
    bool
    MdnsDiscoveryConfiguration::operator!=(const MdnsDiscoveryConfiguration& value)
    {
        return !this->operator==(value);
    }
    
    void
    MdnsDiscoveryConfiguration::copyTo(MdnsDiscoveryConfiguration& value)
    {
        mdnsServerName_.copyTo(value.mdnsServerName());
        serverCapabilities_.copyTo(value.serverCapabilities());
    }
    
    MdnsDiscoveryConfiguration&
    MdnsDiscoveryConfiguration::operator=(const MdnsDiscoveryConfiguration& value)
    {
        const_cast<MdnsDiscoveryConfiguration*>(&value)->copyTo(*this);
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
    MdnsDiscoveryConfiguration::factory(void)
    {
    	return constructSPtr<MdnsDiscoveryConfiguration>();
    }
    
    std::string
    MdnsDiscoveryConfiguration::namespaceName(void)
    {
    	return "http://opcfoundation.org/UA/";
    }
    
    std::string
    MdnsDiscoveryConfiguration::typeName(void)
    {
    	return "MdnsDiscoveryConfiguration";
    }
    
    OpcUaNodeId
    MdnsDiscoveryConfiguration::typeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)12891,0);
    }
    
    OpcUaNodeId
    MdnsDiscoveryConfiguration::binaryTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)12901, 0);
    }
    
    OpcUaNodeId
    MdnsDiscoveryConfiguration::xmlTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)12893, 0);
    }
    
    OpcUaNodeId
    MdnsDiscoveryConfiguration::jsonTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15106, 0);
    }
    
    void
    MdnsDiscoveryConfiguration::opcUaBinaryEncode(std::ostream& os) const
    {
        mdnsServerName_.opcUaBinaryEncode(os);
        serverCapabilities_.opcUaBinaryEncode(os);
    }
    
    void
    MdnsDiscoveryConfiguration::opcUaBinaryDecode(std::istream& is)
    {
        mdnsServerName_.opcUaBinaryDecode(is);
        serverCapabilities_.opcUaBinaryDecode(is);
    }
    
    bool
    MdnsDiscoveryConfiguration::encode(boost::property_tree::ptree& pt, Xmlns& xmlns) const
    {
    }
    
    bool
    MdnsDiscoveryConfiguration::decode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
    }
    
    bool
    MdnsDiscoveryConfiguration::xmlEncode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
        if (!xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair(element, elementTree));
        return true;
    }
    
    bool
    MdnsDiscoveryConfiguration::xmlEncode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
    
        elementTree.clear();
        if (!mdnsServerName_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("MdnsServerName", elementTree));
    
        elementTree.clear();
        if (!serverCapabilities_.xmlEncode(elementTree, "String", xmlns)) return false;
        pt.push_back(std::make_pair("ServerCapabilities", elementTree));
    
        return true;
    }
    
    bool
    MdnsDiscoveryConfiguration::xmlDecode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree = pt.get_child_optional(element);
        if (!tree) return false;
        return xmlDecode(*tree, xmlns);
    }
    
    bool
    MdnsDiscoveryConfiguration::xmlDecode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree;
    
        tree = pt.get_child_optional("MdnsServerName");
        if (!tree) return false;
        if (!mdnsServerName_.xmlDecode(*tree, xmlns)) return false;
    
        tree = pt.get_child_optional("ServerCapabilities");
        if (!tree) return false;
        if (!serverCapabilities_.xmlDecode(*tree, "String", xmlns)) return false;
    
        return true;
    }
    
    bool
    MdnsDiscoveryConfiguration::jsonEncode(boost::property_tree::ptree& pt, const std::string& element)
    {
        return true;
    }
    
    bool
    MdnsDiscoveryConfiguration::jsonEncode(boost::property_tree::ptree& pt)
    {
        return true;
    }
    
    bool
    MdnsDiscoveryConfiguration::jsonDecode(boost::property_tree::ptree& pt, const std::string& element)
    {
    }
    
    bool
    MdnsDiscoveryConfiguration::jsonDecode(boost::property_tree::ptree& pt)
    {
    }
    
    void
    MdnsDiscoveryConfiguration::copyTo(ExtensionObjectBase& extensionObjectBase)
    {
    	MdnsDiscoveryConfiguration* dst = dynamic_cast<MdnsDiscoveryConfiguration*>(&extensionObjectBase);
    	copyTo(*dst);
    }
    
    bool
    MdnsDiscoveryConfiguration::equal(ExtensionObjectBase& extensionObjectBase) const
    {
    	MdnsDiscoveryConfiguration* dst = dynamic_cast<MdnsDiscoveryConfiguration*>(&extensionObjectBase);
    	return *const_cast<MdnsDiscoveryConfiguration*>(this) == *dst;
    }
    
    void
    MdnsDiscoveryConfiguration::out(std::ostream& os)
    {
        os << "MdnsServerName="; mdnsServerName_.out(os);
        os << ", ServerCapabilities="; serverCapabilities_.out(os);
    }

}
