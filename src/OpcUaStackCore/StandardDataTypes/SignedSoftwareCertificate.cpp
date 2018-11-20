/*
    DataTypeClass: SignedSoftwareCertificate

    Generated Source Code - please do not change this source code

    DataTypeCodeGenerator Version:
        OpcUaStackCore - 4.1.0

    Autor: Kai Huebl (kai@huebl-sgh.de)
*/

#include "OpcUaStackCore/StandardDataTypes/SignedSoftwareCertificate.h"

namespace OpcUaStackCore
{
    
    /**
     * A software certificate with a digital signature.
     */
    SignedSoftwareCertificate::SignedSoftwareCertificate(void)
    : Object()
    , ExtensionObjectBase()
    , certificateData_()
    , signature_()
    {
    }
    
    SignedSoftwareCertificate::~SignedSoftwareCertificate(void)
    {
    }
    
    OpcUaByteString&
    SignedSoftwareCertificate::certificateData(void)
    {
        return certificateData_;
    }
    
    OpcUaByteString&
    SignedSoftwareCertificate::signature(void)
    {
        return signature_;
    }
    
    bool
    SignedSoftwareCertificate::operator==(const SignedSoftwareCertificate& value)
    {
        SignedSoftwareCertificate* dst = const_cast<SignedSoftwareCertificate*>(&value);
        if (certificateData_ != dst->certificateData()) return false;
        if (signature_ != dst->signature()) return false;
        return true;
    }
    
    bool
    SignedSoftwareCertificate::operator!=(const SignedSoftwareCertificate& value)
    {
        return !this->operator==(value);
    }
    
    void
    SignedSoftwareCertificate::copyTo(SignedSoftwareCertificate& value)
    {
        certificateData_.copyTo(value.certificateData());
        signature_.copyTo(value.signature());
    }
    
    SignedSoftwareCertificate&
    SignedSoftwareCertificate::operator=(const SignedSoftwareCertificate& value)
    {
        const_cast<SignedSoftwareCertificate*>(&value)->copyTo(*this);
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
    SignedSoftwareCertificate::factory(void)
    {
    	return constructSPtr<SignedSoftwareCertificate>();
    }
    
    std::string
    SignedSoftwareCertificate::namespaceName(void)
    {
    	return "http://opcfoundation.org/UA/";
    }
    
    std::string
    SignedSoftwareCertificate::typeName(void)
    {
    	return "SignedSoftwareCertificate";
    }
    
    OpcUaNodeId
    SignedSoftwareCertificate::typeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)344,0);
    }
    
    OpcUaNodeId
    SignedSoftwareCertificate::binaryTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)346, 0);
    }
    
    OpcUaNodeId
    SignedSoftwareCertificate::xmlTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)345, 0);
    }
    
    OpcUaNodeId
    SignedSoftwareCertificate::jsonTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15136, 0);
    }
    
    void
    SignedSoftwareCertificate::opcUaBinaryEncode(std::ostream& os) const
    {
        certificateData_.opcUaBinaryEncode(os);
        signature_.opcUaBinaryEncode(os);
    }
    
    void
    SignedSoftwareCertificate::opcUaBinaryDecode(std::istream& is)
    {
        certificateData_.opcUaBinaryDecode(is);
        signature_.opcUaBinaryDecode(is);
    }
    
    bool
    SignedSoftwareCertificate::encode(boost::property_tree::ptree& pt, Xmlns& xmlns) const
    {
    }
    
    bool
    SignedSoftwareCertificate::decode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
    }
    
    bool
    SignedSoftwareCertificate::xmlEncode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
        if (!xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair(element, elementTree));
        return true;
    }
    
    bool
    SignedSoftwareCertificate::xmlEncode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
    
        elementTree.clear();
        if (!certificateData_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("CertificateData", elementTree));
    
        elementTree.clear();
        if (!signature_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("Signature", elementTree));
    
        return true;
    }
    
    bool
    SignedSoftwareCertificate::xmlDecode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree = pt.get_child_optional(element);
        if (!tree) return false;
        return xmlDecode(*tree, xmlns);
    }
    
    bool
    SignedSoftwareCertificate::xmlDecode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree;
    
        tree = pt.get_child_optional("CertificateData");
        if (!tree) return false;
        if (!certificateData_.xmlDecode(*tree, xmlns)) return false;
    
        tree = pt.get_child_optional("Signature");
        if (!tree) return false;
        if (!signature_.xmlDecode(*tree, xmlns)) return false;
    
        return true;
    }
    
    bool
    SignedSoftwareCertificate::jsonEncode(boost::property_tree::ptree& pt, const std::string& element)
    {
        return true;
    }
    
    bool
    SignedSoftwareCertificate::jsonEncode(boost::property_tree::ptree& pt)
    {
        return true;
    }
    
    bool
    SignedSoftwareCertificate::jsonDecode(boost::property_tree::ptree& pt, const std::string& element)
    {
    }
    
    bool
    SignedSoftwareCertificate::jsonDecode(boost::property_tree::ptree& pt)
    {
    }
    
    void
    SignedSoftwareCertificate::copyTo(ExtensionObjectBase& extensionObjectBase)
    {
    	SignedSoftwareCertificate* dst = dynamic_cast<SignedSoftwareCertificate*>(&extensionObjectBase);
    	copyTo(*dst);
    }
    
    bool
    SignedSoftwareCertificate::equal(ExtensionObjectBase& extensionObjectBase) const
    {
    	SignedSoftwareCertificate* dst = dynamic_cast<SignedSoftwareCertificate*>(&extensionObjectBase);
    	return *const_cast<SignedSoftwareCertificate*>(this) == *dst;
    }
    
    void
    SignedSoftwareCertificate::out(std::ostream& os)
    {
        os << "CertificateData="; certificateData_.out(os);
        os << ", Signature="; signature_.out(os);
    }

}
